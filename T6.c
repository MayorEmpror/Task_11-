#include <stdio.h>
#include <string.h>

// Define the structure for an invoice
struct Invoice {
    char part_number[20];
    char part_description[100];
    int quantity;
    float price_per_item;
};

// Function to calculate the total amount for the invoice
float calculate_invoice(struct Invoice *inv) {
    if (inv->quantity <= 0) {
        inv->quantity = 0;
    }
    if (inv->price_per_item <= 0) {
        inv->price_per_item = 0.0;
    }
    return inv->quantity * inv->price_per_item;
}

int main() {
    // Declare and initialize the Invoice structure
    struct Invoice inv = {
        "A1234", 
        "Hammer", 
        10, 
        12.99
    };

    // Get invoice details from the user
    printf("Enter part number: ");
    scanf("%s", inv.part_number);

    getchar();  // To consume the newline character from the previous input
    printf("Enter part description: ");
    fgets(inv.part_description, sizeof(inv.part_description), stdin);
    inv.part_description[strcspn(inv.part_description, "\n")] = '\0'; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &inv.quantity);

    printf("Enter price per item: ");
    scanf("%f", &inv.price_per_item);

    // Calculate the invoice total
    float total = calculate_invoice(&inv);

    // Display the invoice details and total amount
    printf("\nInvoice Details:\n");
    printf("Part Number: %s\n", inv.part_number);
    printf("Part Description: %s\n", inv.part_description);
    printf("Quantity: %d\n", inv.quantity);
    printf("Price per item: %.2f\n", inv.price_per_item);
    printf("Total Invoice Amount: %.2f\n", total);

    return 0;
}
