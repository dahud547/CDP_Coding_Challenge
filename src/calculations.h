/**
 * @file calculations.h
 *
 * @brief Module for holding the functions used for calculating power.
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "packet_constants.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int calc_power(pwr_packet_t * pwr_numbers);

#ifdef __cplusplus
}
#endif

#endif // CALCULATIONS_H
