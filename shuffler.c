#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TIMES 20

#ifdef V
#define VERBOSE
#endif

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

#ifdef DEBUG
void print_bin(char a){
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((a << i) & 0x80));
    }
    printf("\n");
}
#endif

int check_bit(char *array, int bit, int char_bits) {
    int index = bit/char_bits;
    int bit_index = bit%char_bits;

    /* Check if index is already set to 1 */
    if (array[index] & (1 << bit_index)) {
        // Already set to 1
        return 0;
    } else {
        // Not yet set to 1
        array[index] |= (1 << bit_index);
        return 1;
    }
}

int main(int argc, char **argv) {
    /* Input argument checking */
    if(argc != 3) {
        error("Please provide two input arguments (number of unique items & number of iterations)");
    }
    char *end_ptr;
    int n = (int)strtol(argv[1], &end_ptr, 10);
    if(*end_ptr != '\0') {
        error("Please ensure input argument is an integer");
    }
    if(n < 2) {
        error("Input argument must be greater than 1");
    }
    long iter = strtol(argv[2], &end_ptr, 10);
    if(*end_ptr != '\0') {
        error("Please ensure input argument is an integer");
    }
    if(iter < 1) {
        error("Input argument must be greater than 0");
    }

    /* Create checking array and counter */
    int char_bits = sizeof(char)*8;
    int array_len = n/char_bits + (n%char_bits!=0);
    char *check = (char*)malloc(array_len);

    #ifdef MEAN
    long mean = 0;
    long remainder = 0;
    #endif

    #ifdef MODE
    short indices = (N_TIMES-1)*n;
    short mode_index;
    /* Initialise a variable for the current mode's index. The mode will be current_mode+n */
    short current_mode = 0;
    /* Create a frequency table from n to N_TIMES*n. Can store a frequency up to 2^(sizeof(int)) */
    int *freq_table = (int*)calloc(indices, sizeof(int));
    #endif

    /* Initialise random number generator */
    srand(time(NULL));
    int rand_num;

    /* Specify stopping point */
    long halt = n*N_TIMES;


    for (int i = 0; i < iter; i++) {
        #ifdef DEBUG
        printf("Iteration %i:\n", i+1);
        #endif
        memset(check, 0, array_len); // must use memset as calloc is not zeroing past the 8th byte

        long counter = n;
        #ifdef DEBUG
        printf("Counter: %li\n", counter);
        #endif
        long total = 0;

        while (counter) {
            rand_num = rand()%n;
            #ifdef DEBUG
            #ifdef VERBOSE
            printf("Num: %i\n", rand_num);
            #endif
            #endif
            counter -= check_bit(check, rand_num, char_bits);
            total++;
            if (total >= halt) { // should never be greater than, but just in case
                printf("\t Failed with %li found\n", n-counter);
                break;
            }
            #ifdef DEBUG
            #ifdef VERBOSE
            for (int i = 0; i < array_len; i++) {
                print_bin(check[i]);
            }
            printf("Counter: %li\n", counter);
            #endif
            #endif
        }

        #ifdef TOTAL_PRINT
        printf("%li ", total);
        #endif

        #ifdef MEAN
        mean += total/iter + remainder/iter;
        remainder = remainder%iter + total%iter;
        #endif

        #ifdef MODE
        mode_index = total-n;
        freq_table[mode_index]++;
        // if (freq_table[mode_index] > freq_table[current_mode]) {
        //     current_mode = mode_index;
        // }
        #endif

        #ifdef DEBUG
        printf("\tTotal: %li\n", total);
        #endif
    }

    free(check);

    #ifdef MODE
    mode_index = 0;
    #ifdef FREQ_TABLE
    printf("Total , Frequency");
    #endif
    
    for (indices--; indices >= 0; indices--) {
        if (freq_table[indices] > freq_table[mode_index]) {
            mode_index = indices;
        }
        #ifdef FREQ_TABLE
        printf("%i , %i\n", indices+n, freq_table[indices]);
        #endif
    }
    printf("Mode random selections: %i\n", mode_index+n);
    #endif

    #ifdef MEAN
    printf("Mean random selections: %.3f\n", mean+remainder/(1.0*iter));
    #endif

    exit(0);
}
