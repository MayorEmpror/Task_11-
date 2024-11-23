#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPARTMENTS 10
#define MAX_COURSES 10
#define MAX_STUDENTS 50
#define FILE_NAME "university.dat"

// Structure Definitions
typedef struct {
    char name[50];
    char email[50];
} Instructor;

typedef struct {
    int id;
    char name[50];
    Instructor instructor;
    int studentCount;
    char students[MAX_STUDENTS][50];
} Course;

typedef struct {
    char name[50];
    int courseCount;
    Course courses[MAX_COURSES];
} Department;

typedef struct {
    int departmentCount;
    Department departments[MAX_DEPARTMENTS];
} University;

// Function Declarations
void addDepartment(University *university);
void addCourse(University *university);
void addStudent(University *university);
void viewUniversity(University *university);
void searchStudent(University *university);
void saveToFile(University *university);
void loadFromFile(University *university);

// Main Function
int main() {
    University university = {0};

    // Load data from file at startup
    loadFromFile(&university);

    int choice;
    while (1) {
        printf("\nUniversity Management System\n");
        printf("1. Add Department\n");
        printf("2. Add Course\n");
        printf("3. Add Student\n");
        printf("4. View University\n");
        printf("5. Search for a Student\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDepartment(&university); break;
            case 2: addCourse(&university); break;
            case 3: addStudent(&university); break;
            case 4: viewUniversity(&university); break;
            case 5: searchStudent(&university); break;
            case 6:
                saveToFile(&university);
                printf("Data saved successfully. Exiting...\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to Add a Department
void addDepartment(University *university) {
    if (university->departmentCount >= MAX_DEPARTMENTS) {
        printf("Maximum departments reached!\n");
        return;
    }

    Department *dept = &university->departments[university->departmentCount];
    printf("Enter Department Name: ");
    getchar(); // Clear newline
    fgets(dept->name, 50, stdin);
    strtok(dept->name, "\n"); // Remove trailing newline
    dept->courseCount = 0; // Initialize with zero courses
    university->departmentCount++;

    printf("Department added successfully!\n");
}

// Function to Add a Course
void addCourse(University *university) {
    if (university->departmentCount == 0) {
        printf("No departments available. Please add a department first.\n");
        return;
    }

    printf("Select Department:\n");
    for (int i = 0; i < university->departmentCount; i++) {
        printf("%d. %s\n", i + 1, university->departments[i].name);
    }
    int deptIndex;
    printf("Enter department number: ");
    scanf("%d", &deptIndex);
    deptIndex--;

    if (deptIndex < 0 || deptIndex >= university->departmentCount) {
        printf("Invalid department number!\n");
        return;
    }

    Department *dept = &university->departments[deptIndex];
    if (dept->courseCount >= MAX_COURSES) {
        printf("Maximum courses for this department reached!\n");
        return;
    }

    Course *course = &dept->courses[dept->courseCount];
    printf("Enter Course ID: ");
    scanf("%d", &course->id);
    getchar(); // Clear newline
    printf("Enter Course Name: ");
    fgets(course->name, 50, stdin);
    strtok(course->name, "\n"); // Remove trailing newline
    printf("Enter Instructor Name: ");
    fgets(course->instructor.name, 50, stdin);
    strtok(course->instructor.name, "\n");
    printf("Enter Instructor Email: ");
    fgets(course->instructor.email, 50, stdin);
    strtok(course->instructor.email, "\n");

    course->studentCount = 0; // Initialize with zero students
    dept->courseCount++;

    printf("Course added successfully!\n");
}

// Function to Add a Student
void addStudent(University *university) {
    if (university->departmentCount == 0) {
        printf("No departments available. Please add a department first.\n");
        return;
    }

    printf("Select Department:\n");
    for (int i = 0; i < university->departmentCount; i++) {
        printf("%d. %s\n", i + 1, university->departments[i].name);
    }
    int deptIndex;
    printf("Enter department number: ");
    scanf("%d", &deptIndex);
    deptIndex--;

    if (deptIndex < 0 || deptIndex >= university->departmentCount) {
        printf("Invalid department number!\n");
        return;
    }

    Department *dept = &university->departments[deptIndex];
    if (dept->courseCount == 0) {
        printf("No courses available in this department. Please add a course first.\n");
        return;
    }

    printf("Select Course:\n");
    for (int i = 0; i < dept->courseCount; i++) {
        printf("%d. %s\n", i + 1, dept->courses[i].name);
    }
    int courseIndex;
    printf("Enter course number: ");
    scanf("%d", &courseIndex);
    courseIndex--;

    if (courseIndex < 0 || courseIndex >= dept->courseCount) {
        printf("Invalid course number!\n");
        return;
    }

    Course *course = &dept->courses[courseIndex];
    if (course->studentCount >= MAX_STUDENTS) {
        printf("Maximum students for this course reached!\n");
        return;
    }

    printf("Enter Student Name: ");
    getchar(); // Clear newline
    fgets(course->students[course->studentCount], 50, stdin);
    strtok(course->students[course->studentCount], "\n"); // Remove trailing newline
    course->studentCount++;

    printf("Student added successfully!\n");
}

// Function to View the University Structure
void viewUniversity(University *university) {
    if (university->departmentCount == 0) {
        printf("No departments available.\n");
        return;
    }

    for (int i = 0; i < university->departmentCount; i++) {
        Department *dept = &university->departments[i];
        printf("\nDepartment: %s\n", dept->name);

        if (dept->courseCount == 0) {
            printf("  No courses available.\n");
            continue;
        }

        for (int j = 0; j < dept->courseCount; j++) {
            Course *course = &dept->courses[j];
            printf("  Course: %s (ID: %d)\n", course->name, course->id);
            printf("    Instructor: %s (Email: %s)\n", course->instructor.name, course->instructor.email);
            printf("    Students:\n");

            if (course->studentCount == 0) {
                printf("      No students enrolled.\n");
            } else {
                for (int k = 0; k < course->studentCount; k++) {
                    printf("      %s\n", course->students[k]);
                }
            }
        }
    }
}

// Function to Search for a Student
void searchStudent(University *university) {
    char studentName[50];
    printf("Enter student name to search: ");
    getchar(); // Clear newline
    fgets(studentName, 50, stdin);
    strtok(studentName, "\n"); // Remove trailing newline

    int found = 0;

    for (int i = 0; i < university->departmentCount; i++) {
        Department *dept = &university->departments[i];

        for (int j = 0; j < dept->courseCount; j++) {
            Course *course = &dept->courses[j];

            for (int k = 0; k < course->studentCount; k++) {
                if (strcmp(course->students[k], studentName) == 0) {
                    printf("Student %s found in Course: %s, Department: %s\n",
                           studentName, course->name, dept->name);
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

// Function to Save Data to a File
void saveToFile(University *university) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Unable to open file for saving!\n");
        return;
    }

    // Save number of departments
    fprintf(file, "%d\n", university->departmentCount);

    for (int i = 0; i < university->departmentCount; i++) {
        Department *dept = &university->departments[i];

        // Save department name and number of courses
        fprintf(file, "%s\n%d\n", dept->name, dept->courseCount);

        for (int j = 0; j < dept->courseCount; j++) {
            Course *course = &dept->courses[j];

            // Save course details
            fprintf(file, "%d\n%s\n%s\n%s\n%d\n", course->id, course->name,
                    course->instructor.name, course->instructor.email, course->studentCount);

            for (int k = 0; k < course->studentCount; k++) {
                // Save each student's name
                fprintf(file, "%s\n", course->students[k]);
            }
        }
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}


void loadFromFile(University *university) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No existing data file found. Starting with an empty university.\n");
        return;
    }

    // Load number of departments
    fscanf(file, "%d\n", &university->departmentCount);

    for (int i = 0; i < university->departmentCount; i++) {
        Department *dept = &university->departments[i];

        // Load department name and number of courses
        fgets(dept->name, 50, file);
        dept->name[strcspn(dept->name, "\n")] = '\0'; // Remove newline
        fscanf(file, "%d\n", &dept->courseCount);

        for (int j = 0; j < dept->courseCount; j++) {
            Course *course = &dept->courses[j];

            // Load course details
            fscanf(file, "%d\n", &course->id);
            fgets(course->name, 50, file);
            course->name[strcspn(course->name, "\n")] = '\0';
            fgets(course->instructor.name, 50, file);
            course->instructor.name[strcspn(course->instructor.name, "\n")] = '\0';
            fgets(course->instructor.email, 50, file);
            course->instructor.email[strcspn(course->instructor.email, "\n")] = '\0';
            fscanf(file, "%d\n", &course->studentCount);

            for (int k = 0; k < course->studentCount; k++) {
                fgets(course->students[k], 50, file);
                course->students[k][strcspn(course->students[k], "\n")] = '\0';
            }
        }
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}
