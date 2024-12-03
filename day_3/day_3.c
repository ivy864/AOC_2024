#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// 57464439
// 46205564
// 46205564
// 76911921
// strtol(char*, NULL, 10);
int multiply(char* str) {
    if (strlen(str) < 8) {
        return 0;
    }
    printf("str: %s\n", str);
    str += 4;
    printf("str: %s\n", str);
    int num1, num2;

    char* com = strchr(str, ',');

    if (com == NULL || com - str > 3) {
        return 0;
    }
    *com = '\0';
    printf("str: %s\n", str);
    num1 = strtol(str, NULL, 10);

    str = com + 1;
    char* parn = strchr(str, ')');

    if (parn == NULL || parn - str > 3) {
        *com = ',';
        return 0;
    }
    *parn = '\0';

    num2 = strtol(str, NULL, 10);

    *parn = ')';
    *com = ',';

    printf("one: %d, two: %d\n", num1, num2);
    return num1 * num2;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[10000];

    char* spot;
    int total = 0;
    int its = 0;
    int domul = 1;
    char* nextdont;

    while (fgets(line, 10000, input)) {
        spot = strstr(line, "mul(");
        nextdont = strstr(line, "don't()");

        while(spot != NULL) {
            if (domul) {
                if (nextdont != NULL && nextdont < spot) {
                    printf("dont! %s\n", nextdont);
                    domul = 0;
                    nextdont = strstr(nextdont + 1, "don't()");
                }

                else {
                    total += multiply(spot);
                    if (strlen(spot) < 8) {
                        break;
                    }
                    spot = spot + 4;
                    spot = strstr(spot, "mul(");
                }
                
            }
            else {
                spot = strstr(spot, "do()");
                if (spot != NULL) {
                    spot = strstr(spot, "mul(");
                    if (spot != NULL) {
                        nextdont = strstr(spot, "don't()");
                    }
                    domul = 1;
                }
            }
        }
        // total += multiply(spot);

        its++;
    }

    printf("total: %d\n", total);
    printf("its: %d\n", its);

    return EXIT_SUCCESS;
}
