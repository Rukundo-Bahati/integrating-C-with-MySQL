#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "studdb"

typedef struct address {
    char email[20];
    char tel[20];
} Address;

typedef struct student {
    int id;
    char fname[20];
    char lname[20];
    char gender[6];
    char dob[20];
    Address addr;
} Student;

MYSQL *conn;

void connect_to_database() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error initializing MySQL: %s\n", mysql_error(conn));
        exit(1);
    }

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to MySQL: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

void create() {
    int numberOfStudents;
    printf("\nHow many students do you want? : ");
    scanf("%d", &numberOfStudents);

    for (int i = 0; i < numberOfStudents; i++) {
        Student s;
        printf("\nEnter Student ID: ");
        scanf("%d", &s.id);

        printf("\nEnter FirstName: ");
        scanf("%s", s.fname);
        printf("\nEnter LastName: ");
        scanf("%s", s.lname);

        printf("\nInput the Gender: ");
        scanf("%s", s.gender);

        printf("\nInput date of Birth: ");
        scanf("%s", s.dob);

        printf("\nEnter Email Address: ");
        scanf("%s", s.addr.email);

        printf("\nEnter Tel No: ");
        scanf("%s", s.addr.tel);

        // Insert address into addresses table
        char addressQuery[512];
        sprintf(addressQuery, "INSERT INTO addresses (email, tel) VALUES ('%s', '%s')",
                s.addr.email, s.addr.tel);
        if (mysql_query(conn, addressQuery)) {
            fprintf(stderr, "Error inserting address: %s\n", mysql_error(conn));
        }

        // Retrieve the auto-generated address ID
        int addressId = mysql_insert_id(conn);

        // Insert student into students table with the retrieved address ID
        char studentQuery[512];
        sprintf(studentQuery, "INSERT INTO students VALUES (%d, '%s', '%s', '%s', '%s', %d)",
                s.id, s.fname, s.lname, s.gender, s.dob, addressId);
        if (mysql_query(conn, studentQuery)) {
            fprintf(stderr, "Error inserting student: %s\n", mysql_error(conn));
        }
    }
}

void read() {
    if (mysql_query(conn, "SELECT students.id, students.fname, students.lname, students.gender, students.dob, addresses.email, addresses.tel FROM students JOIN addresses ON students.address_id = addresses.id")) {
        fprintf(stderr, "Error reading students: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return;
    }

    printf("\n%-5s%-20s%-20s%-10s%-15s%-25s%-15s\n", "ID", "First Name", "Last Name", "Gender", "DOB", "Email", "Tel");
    printf("------------------------------------------------------------------------------------------------------------\n");

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%-5s%-20s%-20s%-10s%-15s%-25s%-15s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
    }

    mysql_free_result(result);
}

int total() {
    if (mysql_query(conn, "SELECT COUNT(*) FROM students")) {
        fprintf(stderr, "Error counting students: %s\n", mysql_error(conn));
        return -1; // Return -1 to indicate failure
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return -1; // Return -1 to indicate failure
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int total = atoi(row[0]); // Convert the count to integer

    printf("Total students: %d\n", total);

    mysql_free_result(result);

    return total;
}

void add() {
    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("\nEnter FirstName: ");
    scanf("%s", s.fname);
    printf("\nEnter LastName: ");
    scanf("%s", s.lname);

    printf("\nInput the Gender: ");
    scanf("%s", s.gender);

    printf("\nInput date of Birth: ");
    scanf("%s", s.dob);

    printf("\nEnter Email Address: ");
    scanf("%s", s.addr.email);

    printf("\nEnter Tel No: ");
    scanf("%s", s.addr.tel);

    // Insert student into database
    char query[512];
    sprintf(query, "INSERT INTO students VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s')",
            s.id, s.fname, s.lname, s.gender, s.dob, s.addr.email, s.addr.tel);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error inserting student: %s\n", mysql_error(conn));
    } else {
        printf("Student added successfully!\n");
    }
}

void update() {
    int id;
    printf("Enter the ID of the student to update: ");
    scanf("%d", &id);

    // Prompt user for updated information
    Student s;
    printf("\nEnter FirstName: ");
    scanf("%s", s.fname);
    printf("\nEnter LastName: ");
    scanf("%s", s.lname);

    printf("\nInput the Gender: ");
    scanf("%s", s.gender);

    printf("\nInput date of Birth: ");
    scanf("%s", s.dob);

    printf("\nEnter Email Address: ");
    scanf("%s", s.addr.email);

    printf("\nEnter Tel No: ");
    scanf("%s", s.addr.tel);

    // Update student record in database
    char query[512];
    sprintf(query, "UPDATE students SET fname='%s', lname='%s', gender='%s', dob='%s', email='%s', tel='%s' WHERE id=%d",
            s.fname, s.lname, s.gender, s.dob, s.addr.email, s.addr.tel, id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error updating student: %s\n", mysql_error(conn));
    } else {
        printf("Student updated successfully!\n");
    }
}

void delete() {
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);

    // Delete student record from database
    char query[512];
    sprintf(query, "DELETE FROM students WHERE id=%d", id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error deleting student: %s\n", mysql_error(conn));
    } else {
        printf("Student deleted successfully!\n");
    }
}

int main() {
    connect_to_database();

    int start;
    do {
        printf("\n1. Create a Record");
        printf("\n2. Display all Records");
        printf("\n3. Total Records");
        printf("\n4. Add a new Record");
        printf("\n5. Update a new Record");
        printf("\n6. Delete a new Record");
        printf("\n0. EXIT");

        printf("\nEnter your Choice: ");
        scanf("%d", &start);

        switch (start) {
            case 1:
                create();
                break;
            case 2:
                read();
                break;
            case 3:
                total();
                break;
            case 4:
                add();
                break;
            case 5:
                update();
                break;
            case 6:
                delete();
                break;
            case 0:
                break;
            default:
                printf("\nInvalid Option chosen.\n");
        }
    } while (start != 0);

    mysql_close(conn);
    return 0;
}
