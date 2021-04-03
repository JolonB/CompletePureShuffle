#include <stdio.h>
#include <stdlib.h>

#define N_TIMES 20

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int main(int argc, char **argv) {
    /* Input argument checking */
    if(argc != 2) {
        error("Please provide one input arguments (number of unique items)");
    }
    char *end_ptr;
    int n = (int)strtol(argv[1], &end_ptr, 10);
    if(*end_ptr != '\0') {
        error("Please ensure input argument is an integer");
    }
    if(n < 2) {
        error("Input argument must be greater than 1");
    }

    #ifdef MEAN
    float mean = 0;
    for (int i = 1; i <= n; i++) {
        mean += 1./i;
    }
    mean *= n;

    printf("Mean random selections: %.3f\n", mean);
    #endif


    exit(0);
}
