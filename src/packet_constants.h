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

#define PWR_PACKET_TYPE_BYTE 0x00u
#define BATT_PACKET_TYPE_BYTE 0x01u
#define START_OF_PT_LOC (0u)
#define START_OF_TS_LOC (START_OF_PT_LOC + PACKET_TYPE_NUM_OF_BYTES)
#define PWR_START_OF_VOLTS_LOC (START_OF_TS_LOC + TIMESTAMP_NUM_OF_BYTES)
#define PWR_START_OF_MILLIAMP_LOC (PWR_START_OF_VOLTS_LOC + VOLTS_NUM_OF_BYTES)
#define PWR_START_OF_ERR_CHECK_LOC (PWR_START_OF_MILLIAMP_LOC + MILLIAMP_NUM_OF_BYTES)
#define BATT_START_OF_BATT_STATUS_LOC (START_OF_TS_LOC + TIMESTAMP_NUM_OF_BYTES)
#define BATT_START_OF_ERR_CHECK_LOC (BATT_START_OF_BATT_STATUS_LOC + BATT_STAT_NUM_OF_BYTES)

/// Structure for holding the data related to the power packet
typedef struct pwr_packet
{
    uint32_t time_stamp; /// Timestamp of the packet recieved in milliseconds
    uint32_t volts; /// Volts of the power packet recieved
    uint64_t milliamps; /// Milliamps of the power packet recieved
    uint8_t err_check; /// Error check value of the packet
    uint64_t milliwatts; /// The calculated power from the volts * milliamps
} pwr_packet_t;

/// Structure for holding the data related to the battery packet
typedef struct batt_packet
{
    uint32_t time_stamp; /// Timestamp of the packet recieved in milliseconds
    uint8_t batt_status; /// Status of the battery, 0-3 for VLOW,LOW,MED,HIGH
    uint8_t err_check; /// Error check value of the packet
} batt_packet_t;

/// Typedef Enum to indicate which type of packet we are working with
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
