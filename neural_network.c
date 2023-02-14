/**
 * Library Description
 * This helper file defines useful functions & structures for creating and operating on a neural network
*/

#include "neural_network.h"

/**
 * Initializes NN & allocates memory for the neural network structure; frees nodes
 * @param net: pointer to the neural net to create
 * @param num_layers: number of layers the network should have
 * @param nodes: number of nodes per layer
 * @modifies: net
 * @return nothing
*/
void create_network(NN *net, int num_layers, int* nodes)
{
    // update information //
    net->num_layers = num_layers;

    net->nodes = (int*) calloc(num_layers, sizeof(int));
    for (int i = 0; i < num_layers; i++)
    {
        net->nodes[i] = nodes[i];
    }

    // allocate memory //
    net->network = (NODE**) calloc(num_layers, sizeof(NODE*));

    for (int i = 0; i < num_layers; i++)
    {
        if (i == num_layers - 1)
        {
            net->network[i] = (NODE*) calloc(nodes[i], sizeof(NODE));
        }
        else
        {
            net->network[i] = (NODE*) calloc(nodes[i] + 1, sizeof(NODE));
        }
    }

    // end function //
    free(nodes);
    return;
}

/**
 * Sets the weights & other information for every node in the network
 * @param net: network to initialize
 * @modifies: net
 * @returns nothing
*/
void initialize_nodes(NN *net)
{
    // variable handling //
    srand(time(NULL));
    const int UPPER_BOUND = 1789;
    int nl = net->num_layers;
    int* nodes = net->nodes;

    // randomly initialize //
    // non-output layers //
    for (int i = 0, nc, num_connects; i < nl - 1; i++)
    {
        nc = nodes[i];
        num_connects = nodes[i + 1];

        for (int j = 0; j <= nc; j++)
        {
            // create node //
            net->network[i][j].layer = i;
            net->network[i][j].node_num = j;
            net->network[i][j].active = j == nc ? 1.0 : 0;

            // connection weights //
            net->network[i][j].weights = (double*) calloc(num_connects, sizeof(double));
            for (int k = 0; k < num_connects; k++)
            {
                net->network[i][j].weights[k] = ((rand() % UPPER_BOUND) * (-2 * (rand() % 2) + 1)) / (1000.0);
            }
        }
    }

    // create output nodes //
    for (int i = 0, layer = net->num_layers - 1, nc = nodes[layer]; i < nc; i++)
    {
        // create node //
        net->network[layer][i].layer = layer;
        net->network[layer][i].node_num = i;
        net->network[layer][i].active = 0;

        // connection weights //
        net->network[layer][i].weights = NULL;
    }

    // end function //
    return;
}

/**
 * Prints a visual representation of the neural network
 * @param net: pointer to the neural network to print
 * @modifies: nothing
 * @returns nothing
*/
void print_network(NN* net)
{
    // variable handling //
    int nl = net->num_layers;
    // int max_node_count = -1;

    // for each layer //
    for (int i = 0, nc; i < nl; i++)
    {
        nc = net->nodes[i];

        // for each node //
        for (int j = 0; j < nc; j++)
        {
            printf("[(%i, %i) :: %.3lf]\t", i, j, net->network[i][j].active);
        }

        // bias node //
        if (i != nl - 1)
        {
            printf("[(%i, %i) :: %.3lf]\t", i, nc, net->network[i][nc].active);
        }
        printf("\n");
    }

    // end function //
    return;
}

/**
 * Frees any memory allocated for the neural network
 * @param net: network whose memory needs to be freed
 * @modifies: net
 * @returns nothing
*/
void free_network(NN *net)
{
    // free network //
    for (int i = 0, nl = net->num_layers - 1; i < nl; i++)
    {
        // free network layers //
        for (int j = 0, nc = net->nodes[i]; j < nc; j++)
        {
            // free connection weights //
            free(net->network[i][j].weights);
            net->network[i][j].weights = NULL;
        }
        
        free(net->network[i]);
        net->network[i] = NULL;
    }

    free(net->network);
    net->network = NULL;

    // free node count //
    free(net->nodes);
    net->nodes = NULL;

    // free NN //
    free(net);
    net = NULL;

    // end function //
    return;
}