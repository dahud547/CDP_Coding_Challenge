/**
 * @file packet_parser.c
 *
 * @brief Module for parsing the incoming packets
 */

#include "packet_parser.h"
#include <stddef.h>

#define START_OF_TS_LOC (0u)
#define PWR_START_OF_VOLTS_LOC (START_OF_TS_LOC + TIMESTAMP_NUM_OF_BYTES)
#define PWR_START_OF_MILLIAMP_LOC (PWR_START_OF_VOLTS_LOC + VOLTS_NUM_OF_BYTES)
#define PWR_START_OF_ERR_CHECK_LOC (PWR_START_OF_MILLIAMP_LOC + MILLIAMP_NUM_OF_BYTES)
#define BATT_START_OF_BATT_STATUS_LOC (START_OF_TS_LOC + TIMESTAMP_NUM_OF_BYTES)
#define BATT_START_OF_ERR_CHECK_LOC (BATT_START_OF_BATT_STATUS_LOC + BATT_STAT_NUM_OF_BYTES)

uint32_t convert_array_to_uint32(uint8_t * p_array, size_t length);

/**
 * @brief Function for determining the type of the incoming packet
 *
 * @param first_byte_of_pack 1st byte of the packet
 * @return packet_type_t Type of packet, will return the Enum error_type if it's
 *                       an invalid packet type.
 */
packet_type_t determine_packet_type(const uint8_t first_byte_of_pack)
{
    packet_type_t ret_type = error_type;
    if (0u == first_byte_of_pack)
    {
        ret_type = power_pack;
    }
    else if (1u == first_byte_of_pack)
    {
        ret_type = battery_pack;
    }
    else
    {
        // Error so do nothing
    }

    return ret_type;
}

/**
 * @brief Function for creating a power packet from an input buffer
 *
 * @param packet_buf Buffer to be converted
 * @return pwr_packet_t Struct with the power information in it
 */
pwr_packet_t process_pwr_packet(uint8_t * packet_buf)
{
    pwr_packet_t ret_pack = {0};
    if( NULL != packet_buf)
    {
        ret_pack.time_stamp = convert_array_to_uint32(&packet_buf[START_OF_TS_LOC],
                                                      TIMESTAMP_NUM_OF_BYTES);

        ret_pack.volts = convert_array_to_uint32(&packet_buf[PWR_START_OF_VOLTS_LOC],
                                                 VOLTS_NUM_OF_BYTES);

        ret_pack.milliamps = convert_array_to_uint32(&packet_buf[PWR_START_OF_MILLIAMP_LOC],
                                                     MILLIAMP_NUM_OF_BYTES);

        ret_pack.err_check = packet_buf[PWR_START_OF_ERR_CHECK_LOC];
    }
    return ret_pack;
}

/**
 * @brief Function for creating a battery status packet from an input buffer
 *
 * @param packet_buf Buffer to be converted
 * @return batt_packet_t Struct with the battery information in it.
 */
batt_packet_t process_batt_packet(uint8_t * packet_buf)
{
    batt_packet_t ret_pack = {0};

    if( NULL != packet_buf)
    {
        ret_pack.time_stamp = convert_array_to_uint32(&packet_buf[START_OF_TS_LOC],
                                                      TIMESTAMP_NUM_OF_BYTES);

        ret_pack.batt_status = packet_buf[BATT_START_OF_BATT_STATUS_LOC];

        ret_pack.err_check = packet_buf[BATT_START_OF_ERR_CHECK_LOC];
    }

    return ret_pack;
}

/**
 * @brief Function for converting an uint8_t array to an uint32_t
 *
 * @todo assert that the length is <=4 bytes
 *
 * @param p_array Array to be converted
 * @param length length of the array in bytes
 * @return uint32_t
 */
uint32_t convert_array_to_uint32(uint8_t * p_array, size_t length)
{
    uint32_t ret_val = 0;
    for (size_t i = 0u; length > i; ++i)
    {
        ret_val <<= 8u;
        ret_val += p_array[i];
    }

    return ret_val;
}
