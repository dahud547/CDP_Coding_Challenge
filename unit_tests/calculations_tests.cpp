#include "CppUTest/TestHarness.h"

#include "calculations.h"

TEST_GROUP(calculations_test_group)
{
    void setup(void)
    {
    }

    void teardown(void)
    {
    }
};

TEST(calculations_test_group, calc_power_null_pointer_check)
{
    int ret_val = calc_power(NULL);
    CHECK_EQUAL(-1, ret_val);
}

TEST(calculations_test_group, calc_power_successful_pwr_calculation)
{
    pwr_packet_t test_packet = {
        .volts = 20,
        .milliamps = 10,
        .milliwatts = 0
    };
    int ret_val = calc_power(&test_packet);
    CHECK_EQUAL(0, ret_val);
    CHECK_EQUAL(200, test_packet.milliwatts);
}

TEST(calculations_test_group, modulus_tests)
{
    uint8_t test_buff[4] = {0x2,0x2,0x3,0x4};
    uint32_t check_val = 0x02020304u;

    uint32_t expected_modulus = check_val % 256;
    uint32_t func_result = mod_of_array(test_buff, 4);
    CHECK_EQUAL(expected_modulus, func_result);
}
