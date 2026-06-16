#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float gpa;
} Student;

typedef struct {
    Student *data;
    int capacity;
    int count;
} Database;

// Initialize the database structure
void init_database(Database *db, int initial_capacity) {
    db->data = (Student *)malloc(initial_capacity * sizeof(Student));
    if (db->data == NULL) {
        printf("System Error: Memory allocation failed!\n");
        exit(1);
    }
    db->capacity = initial_capacity;
    db->count = 0;
}

// Resize array dynamically when capacity limit is reached
void resize_database(Database *db) {
    db->capacity *= 2;
    Student *temp = (Student *)realloc(db->data, db->capacity * sizeof(Student));
    if (temp == NULL) {
        printf("System Error: Memory optimization failed during resize!\n");
        free(db->data);
        exit(1);
    }
    db->data = temp;
    printf("[System Log]: Database expanded capacity to %d slots.\n", db->capacity);
}

// Add a student record with safety checks
void add_student(Database *db, int id, const char *name, float gpa) {
    // Validate uniqueness of ID
    for (int i = 0; i < db->count; i++) {
        if (db->data[i].id == id) {
            printf("Error: Student record with ID %d already exists.\n", id);
            return;
        }
    }

    if (db->count >= db->capacity) {
        resize_database(db);
    }

    db->data[db->count].id = id;
    strncpy(db->data[db->count].name, name, MAX_NAME_LEN - 1);
    db->data[db->count].name[MAX_NAME_LEN - 1] = '\0'; // Safety termination
    db->data[db->count].gpa = gpa;
    db->count++;
    printf("Success: Recorded entry for %s.\n", name);
}

// Search student records by numeric ID
void find_student_by_id(const Database *db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->data[i].id == id) {
            printf("\n--- Record Discovered ---\n");
            printf("ID: %d | Name: %s | GPA: %.2f\n", db->data[i].id, db->data[i].name, db->data[i].gpa);
            return;
        }
    }
    printf("Result: No matching record found for ID %d.\n", id);
}

// Display summary lists of the entire register
void print_database(const Database *db) {
    printf("\n================ STUDENT INVENTORY ================\n");
    if (db->count == 0) {
        printf("The inventory registry is completely empty.\n");
    } else {
        printf("%-10s | %-25s | %-5s\n", "ID", "Full Name", "GPA");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < db->count; i++) {
            printf("%-10d | %-25s | %-5.2f\n", db->data[i].id, db->data[i].name, db->data[i].gpa);
        }
    }
    printf("===================================================\n");
}

// Free allocated memory safely
void free_database(Database *db) {
    if (db->data != NULL) {
        free(db->data);
        db->data = NULL;
    }
    db->count = 0;
    db->capacity = 0;
}

int main(void) {
    Database school_db;
    init_database(&school_db, 2); // Small initial capacity to verify auto-resize

    printf("--- Injecting Seed Data Records ---\n");
    add_student(&school_db, 101, "Alice Montgomery", 3.92);
    add_student(&school_db, 102, "Bob Richardson", 3.45);
    add_student(&school_db, 103, "Charlie Henderson", 2.88); // Triggers auto-resize

    print_database(&school_db);

    printf("\n--- Running Target Lookups ---\n");
    find_student_by_id(&school_db, 102);
    find_student_by_id(&school_db, 999); // Testing search missing edge-case

    printf("\n--- Processing Data Edge Cases ---\n");
    add_student(&school_db, 101, "Duplicate Entry Test", 4.00); // Triggers error block

    free_database(&school_db);
    printf("\n[System Log]: Resource allocation clean-up complete.\n");
    return 0;
}

