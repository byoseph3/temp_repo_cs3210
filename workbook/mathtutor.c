#include <stdio.h>
#include <stdlib.h>

int main() {
    int number1, number2, response, sum;

    srand(17);
    number1 = rand() % 20;
    number2 = rand() % 20;
    sum = number1 + number2;

    printf("%d + %d = ?\n", number1, number2);
    scanf("%d", &response);

    if (response == sum) {
        printf("Correct!\n");
    } else {
        printf("Incorrect!\n");
    }

    return 0;
}