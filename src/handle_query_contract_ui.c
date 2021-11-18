#include "yearn_plugin.h"

// Copies the whole parameter (32 bytes long) from `src` to `dst`.
// Useful for numbers, data...
static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // Take the minimum between dst_len and parameter_length to make sure we don't overwrite memory.
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

void amountToPercent(const uint8_t *amount,
                     uint8_t amount_size,
                     char *out_buffer,
                     uint8_t out_buffer_size) {
    char tmp_buffer[100] = {0};

    amountToString(amount, amount_size, 2, "", tmp_buffer, 100);
    uint8_t amount_len = strnlen(tmp_buffer, sizeof(tmp_buffer));
    memcpy(out_buffer, tmp_buffer, amount_len);
    memcpy(out_buffer + amount_len, " %", 2);
    out_buffer[out_buffer_size - 1] = '\0';
}

void amountWithTicker(const uint8_t *amount,
                      uint8_t amount_size,
                      uint8_t amount_decimals,
                      char *ticker,
                      uint8_t ticker_size,
                      char *out_buffer,
                      uint8_t out_buffer_size) {
    char tmp_buffer[100] = {0};

    amountToString(amount, amount_size, amount_decimals, "", tmp_buffer, 100);

    uint8_t amount_len = strnlen(tmp_buffer, sizeof(tmp_buffer));
    memcpy(out_buffer, tmp_buffer, amount_len);

    memcpy(out_buffer + amount_len, ticker, ticker_size);
    out_buffer[out_buffer_size - 1] = '\0';
}


static void set_amount_ui(ethQueryContractUI_t *msg,
                          context_t *context,
                          bool isDeposit,
                          bool isAll) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    if (isAll) {
        strlcpy(msg->msg, "ALL", msg->msgLength);
    } else if (isDeposit) {
        amountWithTicker(context->amount,
                         sizeof(context->amount),
                         context->decimals,
                         context->want,
                         sizeof(context->want),
                         msg->msg,
                         msg->msgLength);
    } else {
        amountWithTicker(context->amount,
                         sizeof(context->amount),
                         context->decimals,
                         context->vault,
                         sizeof(context->vault),
                         msg->msg,
                         msg->msgLength);
    }
}

static void set_slippage_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Slippage", msg->titleLength);

    amountToPercent(context->slippage, sizeof(context->slippage), msg->msg, msg->msgLength);
}

static void set_recipient_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Recipient", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->recipient,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  chainid);
}

void setVaultName(const char *vaultName,
                     uint8_t vaultName_size,
                     char *out_buffer,
                     uint8_t out_buffer_size) {
    char tmp_buffer[100] = {0};

    strlcpy(tmp_buffer, vaultName, vaultName_size);
    uint8_t amount_len = strnlen(tmp_buffer, sizeof(tmp_buffer));
    memcpy(out_buffer, tmp_buffer, amount_len);
    memcpy(out_buffer + amount_len, " vault", 6);
    out_buffer[out_buffer_size - 1] = '\0';
}

static void set_vault_ui(ethQueryContractUI_t *msg, context_t *context) {
    // setVaultName(context->vault, sizeof(context->vault), msg->title, msg->titleLength);
    // strlcpy(msg->title, context->vault, msg->titleLength);
    strlcpy(msg->title, "Vault", msg->titleLength);

    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->vault_address,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  chainid);
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // Copy the vault address prior to any process
    ethPluginSharedRO_t *pluginSharedRO = (ethPluginSharedRO_t *) msg->pluginSharedRO;
    copy_parameter(context->vault_address,
                   sizeof(context->vault_address),
                   pluginSharedRO->txContent->destination);

    // find information about vault
    uint8_t i;
    yearnVaultDefinition_t *currentVault = NULL;
    for (i = 0; i < NUM_YEARN_VAULTS; i++) {
        currentVault = (yearnVaultDefinition_t *) PIC(&YEARN_VAULTS[i]);
        if (memcmp(currentVault->address, context->vault_address, ADDRESS_LENGTH) == 0) {
            context->decimals = currentVault->decimals;
            memcpy(context->want, currentVault->want, MAX_VAULT_TICKER_LEN);
            memcpy(context->vault, currentVault->vault, MAX_VAULT_TICKER_LEN);
            break;
        }
    }

    switch (msg->screenIndex) {
        case 0:
            switch (context->selectorIndex) {
                case DEPOSIT_ALL:
                    set_amount_ui(msg, context, true, true);
                    break;
                case DEPOSIT:
                    set_amount_ui(msg, context, true, false);
                    break;
                case DEPOSIT_TO:
                    set_amount_ui(msg, context, true, false);
                    break;
                case WITHDRAW_ALL:
                    set_amount_ui(msg, context, false, true);
                    break;
                case WITHDRAW:
                    set_amount_ui(msg, context, false, false);
                    break;
                case WITHDRAW_TO:
                    set_amount_ui(msg, context, false, false);
                    break;
                case WITHDRAW_TO_SLIPPAGE:
                    set_amount_ui(msg, context, false, false);
                    break;
            }
            break;
        case 1:
            set_vault_ui(msg, context);
            break;
        case 2:
            set_recipient_ui(msg, context);
            break;
        case 3:
            set_slippage_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
