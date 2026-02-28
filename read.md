📒 Address Book Management System (C)
🔹 Overview

A console-based Address Book application developed in C to manage contacts efficiently.
Supports creating, searching, editing, deleting, displaying, saving, and loading contacts with proper input validation.

🔹 Features

✔ Add new contacts (Name, Mobile, Email)
✔ Validate name, 10-digit mobile number, and email format
✔ Search by Name / Mobile / Email (handles duplicate names)
✔ Edit and delete contacts with confirmation
✔ Display all contacts
✔ Permanent storage using CSV file

🔹 Implementation Details

🔸 Uses structures and array-based storage (max 100 contacts)
🔸 Input validation using isalpha(), isdigit() and string functions
🔸 File handling implemented using fopen(), fprintf(), fscanf(), and fclose()
🔸 Contacts stored in contacts.csv for persistent storage
🔸 No binary file functions (fread() / fwrite()) used

🔹 Concepts Used

✔ C Programming
✔ Structures & Arrays
✔ File Handling (CSV Format)
✔ String Manipulation
✔ Modular Programming
✔ Input Validation

🔹 Outcome

Demonstrates strong knowledge of C programming fundamentals, structured application design, file management using CSV, and real-world console application development.