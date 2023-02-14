/**
 * Program Description
 * This program simulates a neural network using simple integer outputs and simplified backpropagation
*/

/* Libaries */
#include "neural_network.h"
#include "propagation.h"
#include "user_interaction.h"

int main(int argc, char** argv)
{
    // variable handling //
    int num_layers;
    int* nodes = NULL;
    // double learn_rate;
    // double num_iters;
    NN* net = (NN*) calloc(1, sizeof(NN));

    // user input //
    read_argv(argc, argv, &num_layers, &nodes);
    // read_input();

    // setup neural network //
    create_network(net, num_layers, nodes);
    initialize_nodes(net);
    
    // user input //

print_network(net);
printf("FORWARD PROP\n");
forward_prop(net);
print_network(net);

    // end program //
    free_network(net);
    return 0;
}