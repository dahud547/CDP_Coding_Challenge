#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(packet_parser_test_group);
IMPORT_TEST_GROUP(calculations_test_group);
IMPORT_TEST_GROUP(state_handler_test_group);

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
