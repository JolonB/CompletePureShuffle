#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TIMES 20

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
    if(argc < 3) {
        error("Please provide two input arguments (number of unique items & number of iterations)");
    }
    char *end_ptr;
    long n = strtol(argv[1], &end_ptr, 10);
    if(*end_ptr != '\0') {
        error("Please ensure input argument is an integer");
    }
    if(n <= 2) {
        error("Input argument must be greater than 2");
    }
    long iter = strtol(argv[2], &end_ptr, 10);
    if(*end_ptr != '\0') {
        error("Please ensure input argument is an integer");
    }
    if(iter < 1) {
        error("Input argument must be greater than 0");
    }

    /* Create checking array and counter */
    char *check;
    int char_bits = sizeof(char)*8;
    int array_len = n/char_bits + (n%char_bits!=0);

    /* Initialise random number generator */
    srand(time(NULL));
    int rand_num;

    /* Specify stopping point */
    long halt = n*N_TIMES;

    long mean = 0;
    long remainder = 0;

    for (int i = 0; i < iter; i++) {
        #ifdef DEBUG
        printf("Iteration %i:\n", i+1);
        #endif
        check = (char*)malloc(array_len);
        memset(check, 0, array_len); // must use memset as calloc is not zeroing past the 8th byte

        long counter = n;
        #ifdef DEBUG
        printf("Counter: %li\n", counter);
        #endif
        long total = 0;

        while (counter) {
            rand_num = rand()%n;
            #ifdef DEBUG
            printf("Num: %i\n", rand_num);
            #endif
            counter -= check_bit(check, rand_num, char_bits);
            total++;
            if (total >= halt) {
                printf("\t Failed with %li found\n", n-counter);
                break;
            }
            #ifdef DEBUG
            for (int i = 0; i < array_len; i++) {
                print_bin(check[i]);
            }
            printf("Counter: %li\n", counter);
            #endif
        }

        mean += total/iter + remainder/iter;
        remainder = remainder%iter + total%iter;

        free(check);

        #ifdef DEBUG
        printf("\tTotal: %li\n", total);
        #endif
    }

    printf("Mean random selections: %.3f\n", mean+remainder/(1.0*iter));

    exit(0);
}