#include "calculations.h"
#include "packet_constants.h"
#include "packet_parser.h"
#include "state_handler.h"

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

int parse_arguments(const int argc, char * argv[], FILE ** p_file);
void get_pack_from_file(FILE ** p_file, uint8_t * out_buff, const size_t size);

/**
 * @brief Main function of the program
 *
 * @param argc Number of arguments
 * @param argv Pointer to the list of inputed arguments
 * @return int Status of program
 */
int main(int argc, char * argv[])
{
    int ret_status = 0;
    FILE * p_bin_file = NULL;

    ret_status = parse_arguments(argc, argv, &p_bin_file);

    uint8_t packet_buffer[MAX_PACKET_SIZE] = {0};
    pwr_packet_t pwr_pack = {0};
    batt_packet_t batt_pack = {0};
    if (0 == ret_status)
    {
        ///@todo Potentially come back and rethink if we need any reason to
        /// error out of this loop
        while ((0 == feof(p_bin_file)) ) //&& (0 == ret_status))
        {
            packet_buffer[START_OF_PT_LOC] = (uint8_t)fgetc(p_bin_file);
            packet_type_t pack_type = determine_packet_type(packet_buffer[START_OF_PT_LOC]);
            switch (pack_type)
            {
            case power_pack:
                get_pack_from_file(&p_bin_file,
                                   &packet_buffer[START_OF_TS_LOC],
                                   (SIZE_OF_PWR_PACK - PACKET_TYPE_NUM_OF_BYTES));
                ret_status = process_pwr_packet(packet_buffer, &pwr_pack);
                break;
            case battery_pack:
                get_pack_from_file(&p_bin_file,
                                   &packet_buffer[START_OF_TS_LOC],
                                   (SIZE_OF_BATT_PACK - PACKET_TYPE_NUM_OF_BYTES));
                ret_status = process_batt_packet(packet_buffer, &batt_pack);
                break;
            default:
                break;
            }

            if (0 == ret_status)
            {
                ret_status = process_state_and_transitions(pack_type,
                                                           &pwr_pack,
                                                           &batt_pack);
            }
        }
    }

    (void)fclose(p_bin_file);

    return ret_status;
}

/**
 * @brief Function for parsing the inputs to the program
 *
 * @param argc Number of arguments being entered
 * @param argv Array of the arguments
 * @param p_file Output of the file being expected to be passed. Will be NULL if
 *               invalid
 * @return int Return status, 0 for success, error code for failure
 */
int parse_arguments(const int argc, char * argv[], FILE ** p_file)
{
    int ret_status = 0;
    if (2 == argc)
    {
        *p_file = fopen(argv[1], "rt");
        if (NULL == *p_file)
        {
            perror("ERR: Invalid File Location\n");
            ret_status = ENFILE;
        }
    }
    else if (2 > argc)
    {
        printf("ERR: No imput file passed in! ");
        printf("ie: packet_converter /path/to/bin/file \n");
        ret_status = ENODATA;
    }
    else
    {
        printf("ERR: This requires only 1 input bin file ");
        printf("ie: packet_converter /path/to/bin/file \n");
        ret_status = ENFILE;
    }
    return ret_status;
}

/**
 * @brief Get the pack from file object
 *
 * @param p_file Pointer to the file being processed
 * @param out_buff Outputing the data obtained from the file
 * @param size Size of the buffer to output data in
 */
void get_pack_from_file(FILE ** p_file, uint8_t * out_buff, const size_t size)
{
    for (size_t i = 0; size > i; ++i)
    {
        out_buff[i] = (uint8_t)fgetc(*p_file);
    }
}
