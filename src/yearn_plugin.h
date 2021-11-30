#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PLUGIN_NAME          "Yearn"
#define NUM_SELECTORS        17
#define MAX_VAULT_TICKER_LEN 18  // 17 characters + '\0'

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    DEPOSIT_ALL,
    DEPOSIT,
    DEPOSIT_TO,
    WITHDRAW_ALL,
    WITHDRAW,
    WITHDRAW_TO,
    WITHDRAW_TO_SLIPPAGE,
    ZAP_IN,
    ZAP_IN_PICKLE,
    IB_MINT,
    IB_REDEEM,
    IB_REDEEM_UNDERLYING,
    IB_BORROW,
    IB_REPAY_BORROW,
    CLAIM,
    EXIT,
    GET_REWARDS,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    ZAP_TOKEN = 0,
    ZAP_AMOUNT = 1,
    ZAP_TO_VAULT = 2,
    ZAP_REST = 3,

    AMOUNT = 0,
    RECIPIENT,
    SLIPPAGE,
    UNEXPECTED_PARAMETER,
} parameter;

extern const uint8_t *const YEARN_SELECTORS[NUM_SELECTORS];

typedef struct yearnVaultDefinition_t {
    uint8_t address[ADDRESS_LENGTH];
    char want[MAX_VAULT_TICKER_LEN];
    char vault[MAX_VAULT_TICKER_LEN];
    uint8_t decimals;
} yearnVaultDefinition_t;

#define NUM_YEARN_VAULTS 78
extern yearnVaultDefinition_t const YEARN_VAULTS[NUM_YEARN_VAULTS];
#define NUM_IRON_BANK 32
extern yearnVaultDefinition_t const IRON_BANK[NUM_IRON_BANK];

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