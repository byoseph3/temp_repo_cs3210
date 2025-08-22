#include <stdio.h>

int main()
{
    int marathon_yards_portion;
    int marathon_miles_portion;

    marathon_yards_portion = 385;
    marathon_miles_portion = 29;

    float marathon_in_kilometers = 1.609 * (marathon_miles_portion + (marathon_yards_portion/1760.0));

    printf("Marathon in kilometers: %1.2f\a\n", marathon_in_kilometers);
}