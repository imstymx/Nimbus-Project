
#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_STUDENTS 100

// Structure for Room
struct Room {
    int roomNo;
    float rent;
    int occupied;
};

// Structure for Student
struct Student {
    int id;
    char name[50];
    int roomNo;
    int monthsDue;
    int monthsPaid;
};

// Function declarations
void addStudent(struct Student students[], int *count,
                struct Room rooms[], int roomCount);

void displayStudents(struct Student students[], int count);

void displayRooms(struct Room rooms[], int roomCount);

void payRent(struct Student students[], int count,
             struct Room rooms[], int roomCount);

void vacateRoom(struct Student students[], int *count,
                struct Room rooms[], int roomCount);

void generateMonthlyRent(struct Student students[], int count);

void searchStudent(struct Student students[], int count,
                   struct Room rooms[], int roomCount);


// Main Function
int main() {

    struct Room rooms[MAX_ROOMS];
    struct Student students[MAX_STUDENTS];

    int roomCount, studentCount = 0;
    int choice;

    printf("====================================\n");
    printf("       HOSTEL MANAGEMENT SYSTEM     \n");
    printf("====================================\n");

    printf("Enter number of rooms: ");
    scanf("%d", &roomCount);

    if (roomCount <= 0 || roomCount > MAX_ROOMS) {
        printf("Invalid number of rooms!\n");
        return 0;
    }

    // Initialize rooms
    for (int i = 0; i < roomCount; i++) {

        rooms[i].roomNo = 101 + i;
        rooms[i].occupied = 0;

        printf("Enter rent for Room %d: ",
               rooms[i].roomNo);

        scanf("%f", &rooms[i].rent);
    }

    // Main Menu
    do {

        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Display Rooms\n");
        printf("4. Pay Rent\n");
        printf("5. Vacate Room\n");
        printf("6. Generate Monthly Rent\n");
        printf("7. Search Student\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent(students, &studentCount,
                           rooms, roomCount);
                break;

            case 2:
                displayStudents(students, studentCount);
                break;

            case 3:
                displayRooms(rooms, roomCount);
                break;

            case 4:
                payRent(students, studentCount,
                        rooms, roomCount);
                break;

            case 5:
                vacateRoom(students, &studentCount,
                           rooms, roomCount);
                break;

            case 6:
                generateMonthlyRent(students, studentCount);
                break;

            case 7:
                searchStudent(students, studentCount,
                              rooms, roomCount);
                break;

            case 8:
                printf("\nThank you for using Hostel Management System!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 8);

    return 0;
}


// Function to Add Student
void addStudent(struct Student students[], int *count,
                struct Room rooms[], int roomCount) {

    int i, freeRoom = -1;

    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    // Find available room
    for (i = 0; i < roomCount; i++) {

        if (rooms[i].occupied == 0) {
            freeRoom = i;
            break;
        }
    }

    if (freeRoom == -1) {
        printf("Sorry! No rooms available.\n");
        return;
    }

    students[*count].id = *count + 1;

    printf("Enter student name: ");
    getchar();

    fgets(students[*count].name, 50, stdin);

    students[*count].name[
        strcspn(students[*count].name, "\n")
    ] = '\0';

    // Allocate room
    students[*count].roomNo = rooms[freeRoom].roomNo;

    rooms[freeRoom].occupied = 1;

    students[*count].monthsDue = 1;
    students[*count].monthsPaid = 0;

    printf("\nStudent added successfully!\n");
    printf("Student ID: %d\n", students[*count].id);
    printf("Allocated Room: %d\n", students[*count].roomNo);
    printf("Monthly Rent: %.2f\n", rooms[freeRoom].rent);

    (*count)++;
}


// Function to Display Students
void displayStudents(struct Student students[], int count) {

    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    for (int i = 0; i < count; i++) {

        printf("\nStudent ID: %d", students[i].id);
        printf("\nName: %s", students[i].name);
        printf("\nRoom Number: %d", students[i].roomNo);
        printf("\nMonths Due: %d", students[i].monthsDue);
        printf("\nMonths Paid: %d\n", students[i].monthsPaid);
    }
}


// Function to Display Rooms
void displayRooms(struct Room rooms[], int roomCount) {

    printf("\n========== ROOM DETAILS ==========\n");

    for (int i = 0; i < roomCount; i++) {

        printf("\nRoom Number: %d", rooms[i].roomNo);
        printf("\nMonthly Rent: %.2f", rooms[i].rent);

        if (rooms[i].occupied == 1)
            printf("\nStatus: Occupied\n");
        else
            printf("\nStatus: Available\n");
    }
}


// Function to Pay Rent
void payRent(struct Student students[], int count,
             struct Room rooms[], int roomCount) {

    int id, months, i, j;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {

        if (students[i].id == id) {

            printf("Enter number of months to pay: ");
            scanf("%d", &months);

            if (months <= 0 || months > students[i].monthsDue) {
                printf("Invalid payment months!\n");
                return;
            }

            for (j = 0; j < roomCount; j++) {

                if (rooms[j].roomNo == students[i].roomNo) {

                    float amount = rooms[j].rent * months;

                    students[i].monthsDue -= months;
                    students[i].monthsPaid += months;

                    printf("\nRent paid successfully!\n");
                    printf("Amount Paid: %.2f\n", amount);

                    printf("Remaining Due Months: %d\n",
                           students[i].monthsDue);

                    return;
                }
            }
        }
    }

    printf("Student not found!\n");
}


// Function to Vacate Room
void vacateRoom(struct Student students[], int *count,
                struct Room rooms[], int roomCount) {

    int id, i, j;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (i = 0; i < *count; i++) {

        if (students[i].id == id) {

            // Free the room
            for (j = 0; j < roomCount; j++) {

                if (rooms[j].roomNo == students[i].roomNo) {
                    rooms[j].occupied = 0;
                    break;
                }
            }

            // Shift remaining student records
            for (j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }

            (*count)--;

            printf("Room vacated successfully!\n");
            return;
        }
    }

    printf("Student not found!\n");
}


// Function to Generate Monthly Rent
void generateMonthlyRent(struct Student students[], int count) {

    for (int i = 0; i < count; i++) {
        students[i].monthsDue++;
    }

    printf("Monthly rent generated successfully!\n");
}


// Function to Search Student
void searchStudent(struct Student students[], int count,
                   struct Room rooms[], int roomCount) {

    int id, i, j;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {

        if (students[i].id == id) {

            printf("\nStudent Found!\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Room Number: %d\n", students[i].roomNo);

            for (j = 0; j < roomCount; j++) {

                if (rooms[j].roomNo == students[i].roomNo) {

                    printf("Monthly Rent: %.2f\n", rooms[j].rent);

                    printf("Total Due Amount: %.2f\n",
                           rooms[j].rent * students[i].monthsDue);

                    break;
                }
            }

            printf("Months Paid: %d\n", students[i].monthsPaid);
            printf("Months Due: %d\n", students[i].monthsDue);

            return;
        }
    }

    printf("Student not found!\n");
}
