#include <stdio.h>

#define MIN_DIMENSION 0.0
#define MAX_DIMENSION 20.0

// Define the Rectangle struct
typedef struct {
    float length;
    float width;
} Rectangle;

// Function to check if the dimensions are valid (greater than 0 and less than 20)
int check(Rectangle *rect) {
    if (rect->length > MIN_DIMENSION && rect->length < MAX_DIMENSION &&
        rect->width > MIN_DIMENSION && rect->width < MAX_DIMENSION) {
        return 1; // Valid dimensions
    }
    return 0; // Invalid dimensions
}

// Function to calculate the perimeter of the rectangle
float perimeter(Rectangle *rect) {
    if (check(rect)) {
        return 2 * (rect->length + rect->width);
    } else {
        printf("Invalid dimensions!\n");
        return -1; // Return -1 if dimensions are invalid
    }
}

// Function to calculate the area of the rectangle
float area(Rectangle *rect) {
    if (check(rect)) {
        return rect->length * rect->width;
    } else {
        printf("Invalid dimensions!\n");
        return -1; // Return -1 if dimensions are invalid
    }
}

int main() {
    // Create a Rectangle
    Rectangle rect;
    
    // Input length and width from the user
    printf("Enter length: ");
    scanf("%f", &rect.length);
    printf("Enter width: ");
    scanf("%f", &rect.width);
    
    // Check if the dimensions are valid
    if (check(&rect)) {
        // Calculate and display the perimeter and area
        printf("Perimeter: %.2f\n", perimeter(&rect));
        printf("Area: %.2f\n", area(&rect));
    } else {
        printf("Invalid rectangle dimensions. Length and width must be greater than 0 and less than 20.\n");
    }
    
    return 0;
}
