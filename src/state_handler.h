/**
 * @file state_handler.h
 *
 * @brief Header for the module for handling any state related functions.
 */

#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include "packet_constants.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int process_state_and_transitions(packet_type_t pack_type,
                                  pwr_packet_t const * const pwr,
                                  batt_packet_t const * const batt);

#ifdef __cplusplus
}
#endif

#endif // STATE_HANDLER_H
