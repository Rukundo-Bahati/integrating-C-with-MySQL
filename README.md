<h1>Integrating-C-with-MySQL</h1>
Welcome to the integrating-C-with-Mysql repository! This project demonstrates a CRUD (Create, Read, Update, Delete) system developed in C for 
managing student records using MySQL as the database. The primary objective is to provide a simple and effective example of how to integrate
C programs with a MySQL database.

<h3>Table of Contents</h3>
Introduction
Features
Prerequisites
Installation
Usage
CRUD Operations
Contributing
License
Introduction
This repository contains a C program that connects to a MySQL database to perform CRUD operations on student records. 
It serves as an educational tool for students and developers who want to learn how to integrate C with MySQL for database operations.

<h3>Features</h3>
Create: Add new student records to the database.
Read: Retrieve and display student records from the database.
Update: Modify existing student records in the database.
Delete: Remove student records from the database.
Prerequisites
Before you begin, ensure you have met the following requirements:

C compiler (e.g., GCC)
MySQL server and MySQL client
MySQL C API (MySQL Connector/C)
Basic knowledge of C programming and SQL
Installation
Follow these steps to get a copy of the project up and running on your local machine:

Clone the repository:

sh
Copy code
git clone https://github.com/Rukundo-Bahati/integrating-C-with-MySQL/.git
cd integrating-C-with-Mysql
Install MySQL server and client:

For Ubuntu:
sh
Copy code
sudo apt-get update
sudo apt-get install mysql-server mysql-client libmysqlclient-dev
Set up the MySQL database:

Log in to the MySQL server:
sh
Copy code
mysql -u root -p
Create a database and a user for the project:
sql
Copy code
CREATE DATABASE studentdb;
CREATE USER 'studentuser'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON studentdb.* TO 'studentuser'@'localhost';
FLUSH PRIVILEGES;
Create the student table:

sql
Copy code
USE studentdb;
CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL,
    grade VARCHAR(10) NOT NULL
);
Compile the C program:

sh
Copy code
gcc -o student_crud student_crud.c -lmysqlclient
Usage
Run the compiled program:

sh
Copy code
./student_crud
Follow the on-screen prompts to perform CRUD operations.

CRUD Operations
Create
To add a new student record, select the option to create a new record and provide the required details such as name, age, and grade.

Read
To view student records, select the option to display all records. The program will fetch and display all student records from the database.

Update
To update an existing student record, select the option to update a record, provide the student ID and the new details to be updated.

Delete
To delete a student record, select the option to delete a record and provide the student ID of the record to be removed.

Contributing
Contributions are welcome! Please follow these steps to contribute:

Fork the repository.
Create a new branch (git checkout -b feature-branch).
Make your changes and commit them (git commit -m 'Add new feature').
Push to the branch (git push origin feature-branch).
Open a pull request.
License
This project is licensed under the MIT License. See the LICENSE file for more details.
