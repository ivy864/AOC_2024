#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int in(int *arr, int arrlen, int num) {
    for (int i = 0; i < arrlen; i++)  {
        if (arr[i] == num) {
            return i;
        }
    }

    return -1;
}

int validateline(char line[256], int pgrls[2][1200], int pgrls_size) {
    int *nums = malloc(sizeof(int) * 100);
    int numsize = 0;

    for (int i = 0; i < strlen(line); i = i + 3) {
        line[i + 2] = '\0';
        nums[numsize] = strtol(line + i, NULL, 10);
        line[i + 2] = ',';
        numsize++;
    }

    for (int i = 0; i < numsize; i++) {
        int npos = in(pgrls[1], pgrls_size, nums[i]);


        if (npos != -1) {
            for (int j = npos; j < pgrls_size; j++) {
                if (pgrls[1][j] == nums[i]) {
                    if (in(nums, numsize, pgrls[0][j]) > i) {
                        return 0;
                    }
                }
            }
        }
    }

    int nmid = nums[numsize / 2];

    free(nums);
    return nmid;
}

int orderline(char line[256], int pgrls[2][1200], int pgrls_size) {
    int *nums = malloc(sizeof(int) * 100);
    int numsize = 0;

    for (int i = 0; i < strlen(line); i = i + 3) {
        line[i + 2] = '\0';
        nums[numsize] = strtol(line + i, NULL, 10);
        line[i + 2] = ',';
        numsize++;
    }

    int swaps = 1;

    while (swaps != 0) {
        swaps = 0;

        for (int i = 0; i < numsize; i++) {

            int npos = in(pgrls[1], pgrls_size, nums[i]);

            if (npos != -1) {
                for (int j = npos; j < pgrls_size; j++) {
                    if (pgrls[1][j] == nums[i]) {

                        int n2pos = in(nums, numsize, pgrls[0][j]) ;
                        if (n2pos > i) {
                            int tmp = nums[i];
                            nums[i] = nums[n2pos];
                            for (int k = i; k < n2pos; k++) {
                                int tmp2 = nums[k + 1];
                                nums[k + 1] = tmp;
                                tmp = tmp2;
                            }

                            swaps++;
                        }
                    }
                }
            }
        }
    }

    int midn = nums[numsize / 2];

    free(nums);
    return midn;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int pgrls[2][1200];
    int pgrls_size = 0;

    int total = 0;

    while (fgets(line, 256, input) ) {
        char *delim = strchr(line, '|');
        if (delim != NULL) {
            *delim = '\0';

            pgrls[0][pgrls_size] = strtol(line, NULL, 10);
            pgrls[1][pgrls_size] = strtol(delim + 1, NULL, 10);

            pgrls_size++;
        }
        else {
            printf("%s", line);
            int validate = validateline(line, pgrls, pgrls_size);

            if (validate == 0) {
                total += orderline(line, pgrls, pgrls_size);
            }
        }
    }

    printf("total: %d\n", total);

    return EXIT_SUCCESS;
}
