#include "yearn_plugin.h"

static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

static void copy_address(uint8_t *dst, size_t dst_len, uint8_t *src) {
    size_t offset = PARAMETER_LENGTH - ADDRESS_LENGTH;
    size_t len = MIN(dst_len, ADDRESS_LENGTH);
    memcpy(dst, &src[offset], len);
}

static void handle_deposit_all(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        // no params
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_deposit_to(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->extra_address, sizeof(context->extra_address), msg->parameter);
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw_all(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw_to(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->extra_address, sizeof(context->extra_address), msg->parameter);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_withdraw_to_slippage(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->extra_address, sizeof(context->extra_address), msg->parameter);
            context->next_param = SLIPPAGE;
            break;
        case SLIPPAGE:
            copy_parameter(context->slippage, sizeof(context->slippage), msg->parameter);
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_zap_in(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case ZAP_TOKEN:
            copy_address(context->extra_address, sizeof(context->extra_address), msg->parameter);
            context->next_param = ZAP_AMOUNT;
            break;
        case ZAP_AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = ZAP_TO_VAULT;
            break;
        case ZAP_TO_VAULT:
            copy_address(context->vault_address, sizeof(context->vault_address), msg->parameter);
            context->next_param = ZAP_REST;
            break;
        case ZAP_REST:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_iron_bank(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DEPOSIT_ALL:
            handle_deposit_all(msg, context);
            break;
        case DEPOSIT:
            handle_deposit(msg, context);
            break;
        case DEPOSIT_TO:
            handle_deposit_to(msg, context);
            break;
        case WITHDRAW_ALL:
            handle_withdraw_all(msg, context);
            break;
        case WITHDRAW:
            handle_withdraw(msg, context);
            break;
        case WITHDRAW_TO:
            handle_withdraw_to(msg, context);
            break;
        case WITHDRAW_TO_SLIPPAGE:
            handle_withdraw_to_slippage(msg, context);
            break;
        case ZAP_IN:
            handle_zap_in(msg, context);
            break;
        case IB_MINT:
        case IB_REDEEM:
        case IB_REDEEM_UNDERLYING:
        case IB_BORROW:
        case IB_REPAY_BORROW:
            handle_iron_bank(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}