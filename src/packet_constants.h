/**
 * @file packet_constants.h
 *
 * @brief Header for information about packets like type and constants
 */

#ifndef PACKET_CONSTANTS_H
#define PACKET_CONSTANTS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PACKET_TYPE_NUM_OF_BYTES 1u
#define TIMESTAMP_NUM_OF_BYTES 4u
#define VOLTS_NUM_OF_BYTES 4u
#define MILLIAMP_NUM_OF_BYTES 8u
#define ERR_CHECK_NUM_OF_BYTES 1u
#define BATT_STAT_NUM_OF_BYTES 1u

#define SIZE_OF_PWR_PACK ( PACKET_TYPE_NUM_OF_BYTES \
                          + TIMESTAMP_NUM_OF_BYTES \
                          + VOLTS_NUM_OF_BYTES \
                          + MILLIAMP_NUM_OF_BYTES \
                          + ERR_CHECK_NUM_OF_BYTES)

#define SIZE_OF_BATT_PACK (PACKET_TYPE_NUM_OF_BYTES \
                           + TIMESTAMP_NUM_OF_BYTES \
                           + BATT_STAT_NUM_OF_BYTES \
                           + ERR_CHECK_NUM_OF_BYTES)

#define MAX_PACKET_SIZE ((SIZE_OF_PWR_PACK > SIZE_OF_BATT_PACK) ? \
                          SIZE_OF_PWR_PACK : SIZE_OF_BATT_PACK)

typedef struct pwr_packet
{
    uint32_t time_stamp;
    uint32_t volts;
    uint64_t milliamps;
    uint32_t err_check;
    uint64_t milliwatts;
} pwr_packet_t;

typedef struct batt_packet
{
    uint32_t time_stamp;
    uint8_t batt_status;
    uint32_t err_check;
} batt_packet_t;

typedef enum
{
    power_pack = 0,
    battery_pack,
    error_type,
    num_of_types
} packet_type_t;

#ifdef __cplusplus
}
#endif

#endif // PACKET_CONSTANTS_H
