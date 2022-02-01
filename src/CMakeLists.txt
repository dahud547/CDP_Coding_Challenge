include_directories(${PROJECT_SOURCE_DIR})
add_executable(pwr_and_batt_packet_converter main.c packet_parser.c calculations.c state_handler.c)

