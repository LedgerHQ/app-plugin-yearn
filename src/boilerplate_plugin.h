#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 7

// Name of the plugin.
#define PLUGIN_NAME "Yearn"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
// EDIT THIS: Change the naming (`selector_t`), and add your selector names.
typedef enum {
    DEPOSIT_ALL,
    DEPOSIT,
    DEPOSIT_TO,
    WITHDRAW_ALL,
    WITHDRAW,
    WITHDRAW_TO,
    WITHDRAW_TO_SLIPPAGE,
} selector_t;

// Enumeration used to parse the smart contract data.
// EDIT THIS: Adapt the parameter names here.
typedef enum {
    AMOUNT_TO_DEPOSIT = 0,
    AMOUNT_TO_WITHDRAW = 0,
    RECIPIENT,
    SLIPPAGE,
    UNEXPECTED_PARAMETER,
} parameter;

extern const uint8_t *const YEARN_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
// EDIT THIS: This struct is used by your plugin to save the parameters you parse. You
// will need to adapt this struct to your plugin.
typedef struct context_t {
    // For display.
    uint8_t amount_to_deposit[INT256_LENGTH];
    uint8_t amount_to_withdraw[INT256_LENGTH];
    uint8_t recipient[ADDRESS_LENGTH];
    uint8_t slippage[INT256_LENGTH];
    uint8_t vault_address[ADDRESS_LENGTH];

    char ticker[MAX_TICKER_LEN];
    uint8_t decimals;
    uint8_t token_found;

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);