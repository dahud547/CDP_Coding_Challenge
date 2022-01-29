#include "calculations.h"
#include "packet_constants.h"
#include "packet_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

int parse_arguments(const int argc, char * argv[], FILE ** p_file);
void get_pack_from_file(FILE ** p_file, uint8_t * out_buff, const size_t size);

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char * argv[])
{
    int ret_status = 0;
    FILE * p_bin_file = NULL;

    ret_status = parse_arguments(argc, argv, &p_bin_file);

    pwr_packet_t pwr_pack = {0};
    batt_packet_t batt_pack = {0};
    while ((0 == feof(p_bin_file)) || (0 == ret_status))
    {
        const uint8_t first_byte_of_pack = (uint8_t)fgetc(p_bin_file);
        packet_type_t pack_type = determine_packet_type(first_byte_of_pack);

        switch (pack_type)
        {
            case power_pack:
            {
                uint8_t temp_buf[SIZE_OF_PWR_PACK] = {0};
                get_pack_from_file(&p_bin_file, temp_buf, SIZE_OF_PWR_PACK);
                pwr_pack = process_pwr_packet(temp_buf);
                ret_status = calc_power(&pwr_pack);
                break;
            }
            case battery_pack:
            {
                uint8_t temp_buf[SIZE_OF_BATT_PACK] = {0};
                get_pack_from_file(&p_bin_file, temp_buf, SIZE_OF_BATT_PACK);
                batt_pack = process_batt_packet(temp_buf);
                break;
            }
            case error_type:
                // Intentional fall-through
            default:
                //printf("Err: Invalid packet type\n");
                ret_status = EPROTO;
                break;
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
 *               invalid.
 * @return int Return status, 0 for success, error code for failure
 */
int parse_arguments(const int argc, char * argv[], FILE ** p_file)
{
    int ret_status = 0;
    if (2 == argc)
    {
        *p_file = fopen(argv[0], "rb");
        if (NULL == *p_file)
        {
            perror("ERR: Invalid File Location\n");
            ret_status = -1;
        }
    }
    else if (2 > argc)
    {
        printf("ERR: No imput file passed in!\n");
        ret_status = ENODATA;
    }
    else
    {
        printf("ERR: This requires only 1 input bin file\n");
        ret_status = -1;
    }
    return ret_status;
}

void get_pack_from_file(FILE ** p_file, uint8_t * out_buff, const size_t size)
{
    for (size_t i = 0; size > i; ++i)
    {
        out_buff[0] = (uint8_t)fgetc(*p_file);
    }
}
