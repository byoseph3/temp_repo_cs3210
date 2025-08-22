#include <stdio.h>

int main() {

    int radius;
    float area, circumfrence, pi;

    pi = 22/7.0;
    printf("Enter the radius of the circle: ");
    scanf("%d", &radius);
    area = pi * radius * radius;
    circumfrence = 2 * pi * radius;
    printf("Area: %.5f\nCircumference: %.5f\n", area, circumfrence);

    return 0;
}