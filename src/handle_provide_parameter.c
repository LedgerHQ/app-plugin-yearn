#include "yearn_plugin.h"

// Copies the whole parameter (32 bytes long) from `src` to `dst`.
// Useful for numbers, data...
static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // Take the minimum between dst_len and parameter_length to make sure we don't overwrite memory.
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

// Copies a 20 byte address (located in a 32 bytes parameter) `from `src` to `dst`.
// Useful for token addresses, user addresses...
static void copy_address(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // An address is 20 bytes long: so we need to make sure we skip the first 12 bytes!
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
        case AMOUNT_TO_DEPOSIT:
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
        case AMOUNT_TO_DEPOSIT:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->recipient, sizeof(context->recipient), msg->parameter);
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
        case AMOUNT_TO_WITHDRAW:
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
        case AMOUNT_TO_WITHDRAW:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->recipient, sizeof(context->recipient), msg->parameter);
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
        case AMOUNT_TO_WITHDRAW:
            copy_parameter(context->amount, sizeof(context->amount), msg->parameter);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            copy_address(context->recipient, sizeof(context->recipient), msg->parameter);
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

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;

    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
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
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}