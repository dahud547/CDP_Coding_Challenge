/**
 * @file packet_parser.h
 *
 * @brief Header for the module for parsing the incoming packet data
 */

#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include "packet_constants.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

packet_type_t determine_packet_type(const uint8_t first_byte_of_pack);
int process_pwr_packet(uint8_t const * const p_packet_buf,
                       pwr_packet_t * const p_out_pack);
int process_batt_packet(uint8_t const * const p_packet_buf,
                        batt_packet_t * const p_out_pack);

#ifdef __cplusplus
}
#endif

#endif // PACKET_PARSER_H
