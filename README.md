# 📚 Library Management System in C++

## 📌 Project Overview

The **Library Management System** is a console-based application developed using C++. It helps manage books, book copies, library members, payments, book issuing, returns, and overdue fines.

The system uses file handling to store and retrieve records, allowing data to be maintained even after the program is closed.

## 🎯 Objectives

- To maintain book and book-copy records.
- To register and manage library members.
- To manage membership payments.
- To issue books to eligible members.
- To record book returns and calculate overdue fines.
- To generate reports for issued books, overdue books, paid members, and total fines.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Concepts:** Object-Oriented Programming (OOP)
- **File Handling:** `ifstream` and `ofstream`
- **STL:** Vector and String
- **Libraries:** iostream, fstream, vector, string, ctime
- **Data Storage:** Text files

## ✨ Features

1. **Admin Login** — Login using predefined credentials.
2. **Add Book** — Store book ID, title, author, ISBN, and price.
3. **View Books** — Display stored book records.
4. **Manage Book Copies** — Add and view individual copies with rack numbers and availability status.
5. **Member Registration** — Store member details such as name, address, phone, and email.
6. **Membership Payment** — Record payments and update membership payment status.
7. **Issue Books** — Issue an available book copy to a member whose payment status is active.
8. **Return Books** — Record returned books and calculate fines for late returns.
9. **Issued Books Report** — Display books that have not yet been returned.
10. **Overdue Books Report** — Identify overdue issues.
11. **Paid Members Report** — Display members who have paid.
12. **Total Fine Report** — Calculate the total recorded fines.

## 🔐 Login Credentials

The program uses hardcoded credentials.

- **Username:** `admin`
- **Password:** `1234`

**Note:** These credentials are for demonstration purposes only and should be changed before using the system in a real environment.

## 📂 Project Structure

```text
Library-Management-System/
│
├── main.cpp
├── books.txt
├── copies.txt
├── members.txt
├── issues.txt
├── payments.txt
└── README.md
```

The `.txt` files are created or updated by the program when records are saved.

## ⚙️ How to Run the Project

### Step 1: Install a C++ compiler

Install a C++ compiler such as GCC through MinGW or use an IDE such as Code::Blocks or Visual Studio.

### Step 2: Save the source code

Save the provided C++ source code as `main.cpp`.

### Step 3: Compile the program

Open a terminal in the project folder and run:

```bash
g++ main.cpp -o library
```

### Step 4: Run the program

On Windows, execute:

```bash
library.exe
```

Alternatively, in PowerShell, use:

```powershell
.\library.exe
```

### Step 5: Log in

Enter the username and password provided above to access the main menu.

## 📋 Main Menu

The application provides the following menu options:

| Option | Operation |
|---:|---|
| 1 | Add Book |
| 2 | View Books |
| 3 | Add Copy |
| 4 | View Copies |
| 5 | Add Member |
| 6 | View Members |
| 7 | Make Payment |
| 8 | Issue Book |
| 9 | Return Book |
| 10 | Issued Books Report |
| 11 | Overdue Books |
| 12 | Paid Members |
| 13 | Total Fines |
| 0 | Exit |

## 💰 Fine Calculation

The program calculates overdue fines at a rate of **₹5 per late day**.

- If a book is returned on or before its due date, the fine is ₹0.
- If a book is returned late, the fine is calculated based on the number of late days multiplied by ₹5.

The current implementation uses simplified date calculations for demonstration.

## 💾 Data Storage

The application stores information in text files using the pipe (`|`) character as a separator.

- `books.txt` — Book details
- `copies.txt` — Book-copy details and availability
- `members.txt` — Member details and payment status
- `issues.txt` — Issue, due date, return, and fine details
- `payments.txt` — Payment and receipt details

## 🧠 OOP Concepts Used

- **Classes and Objects:** Separate classes represent books, copies, members, issue records, payments, and the library.
- **Encapsulation:** Related data and operations are grouped into classes, although the data members are public in this implementation.
- **Member Functions:** Functions perform operations such as adding books, issuing books, and processing returns.
- **File Handling:** Records are stored persistently in text files.

## 🚀 Future Enhancements

- Replace hardcoded login credentials with secure authentication.
- Use a database such as MySQL instead of text files.
- Improve date calculations to handle real calendar dates accurately.
- Add search functionality for books and members.
- Add input validation and stronger duplicate-record checks.
- Generate printable receipts and detailed reports.
- Develop a graphical user interface.

## 🎓 Conclusion

The Library Management System demonstrates how C++ and Object-Oriented Programming can be used to automate basic library operations. It provides a practical learning project for understanding classes, file handling, record management, and menu-driven applications.

---

**Project Name:** Library Management System  
**Language:** C++  
**Project Type:** Console-Based Application  
**Purpose:** Academic and learning project
