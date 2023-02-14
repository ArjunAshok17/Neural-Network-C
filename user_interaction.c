/**
 * Library Description
 * This library defines functions useful for user & file io
*/

#include "user_interaction.h"

/**
 * Validates & parses the command-line arguments to determine neural-network dimensions
 * @param argv: vector of command-line args
 * @param num_layers: pointer to number of layers
 * @param nodes: pointer to the number of nodes for each layer (0 -> input layer, num_layers - 1 -> output layer)
 * @modifies: num_layers, nodes
 * @returns nothing
*/
void read_argv(int argc, char** argv, int *num_layers, int* *nodes)
{
    // variable handling //
    char whitespace;

    // check number of arguments 1 //
    if (argc < 2)
    {
        // default values //
        print_error(1);
        default_values(num_layers, nodes);

        return;
    }

    // get number of layers //
    sscanf(argv[1], " %i%c", num_layers, &whitespace);

    if (whitespace != '\0' || *num_layers < 2)
    {
        // default values //
        print_error(2);
        default_values(num_layers, nodes);

        return;
    }

    // check number of arguments 2 //
    if (argc != *num_layers + 2)
    {
        // default values //
        print_error(1);
        default_values(num_layers, nodes);

        return;
    }

    // allocate node counts //
    (*nodes) = (int*) calloc(*num_layers, sizeof(int));

    // read node counts //
    for (int i = 2, end = *num_layers + 2, count; i < end; i++)
    {
        // read input //
        sscanf(argv[i], " %i%c", &count, &whitespace);

        // check validity //
        if (whitespace != '\0' || count <= 0)
        {
            // default values //
            print_error(2);
            default_values(num_layers, nodes);

            return;
        }

        // append to node counts //
        (*nodes)[i - 2] = count;
    }

    // end function //
    return;
}

/**
 * Sets the neural network to the default structure (30 x 40 x 40 x 30)
 * @param num_layers: pointer to number of layers
 * @param nodes: node
*/
void default_values(int *num_layers, int* *nodes)
{
    // layers //
    *num_layers = 4;

    // nodes //
    (*nodes) = (int*) calloc(4, sizeof(int));
    (*nodes)[0] = 30;
    (*nodes)[1] = 40;
    (*nodes)[2] = 40;
    (*nodes)[3] = 30;

    // end function //
    return;
}

/**
 * Prints the corresponding error message for each error code:
 * 1 -> incorrect number of cl-args; 2 -> non-int cl-args; 3 ->
 * 
 * @param error_code: the error message to print
 * @modifies: nothing
 * @returns nothing
*/
void print_error(int error_code)
{
    // route error code //
    switch (error_code)
    {
        case 1:
            printf("ERROR 1 :: Incorrect number of arguments ::\n");
            printf("Correct Usage: ./neural_network.out num_layers layer_1_nodes layer_2_nodes . . .\n");
            printf("Defaulting to 30 x 40 x 40 x 30\n");
            break;
        
        case 2:
            printf("ERROR 2 :; Non-valid/non-integer arguments ::\n");
            printf("Correct Usage: ./neural_network.out num_layers layer_1_nodes layer_2_nodes . . .\n");
            printf("Defaulting to 30 x 40 x 40 x 30\n");
            break;
    }
}