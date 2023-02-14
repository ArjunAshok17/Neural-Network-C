#ifndef USER_INTERACTION_H
    #define USER_INTERACTION_H

    // libraries //
    #include <ctype.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    /* functions */
    // command line //
    void read_argv(int argc, char** argv, int *num_layers, int* *nodes);
    void default_values(int *num_layers, int* *nodes);

    // user io //
    void print_error(int error_code);

    // file io //


#endif