/**
 * @file packet_parser.h
 *
 * @brief Module for parsing the incoming packets
 */

#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include "packet_constants.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int process_packet(uint8_t * p_packet_buf,
                   size_t length,
                   pwr_packet_t * pwr_out,
                   batt_packet_t * batt_out);

#ifdef __cplusplus
}
#endif

#endif // PACKET_PARSER_H
