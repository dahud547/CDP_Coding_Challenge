/**
 * @file packet_parser.h
 *
 * @brief Module for parsing the incoming packets
 */

#ifndef COM_IF_H
#define COM_IF_H

#include "packet_constants.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

packet_type_t determine_packet_type(const uint8_t first_byte_of_pack);
pwr_packet_t process_pwr_packet(uint8_t * packet_buf);
batt_packet_t process_batt_packet(uint8_t * packet_buf);

#ifdef __cplusplus
}
#endif

#endif // COM_IF_H
