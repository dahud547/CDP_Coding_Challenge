#include "CppUTest/TestHarness.h"

#include "packet_parser.c"

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

TEST(packet_parser_test_group, process_pwr_packet_both_parms_null)
{
    int ret_val = process_pwr_packet(NULL, NULL);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_batt_packet_both_parms_null)
{
    int ret_val = process_batt_packet(NULL, NULL);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_pwr_packet_packet_parm_null)
{
    pwr_packet_t pwr_pack = {0};
    int ret_val = process_pwr_packet(NULL, &pwr_pack);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_batt_packet_packet_parm_null)
{
    batt_packet_t batt_pack = {0};
    int ret_val = process_batt_packet(NULL, &batt_pack);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_pwr_packet_struct_parm_null)
{
    uint8_t test_pack[4] = {0};
    int ret_val = process_pwr_packet(test_pack, NULL);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_batt_packet_struct_parm_null)
{
    uint8_t test_pack[4] = {0};
    int ret_val = process_batt_packet(test_pack, NULL);
    CHECK_EQUAL(-1, ret_val);
}

TEST(packet_parser_test_group, process_pwr_packet_successful_packet)
{
    uint8_t test_buff[SIZE_OF_PWR_PACK] = {0x0, //Packet Type
                                           0x1,0x2,0x3,0x4, //Timestamp
                                           0x0,0x0,0x0,0x4, //volts
                                           0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2, //milliamps
                                           0x10}; //error check
    pwr_packet_t pwr_pack = {0};
    int ret_val = process_pwr_packet(test_buff, &pwr_pack);
    CHECK_EQUAL_ZERO(ret_val);
    CHECK_EQUAL(0x01020304, pwr_pack.time_stamp);
    CHECK_EQUAL(0x00000004, pwr_pack.volts);
    CHECK_EQUAL(0x0000000000000002, pwr_pack.milliamps);
    CHECK_EQUAL(0x10, pwr_pack.err_check);
    CHECK_EQUAL(8, pwr_pack.milliwatts);
}

TEST(packet_parser_test_group, process_batt_packet_successful_packet)
{
    uint8_t test_buff[SIZE_OF_BATT_PACK] = {0x1, //Packet Type
                                            0x1,0x2,0x3,0x4, //Timestamp
                                            0x1, // battery status
                                            0x0C}; // error check
    batt_packet_t batt_pack = {0};
    int ret_val = process_batt_packet(test_buff, &batt_pack);
    CHECK_EQUAL_ZERO(ret_val);
    CHECK_EQUAL(0x01020304,batt_pack.time_stamp);
    CHECK_EQUAL(0x01,batt_pack.batt_status);
    CHECK_EQUAL(0x0C, batt_pack.err_check);
}
