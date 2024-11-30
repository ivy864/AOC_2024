#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int startswith(char *str, char *substr) {
    if (strstr(str, substr) == str) {
    //    printf("%s: %s\n", str, substr);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }
    int sum = 0;
    char d1, d2;
    d1 = -1;
    d2 = -1; 

    char digits[10][20] = {"one", "two", "three", "four", "five", "six", 
        "seven", "eight", "nine"};

    char line[256];
    while (fgets(line, 256, input)) {
        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                if (d1 == -1) {
                    d1 = line[i] - '0';
                    d2 = line[i] - '0';
                }
                else {
                    d2 = line[i] - '0';
                }
            }

            else if (strlen(line) - i > 3){
                for (int j = 0; j < 9; j++) {
                    if (startswith(line + i, digits[j])) {
                        if (d1 == -1) {
                            d1 = j + 1;
                            d2 = j + 1;
                            break;
                        }
                        else {
                            d2 = j + 1;
                            break;
                        }
                    }
                }
            }

        }

        printf("%s: %d, %d\n", line, d1, d2);
        sum += (d1 * 10) + d2;

        d1 = -1;
        d2 = -1;
    }

    printf("sum: %d\n", sum);

    return EXIT_SUCCESS;
}
