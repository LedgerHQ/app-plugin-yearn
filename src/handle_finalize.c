#include "yearn_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    msg->numScreens = 2;  // At least 2, amount + vault

    switch (context->selectorIndex) {
        case DEPOSIT_TO:
        case WITHDRAW_TO:
            if (memcmp(msg->address, context->extra_address, ADDRESS_LENGTH) != 0) {
                msg->numScreens += 1;
            }
            break;
        case WITHDRAW_TO_SLIPPAGE:
            msg->numScreens += 2;
            break;
        case ZAP_IN:
            msg->tokenLookup1 = context->extra_address;
            break;
        case ZAP_IN_PICKLE:
            msg->tokenLookup1 = context->extra_address;
            break;
        default:
            break;
    }
    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->result = ETH_PLUGIN_RESULT_OK;
}
