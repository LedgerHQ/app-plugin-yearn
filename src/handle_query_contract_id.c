#include "yearn_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case DEPOSIT:
        case DEPOSIT_ALL:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case WITHDRAW:
        case WITHDRAW_TO:
        case WITHDRAW_ALL:
        case WITHDRAW_TO_SLIPPAGE:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case CLAIM:
            strlcpy(msg->version, "Claim", msg->versionLength);
            break;
        case ZAP_IN:
            strlcpy(msg->version, "Zap In", msg->versionLength);
            break;
        case ZAP_CRV:
            strlcpy(msg->version, "Zap", msg->versionLength);
            break;
        case ZAP_ETH:
            strlcpy(msg->version, "Zap ETH", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
