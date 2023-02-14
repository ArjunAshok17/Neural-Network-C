/**
 * Library Description
 * This helper file defines methods for conductin the flow of information through each node-layer,
 * both forwards for generating output and backwards for correcting error
*/

#include "neural_network.h"
#include "propagation.h"

/**
 * Conducts a single flow of activation from init_layer to the next layer; assumes network[i][nodes[i]]
 *      is a bias node for hidden layers
 * @param net: network to conduct one flow from
 * @param cur_layer: the layer whose activation is being considered
 * @modifies: net
 * @returns nothing
*/
void tensor_flow(NN* net, int cur_layer)
{
    // variable handling //
    int num_nodes = net->nodes[cur_layer];
    double* active_sum = (double*) calloc(num_nodes, sizeof(double));
    NODE* cur_node = NULL;

    // sum connection weights //
    for (int i = 0, nc = net->nodes[cur_layer - 1]; i < num_nodes; i++)
    {   
        // all connections to cur_node //
        for (int j = 0; j < nc; j++)
        {
            cur_node = &(net->network[cur_layer - 1][j]);
            active_sum[i] += cur_node->weights[i] * cur_node->active;
        }
        
        // add bias weight //
        cur_node = &(net->network[cur_layer - 1][nc]);
        active_sum[i] += active_sum[i] += cur_node->weights[i] * cur_node->active;
 
        // activation function //
        active_sum[i] = gauss_error(active_sum[i]);
    
        // map activation //
        net->network[cur_layer][i].active = active_sum[i];
    }

    // end function //
    free(active_sum);
    return;
}

/**
 * Conducts a flow through the entire network from input layer till the output
 * @param net: network to propagate through
 * @modifies: net
 * @returns nothing
 * 
*/
void forward_prop(NN* net)
{
    // file io //
// FILE* sreader = NULL;
// sreader = fopen("", "r"); // start reader, inputs

    // convert input //
// input_conversion(net, sreader);

    // forward prop //
    for (int i = 1, nl = net->num_layers; i < nl; i++)
    {
        // conduct flow //
        tensor_flow(net, i);

    }

    // end function //
// fclose();
    return;
}

/**
 * Conducts a series of backwards propagation through the entire network
 * @param net: neural network to conduct propagation on
 * @param exp_act: expected activation in the output layer neurons
 * @modifies: net
 * @returns nothing
*/
void backwards_prop(NN* net, ACTIV* exp_act)
{
    return;
}

/**
 * Conducts a step of gradient descent on the node
 * @param n: node to evaluate
 * @param exp_val: expected value to calculate error with
 * @modifies: n
 * @returns nothing
*/
void gradient_step(NODE *n, double exp_val)
{

    // end function //
    return;
}

/**
 * Calculates the GELU function at the value specified
 * @param x: x-value to calculate the function at
 * @modifies: nothing
 * @returns: GELU(x)
*/
double gauss_error(double x)
{
    return (0.5 * x) * (1 + tanh(M_SQRT2 * M_2_SQRTPI / 2) * (x + 0.044715 * x * x * x));
}

/**
 * Normalizes the input array using basic normalization to ensure faster convergence for Gradient Descent
 * @param input: input values to normalize
 * @modifies: input
 * @returns nothing
*/
void normalize_inputs_basic(ACTIV* input)
{
    // variable declaration //
    double min = input->active[0], max = min;
    double num;
    double range;
    int l = input->num_nodes;

    // find range //
    for (int i = 0; i < l; i++)
    {
        num = input->active[i];
        min = num < min ? num : min;
        max = num > max ? num : max;
    }

    range = max - min;

    // normalize inputs //
    for (int i = 0; i < l; i++)
    {
        input->active[i] = (input->active[i] - min) / range;
    }

    // end function //
    return;
}

/**
 * Normalizes the input array using z-score normalization to ensure faster convergence for Gradient Descent
 * @param input: input values to normalize
 * @modifies: input
 * @returns nothing
*/
void normalize_inputs_zscore(ACTIV* input)
{
    // variable handling //
    double sum = 0, mean;
    double var = 0, dev;
    int l = input->num_nodes;

    // calculate mean //
    for (int i = 0; i < l; i++)
    {
        sum += input->active[i];
    }
    mean = ((double) sum) / l;

    // calculate variance //
    for (int i = 0; i < l; i++)
    {
        var += (input->active[i] - mean) * (input->active[i] - mean);
    }
    var /= l;

    // calculate standard deviation //
    dev = sqrt(var);

    // replace input with z-score values //
    for (int i = 0; i < l; i++)
    {
        input->active[i] = (input->active[i] - mean) / dev;
    }

    // end function //
    return;
}

// void input_conversion(NN* net, FILE* sreader);
// void output_conversion(NN* net, FILE* ereader, double* *exp_act);
