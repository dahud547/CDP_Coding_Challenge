/**
 * @file calculations.h
 *
 * @brief Header of the module for holding the functions used for calculating power
 *
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "packet_constants.h"

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int calc_power(pwr_packet_t * const pwr_numbers);
uint32_t mod_of_array(uint8_t const * const p_array, size_t length);

#ifdef __cplusplus
}
#endif

#endif // CALCULATIONS_H
