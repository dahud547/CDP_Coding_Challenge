#include <stdio.h>
#include <errno.h>

int parse_arguments(const int argc, char * argv[], FILE * p_file);

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

    ret_status = parse_arguments(argc, argv, p_bin_file);

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
int parse_arguments(const int argc, char * argv[], FILE * p_file)
{
    int ret_status = 0;
    if (2 == argc)
    {
        p_file = fopen(argv[0], "rb");
        if (NULL == p_file)
        {
            printf("ERR: Invalid File Location\n");
            ret_status = ENODATA;
        }
        else
        {
            printf("File has been read in!\n");
            (void)fclose(p_file);
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
