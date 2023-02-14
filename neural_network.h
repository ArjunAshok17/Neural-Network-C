#ifndef NEURAL_NETWORK_H
    #define NEURAL_NETWORK_H

    // libraries //
    #include <math.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>

    // structs //
    typedef struct Node_struct
    {
        int layer; // layer number
        int node_num; // node number in the layer (top => 0, bottom => nodes[layer - 1] - 1)
        double active; // signal if the node is activated or not
        double* weights; // weight of the node for each connection
    }
    NODE;

    typedef struct Neural_Network_struct
    {
        int num_layers; // number of layers
        int* nodes; // number of nodes per layer
        NODE** network; // 2D-array to position each NODE correctly
    }
    NN;

    /* functions */
    // setup //
    void create_network(NN *net, int num_layers, int* nodes);
    void initialize_nodes(NN *net);

    // operation //
    void print_network(NN* net);
    void free_network(NN *net);

#endif