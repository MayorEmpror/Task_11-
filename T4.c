#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 10

// Define the Employee structure
typedef struct {
    char name[50];
    char dob[11]; // Date of birth in DD/MM/YYYY format
    int emp_id;
    char department[50];
    float salary;
} Employee;

// Global array of employees
Employee employees[MAX_EMPLOYEES];
int employee_count = 0; // Track the number of employees in the system

// Function to add an employee
void add_employee() {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Employee limit reached! Cannot add more employees.\n");
        return;
    }

    Employee emp;
    printf("Enter employee details:\n");
    printf("Name: ");
    getchar(); // To consume newline from previous input
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0; // Remove the newline character from the input

    printf("Date of Birth (DD/MM/YYYY): ");
    fgets(emp.dob, sizeof(emp.dob), stdin);
    emp.dob[strcspn(emp.dob, "\n")] = 0;

    printf("Employee ID: ");
    scanf("%d", &emp.emp_id);

    getchar(); // To consume newline
    printf("Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    emp.department[strcspn(emp.department, "\n")] = 0;

    printf("Salary: ");
    scanf("%f", &emp.salary);

    // Add the employee to the array
    employees[employee_count++] = emp;
    printf("Employee added successfully!\n");
}

// Function to delete an employee by Employee ID
void delete_employee() {
    int emp_id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &emp_id);

    // Search for the employee with the given ID
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].emp_id == emp_id) {
            // Shift all employees after the deleted one
            for (int j = i; j < employee_count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employee_count--;
            printf("Employee with ID %d deleted successfully!\n", emp_id);
            return;
        }
    }
    printf("Employee with ID %d not found!\n", emp_id);
}

// Function to display all employees
void display_employees() {
    if (employee_count == 0) {
        printf("No employees to display.\n");
        return;
    }

    printf("\nEmployee Details:\n");
    for (int i = 0; i < employee_count; i++) {
        printf("Employee %d:\n", i + 1);
        printf("Name: %s\n", employees[i].name);
        printf("Date of Birth: %s\n", employees[i].dob);
        printf("Employee ID: %d\n", employees[i].emp_id);
        printf("Department: %s\n", employees[i].department);
        printf("Salary: %.2f\n\n", employees[i].salary);
    }
}

// Main function to display menu and handle user inputs
int main() {
    int choice;

    while (1) {
        // Display menu options
        printf("Employee Management System\n");
        printf("1. Add an Employee\n");
        printf("2. Delete an Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                delete_employee();
                break;
            case 3:
                display_employees();
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0); // Exit the program
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
