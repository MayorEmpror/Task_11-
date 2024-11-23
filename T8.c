#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "books.txt"

// Structure to store book details
typedef struct {
    int id;
    char title[100];
    char author[100];
    int quantity;
    float price;
} Book;

// Function declarations
void addBook();
void viewBooks();
void searchBook();
void updateBook();
void deleteBook();
void calculateInventoryValue();
int isDuplicateID(int id);
void menu();

// Main function
int main() {
    menu();
    return 0;
}

// Display the menu
void menu() {
    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add New Book\n");
        printf("2. View All Books\n");
        printf("3. Search for a Book\n");
        printf("4. Update Book Details\n");
        printf("5. Delete a Book\n");
        printf("6. Calculate Total Inventory Value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 6: calculateInventoryValue(); break;
            case 7: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to add a new book
void addBook() {
    FILE *file = fopen(FILE_NAME, "a+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.id);

    if (isDuplicateID(book.id)) {
        printf("Book ID already exists! Try again with a unique ID.\n");
        fclose(file);
        return;
    }

    printf("Enter Title: ");
    getchar(); // To clear newline character from input buffer
    fgets(book.title, 100, stdin);
    strtok(book.title, "\n"); // Remove trailing newline
    printf("Enter Author: ");
    fgets(book.author, 100, stdin);
    strtok(book.author, "\n"); // Remove trailing newline
    printf("Enter Quantity: ");
    scanf("%d", &book.quantity);
    if (book.quantity < 0) {
        printf("Quantity cannot be negative!\n");
        fclose(file);
        return;
    }
    printf("Enter Price: ");
    scanf("%f", &book.price);
    if (book.price < 0) {
        printf("Price cannot be negative!\n");
        fclose(file);
        return;
    }

    fprintf(file, "%d,%s,%s,%d,%.2f\n", book.id, book.title, book.author, book.quantity, book.price);
    fclose(file);
    printf("Book added successfully!\n");
}

// Function to view all books
void viewBooks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Book book;
    printf("\n%-10s %-30s %-30s %-10s %-10s\n", "Book ID", "Title", "Author", "Quantity", "Price");
    printf("-----------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
        printf("%-10d %-30s %-30s %-10d %-10.2f\n", book.id, book.title, book.author, book.quantity, book.price);
    }

    fclose(file);
}

// Function to search for a book by ID or title
void searchBook() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int searchID;
    char searchTitle[100];
    int choice, found = 0;

    printf("Search by:\n1. ID\n2. Title\nEnter choice: ");
    scanf("%d", &choice);

    Book book;

    if (choice == 1) {
        printf("Enter Book ID: ");
        scanf("%d", &searchID);

        while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
            if (book.id == searchID) {
                printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\nPrice: %.2f\n",
                       book.id, book.title, book.author, book.quantity, book.price);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        printf("Enter Book Title: ");
        getchar(); // To clear newline character from input buffer
        fgets(searchTitle, 100, stdin);
        strtok(searchTitle, "\n"); // Remove trailing newline

        while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
            if (strcmp(book.title, searchTitle) == 0) {
                printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\nPrice: %.2f\n",
                       book.id, book.title, book.author, book.quantity, book.price);
                found = 1;
                break;
            }
        }
    } else {
        printf("Invalid choice!\n");
    }

    if (!found) {
        printf("Book not found.\n");
    }

    fclose(file);
}

// Function to update book details
void updateBook() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    int updateID, found = 0;
    Book book;
    printf("Enter Book ID to update: ");
    scanf("%d", &updateID);

    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
        if (book.id == updateID) {
            found = 1;
            printf("Enter new Quantity: ");
            scanf("%d", &book.quantity);
            if (book.quantity < 0) {
                printf("Quantity cannot be negative! Skipping update.\n");
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }
            printf("Enter new Price: ");
            scanf("%f", &book.price);
            if (book.price < 0) {
                printf("Price cannot be negative! Skipping update.\n");
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }
        }
        fprintf(tempFile, "%d,%s,%s,%d,%.2f\n", book.id, book.title, book.author, book.quantity, book.price);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Book details updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("Book not found.\n");
    }
}

// Function to delete a book
void deleteBook() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    int deleteID, found = 0;
    Book book;
    printf("Enter Book ID to delete: ");
    scanf("%d", &deleteID);

    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
        if (book.id == deleteID) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d,%s,%s,%d,%.2f\n", book.id, book.title, book.author, book.quantity, book.price);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Book deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("Book not found.\n");
    }
}

// Function to calculate total inventory value
void calculateInventoryValue() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Book book;
    float totalValue = 0;

       while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
        totalValue += book.quantity * book.price;
    }

    fclose(file);
    printf("Total Inventory Value: %.2f\n", totalValue);
}

// Function to check for duplicate Book ID
int isDuplicateID(int id) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        return 0; // No file exists, so no duplicates
    }

    Book book;
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%f\n", &book.id, book.title, book.author, &book.quantity, &book.price) == 5) {
        if (book.id == id) {
            fclose(file);
            return 1; // Duplicate ID found
        }
    }

    fclose(file);
    return 0; // No duplicate ID
}

