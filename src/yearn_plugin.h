#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PLUGIN_NAME          "Yearn"
#define NUM_SELECTORS        7
#define MAX_VAULT_TICKER_LEN 18  // 17 characters + '\0'

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    DEPOSIT,
    DEPOSIT_ALL,
    WITHDRAW_ALL,
    WITHDRAW,
    WITHDRAW_TO,
    WITHDRAW_TO_SLIPPAGE,
    ZAP_IN,
} selector_t;

// Enumeration used to parse the smart contract data.
#define ZAP_TOKEN       0
#define ZAP_AMOUNT      1
#define ZAP_INTER_TOKEN 2
#define ZAP_TO_VAULT    3
#define TRACK_VAULT     4
#define TRACK_PARNER    5
#define TRACK_AMOUNT    6
#define AMOUNT          7
#define RECIPIENT       8
#define SLIPPAGE        9
#define UNEXPECTED_PARAMETER    13 //when it's done parsing but there's still data there

extern const uint8_t *const YEARN_SELECTORS[NUM_SELECTORS];

typedef struct yearnVaultDefinition_t {
    uint8_t address[ADDRESS_LENGTH];
    char want[MAX_VAULT_TICKER_LEN];
    char vault[MAX_VAULT_TICKER_LEN];
    uint8_t decimals;
} yearnVaultDefinition_t;

#define NUM_YEARN_VAULTS 95
extern yearnVaultDefinition_t const YEARN_VAULTS[NUM_YEARN_VAULTS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    uint8_t amount[INT256_LENGTH];
    uint8_t slippage[INT256_LENGTH];
    uint8_t vault_address[ADDRESS_LENGTH];
    uint8_t extra_address[ADDRESS_LENGTH];
    char vault[MAX_VAULT_TICKER_LEN];
    char want[MAX_VAULT_TICKER_LEN];

    uint8_t decimals;
    uint8_t next_param;
    uint16_t offset;
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_token(void *parameters);
void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_query_contract_id(void *parameters);