/**
 * @file state_handler.c
 *
 * @brief Source file of the module for handling any state related functions.
 */
#include "state_handler.h"
#include <stdbool.h>
#include <stdio.h>

#define STATE_0_UPPER_BOUNDS 200u
#define STATE_1_LOWER_BOUNDS 300u
#define STATE_1_UPPER_BOUNDS 450u
#define STATE_2_LOWER_BOUNDS 550u
#define STATE_2_UPPER_BOUNDS 650u
#define STATE_3_LOWER_BOUNDS 800u
#define STATE_3_UPPER_BOUNDS 1200u

typedef enum
{
    /// Initial State for Power reading, 0 to 200 mW
    STATE_0 = 0,
    /// 1st State for Power reading, 300 to 450 mW
    STATE_1,
    /// 2nd State for Power reading, 550 to 650 mW
    STATE_2,
    /// 2nd State for Power reading, 800 to 1200 mW
    STATE_3,
    /// Number of total states
    NUM_OF_STATES
} states_t;

const char * batt_states[4] = {"VLOW", "LOW", "MED", "HIGH"};
uint32_t calc_time_from_start_ms_to_sec(uint32_t current_ts_ms);
states_t determine_state(pwr_packet_t const * const pwr);
void set_initial_timestamp(const uint32_t ts_ms);
bool time_check(uint32_t prev_ts_ms, uint32_t current_ts_ms);

static uint32_t inital_ts_ms = 0;

/**
 * @brief Function for processing the states of either a power or battery state
 *
 * @param pack_type Type of packet being processed
 * @param pwr Pointer to the struct that holds the power information
 * @param batt Pointer to the struct that holds the battery information
 * @return int 0 == Success
 */
int process_state_and_transitions(packet_type_t pack_type,
                                  pwr_packet_t const * const pwr,
                                  batt_packet_t const * const batt)
{
    int ret_status = 0;
    static uint32_t prev_ts_ms = 0;
    static states_t prev_state = STATE_0;
    static bool init_intial_ts = true;
    if ((NULL == pwr) || (NULL == batt))
    {
        ret_status = -1;
    }
    else
    {
        switch (pack_type)
        {
            case power_pack:
            {
                if (init_intial_ts)
                {
                    set_initial_timestamp(pwr->time_stamp);
                    init_intial_ts = false;
                }
                states_t current_state = determine_state(pwr);
                if (current_state != prev_state)
                {
                    if(time_check(prev_ts_ms, pwr->time_stamp))
                    {
                        printf("S;%u;%u-%u\n",
                               calc_time_from_start_ms_to_sec(pwr->time_stamp),
                               prev_state,
                               current_state);
                    }
                }
                prev_state = current_state;
                break;
            }
            case battery_pack:
            {
                if (init_intial_ts)
                {
                    set_initial_timestamp(batt->time_stamp);
                    init_intial_ts = false;
                }
                printf("B;%u;%s\n",
                       calc_time_from_start_ms_to_sec(batt->time_stamp),
                       batt_states[batt->batt_status]);
                break;
            }
            default:
            {
                ret_status = -1;
                break;
            }
        }
    }

    return ret_status;
}

/**
 * @brief Function for calculating the time since the start of the program
 *
 * @param current_ts_ms Current timestamp in milliseconds
 * @return uint32_t Time from start of program in seconds
 */
uint32_t calc_time_from_start_ms_to_sec(uint32_t current_ts_ms)
{
    uint32_t ts_ms = (current_ts_ms - inital_ts_ms);
    return (ts_ms / 1000);
}

/**
 * @brief Function for determining the state from power
 *
 * @param pwr Pointer to the struct that holds the power information
 * @return states_t Current state, returns NUM_OF_STATES if invalid
 */
states_t determine_state(pwr_packet_t const * const pwr)
{
    states_t ret_state = NUM_OF_STATES;
    if (STATE_0_UPPER_BOUNDS >= pwr->milliwatts)
    {
        ret_state = STATE_0;
    }
    else if ((STATE_1_LOWER_BOUNDS <= pwr->milliwatts)
            && (STATE_1_UPPER_BOUNDS >= pwr->milliwatts))
    {
        ret_state = STATE_1;
    }
    else if ((STATE_2_LOWER_BOUNDS <= pwr->milliwatts)
            && (STATE_2_UPPER_BOUNDS >= pwr->milliwatts))
    {
        ret_state = STATE_2;
    }
    else if ((STATE_3_LOWER_BOUNDS <= pwr->milliwatts)
            && (STATE_3_UPPER_BOUNDS >= pwr->milliwatts))
    {
        ret_state = STATE_3;
    }
    else
    {
        //do nothing
    }

    return ret_state;
}

/**
 * @brief Set the initial timestamp object
 *
 * @param ts Initial timestampt to be saved in milliseconds
 */
void set_initial_timestamp(const uint32_t ts_ms)
{
    inital_ts_ms = ts_ms;
}

/**
 * @brief Function to check if 2 timestamps are greater than 10 ms apart
 *
 * @todo There is probably a better way to handle an uint32_t overflow or
 *       underflow situation
 *
 * @param prev_ts_ms Previous timestamp
 * @param current_ts_ms Current timestamp
 * @return true If (current - prev) > 10ms
 * @return false If (current - prev) < 10ms
 */
bool time_check(uint32_t prev_ts_ms, uint32_t current_ts_ms)
{
    bool greater_than_10 = false;

    if (prev_ts_ms < current_ts_ms)
    {
        if (10u <= (current_ts_ms - prev_ts_ms))
        {
            greater_than_10 = true;
        }
    }

    return greater_than_10;
}
