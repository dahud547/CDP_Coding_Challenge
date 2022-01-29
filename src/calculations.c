/**
 * @file calculations.c
 *
 * @brief Module for holding the functions used for calculating power.
 */
#include "calculations.h"
#include <stddef.h>

/**
 * @brief Function for calculating the power from the voltage and amperage given
 *
 * @param pwr_numbers Struct holding the power information
 * @return int Success = 0, failure = -1
 */
int calc_power(pwr_packet_t * pwr_numbers)
{
    int ret_status = -1;
    if (NULL != pwr_numbers)
    {
        pwr_numbers->milliwatts = (uint64_t)pwr_numbers->volts * pwr_numbers->milliamps;
        ret_status = 0;
    }

    return ret_status;
}
