#include <stdio.h>

// Define the structure for storing a phone number
struct phone {
    int area_code;
    int exchange;
    int number;
};

int main() {
    // Initialize the first phone number with predefined values
    struct phone my_number = {212, 767, 8900};

    // Declare a second phone number that will be input by the user
    struct phone your_number;

    // Get the phone number details from the user
    printf("Enter area code: ");
    scanf("%d", &your_number.area_code);

    printf("Enter exchange: ");
    scanf("%d", &your_number.exchange);

    printf("Enter number: ");
    scanf("%d", &your_number.number);

    // Display both phone numbers
    printf("\nMy number is (%d) %d-%d\n", my_number.area_code, my_number.exchange, my_number.number);
    printf("Your number is (%d) %d-%d\n", your_number.area_code, your_number.exchange, your_number.number);

    return 0;
}
