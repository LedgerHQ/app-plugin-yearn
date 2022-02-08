#include "yearn_plugin.h"

static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

void copy_amount_with_ticker(const uint8_t *amount,
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
    memcpy(out_buffer + amount_len, " ", 1);
    memcpy(out_buffer + amount_len + 1, ticker, ticker_size);
    out_buffer[out_buffer_size - 1] = '\0';
}

void copy_vault_name(const char *vaultName,
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

/******************************************************************************
**  Will display the splipage used for this transaction.
**  | Slippage |
**  |   10 %   |
******************************************************************************/
static void set_slippage_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Slippage", msg->titleLength);
    copy_amount_with_ticker(context->slippage,
                            sizeof(context->slippage),
                            2,
                            "%",
                            1,
                            msg->msg,
                            msg->msgLength);
}

/******************************************************************************
**  Will display the recipient's address (withdraw)
**  |                   Recipient                  |
**  |  0x28bC240B2433B65d3C64EBF168862E60fAb019E4  |
******************************************************************************/
static void set_recipient_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Recipient", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->extra_address,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  chainid);
}

/******************************************************************************
**  Will display the address of the vault
**  |                     Vault                    |
**  |  0x28bC240B2433B65d3C64EBF168862E60fAb019E4  |
******************************************************************************/
static void set_vault_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Vault", msg->titleLength);

    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->vault_address,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  chainid);
}

/******************************************************************************
**  Will display the amount of token to be deposit in the vault.
**  |   Amount  |
**  |  200 DAI  |
******************************************************************************/
static void set_amount_with_want(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    copy_amount_with_ticker(context->amount,
                            sizeof(context->amount),
                            context->decimals,
                            context->want,
                            sizeof(context->want),
                            msg->msg,
                            msg->msgLength);
}

/******************************************************************************
**  Will display the amount of token to be withdrawn from the vault.
**  |    Amount   |
**  |  200 yvDAI  |
******************************************************************************/
static void set_amount_with_vault(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    copy_amount_with_ticker(context->amount,
                            sizeof(context->amount),
                            context->decimals,
                            context->vault,
                            sizeof(context->vault),
                            msg->msg,
                            msg->msgLength);
}

/******************************************************************************
**  Will display ALL to indicate that the full balance should be deposited or
**  withdrawn.
**  |  Amount |
**  |   ALL   |
******************************************************************************/
static void set_amount_with_all(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    strlcpy(msg->msg, "ALL", msg->msgLength);
}

/******************************************************************************
**  Will display the Vault name. The vaults are defined in main.c in the
**  YEARN_VAULTS variable.
**  | Vault |
**  | yvDAI |
******************************************************************************/
static void set_vault_name(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Vault", msg->titleLength);
    strlcpy(msg->msg, context->vault, msg->msgLength);
}

void handle_query_contract_ui_zap_in(ethQueryContractUI_t *msg, context_t *context) {
    uint8_t i;
    yearnVaultDefinition_t *currentVault = NULL;
    for (i = 0; i < NUM_YEARN_VAULTS; i++) {
        currentVault = (yearnVaultDefinition_t *) PIC(&YEARN_VAULTS[i]);
        if (memcmp(currentVault->address, context->vault_address, ADDRESS_LENGTH) == 0) {
            memcpy(context->vault, currentVault->vault, MAX_VAULT_TICKER_LEN);
            break;
        }
    }

    switch (msg->screenIndex) {
        case 0:
            set_amount_with_want(msg, context);
            break;
        case 1:
            if (context->selectorIndex == ZAP_IN_PICKLE) {
                strlcpy(msg->title, "Vault", msg->titleLength);
                strlcpy(msg->msg, "pSLPyvBOOST-ETH", msg->msgLength);
                break;
            }
            set_vault_name(msg, context);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}

void handle_query_contract_ui_vaults(ethQueryContractUI_t *msg, context_t *context) {
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
                case WITHDRAW_ALL:
                case DEPOSIT_ALL:
                case CLAIM:
                case GET_REWARDS:
                case EXIT:
                    set_amount_with_all(msg);
                    break;
                case DEPOSIT_TO:
                case DEPOSIT:
                    set_amount_with_want(msg, context);
                    break;
                case WITHDRAW_TO_SLIPPAGE:
                case WITHDRAW_TO:
                case WITHDRAW:
                    set_amount_with_vault(msg, context);
                    break;
                default:
                    break;
            }
            break;
        case 1:
            set_vault_name(msg, context);
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

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case ZAP_IN:
        case ZAP_IN_PICKLE:
            handle_query_contract_ui_zap_in(msg, context);
            break;
        default:
            handle_query_contract_ui_vaults(msg, context);
            return;
    }
}
