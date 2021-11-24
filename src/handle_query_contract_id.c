#include "yearn_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case DEPOSIT_ALL:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case DEPOSIT:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case DEPOSIT_TO:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case WITHDRAW_ALL:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case WITHDRAW:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case WITHDRAW_TO:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case WITHDRAW_TO_SLIPPAGE:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case ZAP_IN:
            strlcpy(msg->version, "Zap In", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}