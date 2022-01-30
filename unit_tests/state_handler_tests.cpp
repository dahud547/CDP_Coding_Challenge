#include "CppUTest/TestHarness.h"

#include "state_handler.c"

TEST_GROUP(state_handler_test_group)
{
    void setup(void)
    {
        inital_ts_ms = 0;
    }

    void teardown(void)
    {
    }
};

TEST(state_handler_test_group, set_initial_timestamp_success)
{
    set_initial_timestamp(1000);
    CHECK_EQUAL(1000, inital_ts_ms);
}

TEST(state_handler_test_group, time_check_greater_10ms)
{
    bool ret_val = time_check(0u, 11u);
    CHECK_TRUE(ret_val);
}

TEST(state_handler_test_group, time_check_less_than_10ms)
{
    bool ret_val = time_check(1u, 10u);
    CHECK_FALSE(ret_val);
}

TEST(state_handler_test_group, time_check_greater_prev_ts)
{
    bool ret_val = time_check(11u, 10u);
    CHECK_FALSE(ret_val);
}

TEST(state_handler_test_group, calc_time_from_start_correctly)
{
    uint32_t ret_val = calc_time_from_start_ms_to_sec(1000);
    CHECK_EQUAL(1, ret_val);
}

TEST(state_handler_test_group, calc_time_from_start_floors_correctly)
{
    uint32_t ret_val = calc_time_from_start_ms_to_sec(1500);
    CHECK_EQUAL(1, ret_val);
}

TEST(state_handler_test_group, determine_state_state_0_bounds)
{
    pwr_packet_t pwr = {0};
    states_t ret_val = NUM_OF_STATES;
    for (uint32_t i = 0; STATE_0_UPPER_BOUNDS >= i; ++i)
    {
        pwr.milliwatts = i;
        ret_val = determine_state(&pwr);
        CHECK_EQUAL(STATE_0, ret_val);
    }
    ++pwr.milliwatts;
    ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
}

TEST(state_handler_test_group, determine_state_state_1_bounds)
{
    pwr_packet_t pwr = {0};
    pwr.milliwatts = STATE_1_LOWER_BOUNDS - 1u;
    states_t ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
    for (uint32_t i = STATE_1_LOWER_BOUNDS; STATE_1_UPPER_BOUNDS >= i; ++i)
    {
        pwr.milliwatts = i;
        ret_val = determine_state(&pwr);
        CHECK_EQUAL(STATE_1, ret_val);
    }
    ++pwr.milliwatts;
    ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
}

TEST(state_handler_test_group, determine_state_state_2_bounds)
{
    pwr_packet_t pwr = {0};
    pwr.milliwatts = STATE_2_LOWER_BOUNDS - 1u;
    states_t ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
    for (uint32_t i = STATE_2_LOWER_BOUNDS; STATE_2_UPPER_BOUNDS >= i; ++i)
    {
        pwr.milliwatts = i;
        ret_val = determine_state(&pwr);
        CHECK_EQUAL(STATE_2, ret_val);
    }
    ++pwr.milliwatts;
    ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
}

TEST(state_handler_test_group, determine_state_state_3_bounds)
{
    pwr_packet_t pwr = {0};
    pwr.milliwatts = STATE_3_LOWER_BOUNDS - 1u;
    states_t ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
    for (uint32_t i = STATE_3_LOWER_BOUNDS; STATE_3_UPPER_BOUNDS >= i; ++i)
    {
        pwr.milliwatts = i;
        ret_val = determine_state(&pwr);
        CHECK_EQUAL(STATE_3, ret_val);
    }
    ++pwr.milliwatts;
    ret_val = determine_state(&pwr);
    CHECK_EQUAL(NUM_OF_STATES, ret_val);
}

TEST(state_handler_test_group, process_st_invalid_pack_type)
{
    pwr_packet_t pwr = {0};
    batt_packet_t batt = {0};
    int ret_val = process_state_and_transitions(error_type, &pwr, &batt);
    CHECK_EQUAL(-1, ret_val);
}

TEST(state_handler_test_group, process_st_pwr_null_check)
{
    batt_packet_t batt = {0};
    int ret_val = process_state_and_transitions(power_pack, NULL, &batt);
    CHECK_EQUAL(-1, ret_val);
}

TEST(state_handler_test_group, process_st_batt_null_check)
{
    pwr_packet_t pwr = {0};
    int ret_val = process_state_and_transitions(power_pack, &pwr, NULL);
    CHECK_EQUAL(-1, ret_val);
}

///@todo add more tests
