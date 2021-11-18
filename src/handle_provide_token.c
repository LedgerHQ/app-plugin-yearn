#include "yearn_plugin.h"

// EDIT THIS: Adapt this function to your needs! Remember, the information for tokens are held in
// `msg->token1` and `msg->token2`. If those pointers are `NULL`, this means the ethereum app didn't
// find any info regarding the requested tokens!
void handle_provide_token(void *parameters) {
    ethPluginProvideToken_t *msg = (ethPluginProvideToken_t *) parameters;
    msg->result = ETH_PLUGIN_RESULT_OK;
}