# Inverted Search

## 📌 Description

Inverted Search is a C-based project that creates an inverted index for words present in multiple text files.

The project stores each unique word along with the list of files in which the word occurs and the number of occurrences in each file.

It allows efficient searching of words across multiple files without scanning every file each time.

---

## 🚀 Features

- Create an inverted index from multiple text files.
- Store unique words using a hash table.
- Store file information using linked lists.
- Search for a word and display the files in which it occurs.
- Display the complete database.
- Update the database with additional files.
- Save the database to a file.
- Load the database from a previously saved file.
- Handle duplicate words and multiple occurrences.

---

## 🛠️ Technologies Used

- C Programming
- Data Structures
- Hash Table
- Linked List
- File Handling
- Pointers
- Dynamic Memory Allocation
- Command Line Arguments

---

## 📚 Data Structures Used

### 1. Hash Table

A hash table is used as the primary data structure to store words.

A hash function maps each word to a particular index in the hash table.

```text
Hash Table
   |
   +-- [0]
   +-- [1]
   +-- [2] --> word --> file list
   +-- [3]
   +-- ...
   +-- [27]

2. Linked List

Linked lists are used to handle multiple words at the same hash index and to maintain file information associated with each word.

The project uses linked structures to store:

Word information

File names

Occurrence counts



---

📂 Project Structure

Inverted_Search/
│
├── main.c
├── create_database.c
├── display_database.c
├── search_database.c
├── update_database.c
├── save_database.c
├── file.h
├── main.h
├── types.h
└── README.md

> File names may vary depending on the project skeleton.




---

⚙️ Compilation

Compile all C files using:

gcc *.c


---

▶️ Running the Project

Example:

./a.out file1.txt file2.txt file3.txt

The project can then be used to create, search, display, update, and save the inverted database.


---

🔍 Example

Suppose the input files contain:

file1.txt

hello world
hello c

file2.txt

hello programming

The inverted index for hello can be represented as:

hello
 ├── file1.txt : 2
 └── file2.txt : 1

Here:

hello → searched word

file1.txt → contains the word 2 times

file2.txt → contains the word 1 time



---

💡 Concepts Learned

Hashing

Hash table implementation

Linked lists

Collision handling

File handling

Dynamic memory allocation

Structures and pointers

Command-line arguments

Searching and indexing

Modular programming

Database creation and updating



---

🎯 Project Objective

The objective of this project is to implement an efficient word-searching mechanism using a hash table and linked lists.

The project demonstrates how an inverted index can be created and used to quickly find the files containing a particular word.


---

👨‍💻 Author

Raj Chilshett
