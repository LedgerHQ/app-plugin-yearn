#include "yearn_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case DEPOSIT:
        case DEPOSIT_TO:
        case DEPOSIT_ALL:
            strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case WITHDRAW:
        case WITHDRAW_TO:
        case WITHDRAW_ALL:
        case WITHDRAW_TO_SLIPPAGE:
            strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case CLAIM:
        case GET_REWARDS:
            strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
            strlcpy(msg->version, "Claim", msg->versionLength);
            break;
        case EXIT:
            strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
            strlcpy(msg->version, "Exit", msg->versionLength);
            break;
        case ZAP_IN:
            strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
            strlcpy(msg->version, "Zap In", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}