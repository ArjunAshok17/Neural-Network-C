#ifndef PROPAGATION_H
    #define PROPAGATION_H

    // libraries //
    #include "neural_network.h"
    #include <math.h>

    // structs //
    typedef struct Activation_struct
    {
        int num_nodes; // number of nodes in the layer
        double* active; // activation of neurons
    } ACTIV;

    /* functions */
    // flow //
    void tensor_flow(NN* net, int cur_layer);
    void forward_prop(NN* net);
    void backwards_prop(NN* net, ACTIV* exp_act);

    // helper functions //
    void gradient_step(NODE *n, double exp_val);
    double gauss_error(double x);

    // input/output //
    void normalize_inputs(double* input);
    void input_conversion(NN* net, FILE* sreader);
    void output_conversion(NN* net, FILE* ereader, double* *exp_act);
    
#endif