/**
 * @file packet_parser.c
 *
 * @brief Module for parsing the incoming packets
 */

#include "packet_parser.h"
#include "calculations.h"
#include <stdbool.h>
#include <stdio.h>

static uint32_t prev_pack_modulus = 0u;

uint32_t convert_array_to_uint32(uint8_t * p_array, size_t length);
int check_for_pack_error(packet_type_t pack_type, uint8_t * p_packet);

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
    if (PWR_PACKET_TYPE_BYTE == first_byte_of_pack)
    {
        ret_type = power_pack;
    }
    else if (BATT_PACKET_TYPE_BYTE == first_byte_of_pack)
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
int process_pwr_packet(uint8_t * p_packet_buf, pwr_packet_t * p_out_pack)
{
    int ret_status = -1;
    if((NULL != p_packet_buf) && (NULL != p_out_pack))
    {
        p_out_pack->time_stamp = convert_array_to_uint32(&p_packet_buf[START_OF_TS_LOC],
                                                      TIMESTAMP_NUM_OF_BYTES);

        p_out_pack->volts = convert_array_to_uint32(&p_packet_buf[PWR_START_OF_VOLTS_LOC],
                                                 VOLTS_NUM_OF_BYTES);

        p_out_pack->milliamps = convert_array_to_uint32(&p_packet_buf[PWR_START_OF_MILLIAMP_LOC],
                                                     MILLIAMP_NUM_OF_BYTES);

        p_out_pack->err_check = (uint16_t)p_packet_buf[PWR_START_OF_ERR_CHECK_LOC];

        ret_status = calc_power(p_out_pack);

        if(0 == ret_status)
        {
            ret_status = check_for_pack_error(power_pack, p_packet_buf);
        }
    }
    return ret_status;
}

/**
 * @brief Function for creating a battery status packet from an input buffer
 *
 * @param packet_buf Buffer to be converted
 * @return batt_packet_t Struct with the battery information in it.
 */
int process_batt_packet(uint8_t * p_packet_buf, batt_packet_t * p_out_pack)
{
    int ret_status = -1;

    if((NULL != p_packet_buf) && (NULL != p_out_pack))
    {
        p_out_pack->time_stamp = convert_array_to_uint32(&p_packet_buf[START_OF_TS_LOC],
                                                      TIMESTAMP_NUM_OF_BYTES);

        p_out_pack->batt_status = p_packet_buf[BATT_START_OF_BATT_STATUS_LOC];

        p_out_pack->err_check = (uint16_t)p_packet_buf[BATT_START_OF_ERR_CHECK_LOC];

        ret_status = check_for_pack_error(battery_pack, p_packet_buf);
    }

    return ret_status;
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

/**
 * @brief Helper function to check the error byte for integraty
 *
 * @param pack_type Type of packet being checked
 * @param p_packet pointer to the packet buffer
 * @return int Success = 0
 */
int check_for_pack_error(packet_type_t pack_type, uint8_t * p_packet)
{
    int ret_status = 0;
    uint32_t mod_of_pack = 0;
    bool save_modulus = true;
    switch (pack_type)
    {
    case power_pack:
        mod_of_pack = mod_of_array(p_packet, (SIZE_OF_PWR_PACK - ERR_CHECK_NUM_OF_BYTES));
        if (prev_pack_modulus != p_packet[PWR_START_OF_ERR_CHECK_LOC])
        {
            ret_status = -1;
            printf("ERR: Packet Failed Error Check\n");
        }
        break;
    case battery_pack:
        mod_of_pack = mod_of_array(p_packet, (SIZE_OF_BATT_PACK - ERR_CHECK_NUM_OF_BYTES));
        if (prev_pack_modulus != p_packet[BATT_START_OF_ERR_CHECK_LOC])
        {
            ret_status = -1;
            printf("ERR: Packet Failed Error Check\n");
        }
        break;
    default:
        // Should never be able to call this but should guard for it just in case
        save_modulus = false;
        break;
    }

    if(save_modulus)
    {
        prev_pack_modulus = mod_of_pack;
    }

    return ret_status;
}
