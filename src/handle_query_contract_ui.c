#include <stdio.h>
#include <stdbool.h>
#include "yearn_plugin.h"

bool copy_amount_with_ticker(const size_t *amount,
                             size_t amount_size,
                             size_t amount_decimals,
                             char *ticker,
                             size_t ticker_size,
                             char *out_buffer,
                             size_t out_buffer_size) {
    char tmp_buffer[100] = {0};
    if (!amountToString(amount, amount_size, amount_decimals, "", tmp_buffer, sizeof(tmp_buffer))) {
        return false;
    }
    size_t stringLen = strnlen(tmp_buffer, sizeof(tmp_buffer)) + 1 + ticker_size;
    snprintf(out_buffer, MIN(out_buffer_size, stringLen), "%s %s", tmp_buffer, ticker);
    out_buffer[out_buffer_size - 1] = '\0';
    return true;
}

/******************************************************************************
**  Will display the splipage used for this transaction.
**  | Slippage |
**  |   10 %   |
******************************************************************************/
static bool set_slippage_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Slippage", msg->titleLength);
    return copy_amount_with_ticker(context->slippage,
                                   sizeof(context->slippage),
                                   2,
                                   "%%",
                                   2,
                                   msg->msg,
                                   msg->msgLength);
}

/******************************************************************************
**  Will display the recipient's address (withdraw)
**  |                   Recipient                  |
**  |  0x28bC240B2433B65d3C64EBF168862E60fAb019E4  |
******************************************************************************/
static bool set_recipient_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Recipient", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    return getEthAddressStringFromBinary(context->extra_address,
                                         msg->msg + 2,
                                         msg->pluginSharedRW->sha3,
                                         chainid);
}

/******************************************************************************
**  Will display the amount of token to be deposit in the vault.
**  |   Amount  |
**  |  200 DAI  |
******************************************************************************/
static bool set_amount_with_want(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    return copy_amount_with_ticker(context->amount,
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
static bool set_amount_with_vault(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    return copy_amount_with_ticker(context->amount,
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
static bool set_amount_with_all(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    strlcpy(msg->msg, "ALL", msg->msgLength);
    return true;
}

/******************************************************************************
**  Will display the Vault name. The vaults are defined in main.c in the
**  YEARN_VAULTS variable.
**  | Vault |
**  | yvDAI |
******************************************************************************/
static bool set_vault_name(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Vault", msg->titleLength);
    strlcpy(msg->msg, context->vault, msg->msgLength);
    return true;
}

/******************************************************************************
**  Will search for current vault in YEARN_VAULTS.
**  It will set name and want in context.
******************************************************************************/
bool set_vault_information(ethQueryContractUI_t *msg, context_t *context) {
    uint8_t i;
    yearnVaultDefinition_t *currentVault = NULL;

    (void) msg;
    for (i = 0; i < NUM_YEARN_VAULTS; i++) {
        currentVault = (yearnVaultDefinition_t *) PIC(&YEARN_VAULTS[i]);
        if (memcmp(currentVault->address, context->vault_address, ADDRESS_LENGTH) == 0) {
            context->decimals = currentVault->decimals;
            if (context->selectorIndex != ZAP_IN) {
                memcpy(context->want, currentVault->want, MAX_VAULT_TICKER_LEN);
            }
            memcpy(context->vault, currentVault->vault, MAX_VAULT_TICKER_LEN);
            break;
        }
    }

    if (context->vault[0] == '\0') {
        PRINTF("Received an invalid vault\n");
        return false;
    }
    return true;
}

bool handle_query_contract_ui_zap_in(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    if (set_vault_information(msg, context)) {
        switch (msg->screenIndex) {
            case 0:
                ret = set_amount_with_want(msg, context);
                break;
            case 1:
                ret = set_vault_name(msg, context);
                break;
            default:
                PRINTF("Received an invalid screenIndex\n");
        }
    }
    return ret;
}

bool handle_query_contract_ui_track_in(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    if (set_vault_information(msg, context)) {
        switch (msg->screenIndex) {
            case 0:
                switch (context->selectorIndex) {
                    case DEPOSIT_ALL:
                        ret = set_amount_with_all(msg);
                        break;
                    case DEPOSIT:
                        ret = set_amount_with_want(msg, context);
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                ret = set_vault_name(msg, context);
                break;
            default:
                PRINTF("Received an invalid screenIndex\n");
        }
    }
    return ret;
}

bool handle_query_contract_ui_vaults(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;
    // Copy the vault address prior to any process
    ethPluginSharedRO_t *pluginSharedRO = (ethPluginSharedRO_t *) msg->pluginSharedRO;
    copy_parameter(context->vault_address,
                   pluginSharedRO->txContent->destination,
                   sizeof(context->vault_address));

    if (set_vault_information(msg, context)) {
        switch (msg->screenIndex) {
            case 0:
                switch (context->selectorIndex) {
                    case CLAIM:
                    case WITHDRAW_ALL:
                        ret = set_amount_with_all(msg);
                        break;
                    case WITHDRAW_TO_SLIPPAGE:
                    case WITHDRAW_TO:
                    case WITHDRAW:
                        ret = set_amount_with_vault(msg, context);
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                ret = set_vault_name(msg, context);
                break;
            case 2:
                ret = set_recipient_ui(msg, context);
                break;
            case 3:
                ret = set_slippage_ui(msg, context);
                break;
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
        }
    }
    return ret;
}

bool handle_query_contract_ui_zap_eth(ethQueryContractUI_t *msg) {
    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);
            ret = amountToString(eth_amount,
                                 eth_amount_size,
                                 WEI_TO_ETHER,
                                 "ETH",
                                 msg->msg,
                                 msg->msgLength);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case ZAP_ETH:
            ret = handle_query_contract_ui_zap_eth(msg);
            break;
        case DEPOSIT:
        case DEPOSIT_ALL:
            ret = handle_query_contract_ui_track_in(msg, context);
            break;
        case ZAP_CRV:
        case ZAP_IN:
            ret = handle_query_contract_ui_zap_in(msg, context);
            break;
        default:
            ret = handle_query_contract_ui_vaults(msg, context);
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
