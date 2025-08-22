#include <stdio.h>

int main() {

    int integer_1, integer_2, sum;
    float avg;

    printf("Please give two integers with a space in between:");
    scanf("%d %d", &integer_1, &integer_2);

    sum = integer_1 + integer_2;
    avg = sum / 2.0;

    printf("Sum = %d\n Average = %.2f\n", sum, avg);
    return 0;
}