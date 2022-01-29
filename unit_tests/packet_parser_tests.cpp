#include "CppUTest/TestHarness.h"

#include "packet_parser.h"

TEST_GROUP(packet_parser_test_group)
{
    void setup(void)
    {
    }

    void teardown(void)
    {
    }
};

TEST(packet_parser_test_group, check_packet_type_fail)
{
    packet_type_t ret_val = determine_packet_type(0x02);
    CHECK_EQUAL(error_type, ret_val);
}

TEST(packet_parser_test_group, check_packet_type_pwr)
{
    packet_type_t ret_val = determine_packet_type(0x00);
    CHECK_EQUAL(power_pack, ret_val);
}

TEST(packet_parser_test_group, check_packet_type_batt)
{
    packet_type_t ret_val = determine_packet_type(0x01);
    CHECK_EQUAL(battery_pack, ret_val);
}

TEST(packet_parser_test_group, process_pwr_packet_null_check)
{
    pwr_packet_t ret_val = process_pwr_packet(NULL);
    CHECK_EQUAL_ZERO(ret_val.time_stamp);
    CHECK_EQUAL_ZERO(ret_val.volts);
    CHECK_EQUAL_ZERO(ret_val.milliamps);
    CHECK_EQUAL_ZERO(ret_val.err_check);
    CHECK_EQUAL_ZERO(ret_val.milliwatts);
}

TEST(packet_parser_test_group, process_batt_packet_null_check)
{
    batt_packet_t ret_val = process_batt_packet(NULL);
    CHECK_EQUAL_ZERO(ret_val.time_stamp);
    CHECK_EQUAL_ZERO(ret_val.batt_status);
    CHECK_EQUAL_ZERO(ret_val.err_check);
}

TEST(packet_parser_test_group, process_pwr_packet_successful_packet)
{
    uint8_t test_buff[SIZE_OF_PWR_PACK] = {0x1,0x2,0x3,0x4, //Timestamp
                                           0x0,0x0,0x0,0x4, //volts
                                           0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2, //milliamps
                                           0x1}; //error check
    pwr_packet_t ret_val = process_pwr_packet(test_buff);
    CHECK_EQUAL(0x01020304, ret_val.time_stamp);
    CHECK_EQUAL(0x00000004, ret_val.volts);
    CHECK_EQUAL(0x0000000000000002, ret_val.milliamps);
    CHECK_EQUAL(0x01, ret_val.err_check);
    CHECK_EQUAL_ZERO(ret_val.milliwatts);
}

TEST(packet_parser_test_group, process_batt_packet_successful_packet)
{
    uint8_t test_buff[SIZE_OF_BATT_PACK] = {0x1,0x2,0x3,0x4, //Timestamp
                                            0x1, // battery status
                                            0x1}; // error check
    batt_packet_t ret_val = process_batt_packet(test_buff);
    CHECK_EQUAL(0x01020304,ret_val.time_stamp);
    CHECK_EQUAL(0x01,ret_val.batt_status);
    CHECK_EQUAL(0x01,ret_val.err_check);
}
