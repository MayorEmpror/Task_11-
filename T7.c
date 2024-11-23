#include <stdio.h>
#include <string.h>

#define MAX_DEPARTMENTS 5
#define MAX_COURSES 5

// Define a structure for the course details
struct Course {
    char course_id[10];
    char course_name[50];
    char instructor_name[50];
    int credits;
};

// Define a structure for the department, which contains courses
struct Department {
    char department_name[50];
    struct Course courses[MAX_COURSES];
    int num_courses; // To keep track of the number of courses in the department
};

// Declare an array of departments
struct Department departments[MAX_DEPARTMENTS];
int num_departments = 0; // To keep track of the number of departments in the system

// Function to add a new department
void add_department() {
    if (num_departments >= MAX_DEPARTMENTS) {
        printf("Maximum department limit reached!\n");
        return;
    }

    struct Department new_department;
    printf("Enter department name: ");
    getchar();  // To consume the newline from previous input
    fgets(new_department.department_name, sizeof(new_department.department_name), stdin);
    new_department.department_name[strcspn(new_department.department_name, "\n")] = '\0'; // Remove newline

    new_department.num_courses = 0; // Initialize course count to zero

    // Add the new department to the departments array
    departments[num_departments++] = new_department;
    printf("Department '%s' added successfully!\n", new_department.department_name);
}

// Function to add a new course to a department
void add_course() {
    char department_name[50];
    printf("Enter department name to add a course: ");
    getchar();  // To consume the newline from previous input
    fgets(department_name, sizeof(department_name), stdin);
    department_name[strcspn(department_name, "\n")] = '\0'; // Remove newline

    // Search for the department
    for (int i = 0; i < num_departments; i++) {
        if (strcmp(departments[i].department_name, department_name) == 0) {
            // Add the course to the department
            if (departments[i].num_courses >= MAX_COURSES) {
                printf("Maximum course limit reached for this department!\n");
                return;
            }

            struct Course new_course;
            printf("Enter course ID: ");
            fgets(new_course.course_id, sizeof(new_course.course_id), stdin);
            new_course.course_id[strcspn(new_course.course_id, "\n")] = '\0'; // Remove newline

            printf("Enter course name: ");
            fgets(new_course.course_name, sizeof(new_course.course_name), stdin);
            new_course.course_name[strcspn(new_course.course_name, "\n")] = '\0'; // Remove newline

            printf("Enter instructor name: ");
            fgets(new_course.instructor_name, sizeof(new_course.instructor_name), stdin);
            new_course.instructor_name[strcspn(new_course.instructor_name, "\n")] = '\0'; // Remove newline

            printf("Enter number of credits: ");
            scanf("%d", &new_course.credits);

            // Add the new course to the department's course list
            departments[i].courses[departments[i].num_courses++] = new_course;
            printf("Course '%s' added to department '%s'.\n", new_course.course_name, department_name);
            return;
        }
    }

    printf("Department '%s' not found!\n", department_name);
}

// Function to display details of all departments and courses
void display_details() {
    if (num_departments == 0) {
        printf("No departments available.\n");
        return;
    }

    for (int i = 0; i < num_departments; i++) {
        printf("\nDepartment: %s\n", departments[i].department_name);
        for (int j = 0; j < departments[i].num_courses; j++) {
            printf("  Course ID: %s\n", departments[i].courses[j].course_id);
            printf("  Course Name: %s\n", departments[i].courses[j].course_name);
            printf("  Instructor: %s\n", departments[i].courses[j].instructor_name);
            printf("  Credits: %d\n", departments[i].courses[j].credits);
        }
    }
}

// Function to calculate the total credits for a department
void calculate_total_credits() {
    char department_name[50];
    printf("Enter department name to calculate total credits: ");
    getchar();  // To consume the newline from previous input
    fgets(department_name, sizeof(department_name), stdin);
    department_name[strcspn(department_name, "\n")] = '\0'; // Remove newline

    for (int i = 0; i < num_departments; i++) {
        if (strcmp(departments[i].department_name, department_name) == 0) {
            int total_credits = 0;
            for (int j = 0; j < departments[i].num_courses; j++) {
                total_credits += departments[i].courses[j].credits;
            }
            printf("Total credits in department '%s': %d\n", department_name, total_credits);
            return;
        }
    }

    printf("Department '%s' not found!\n", department_name);
}

// Main function with the menu system
int main() {
    int choice;

    while (1) {
        printf("\nUniversity Course Enrollment System\n");
        printf("1. Add a Department\n");
        printf("2. Add a Course\n");
        printf("3. Display All Departments and Courses\n");
        printf("4. Calculate Total Credits for a Department\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_department();
                break;
            case 2:
                add_course();
                break;
            case 3:
                display_details();
                break;
            case 4:
                calculate_total_credits();
                break;
            case 5:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
