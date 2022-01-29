/**
 * @file calculations.c
 *
 * @brief Module for holding the functions used for calculating power.
 */
#include "calculations.h"

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

/**
 * @brief Function for taking the modulus of an array
 *
 * @param p_array Array to be used
 * @param length Length of that array
 * @return uint32_t Modulus of the array
 */
uint32_t mod_of_array(uint8_t * p_array, size_t length)
{
    uint32_t ret_mod = 0;
    for (size_t i = 0; length > i; ++i)
    {
        ret_mod = ((UINT8_MAX + 1ULL)*ret_mod + p_array[i]);
    }
    ret_mod %= 256;
    return ret_mod;
}
