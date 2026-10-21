#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
// BOOK
class Book
{
public:
    int book_id;
    string title, author, isbn;
    float price;

    void input()
    {
        cout << "Enter Book ID: ";
        cin >> book_id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter ISBN: ";
        getline(cin, isbn);

        cout << "Enter Price: ";
        cin >> price;
    }

    void save()
    {
        ofstream file("books.txt", ios::app);

        file << book_id << "|"
             << title << "|"
             << author << "|"
             << isbn << "|"

             << price << endl;

        file.close();
    }
};

// COPY
class Copy
{
public:
    int copy_id;
    int book_id;
    string rack_no;
    string status;

    void input()
    {
        cout << "Enter Copy ID: ";
        cin >> copy_id;

        cout << "Enter Book ID (must exist): ";
        cin >> book_id;
        cin.ignore();

        cout << "Enter Rack Number: ";
        getline(cin, rack_no);

        status = "available"; // default
    }

    void save()
    {
        ofstream file("copies.txt", ios::app);

        file << copy_id << "|"
             << book_id << "|"
             << rack_no << "|"
             << status << endl;

        file.close();
    }
};

// MEMBER
class Member
{
public:
    int member_id;
    string name, address, phone, email;
    string registration_date;
    bool paid_status;

    void input()
    {
        cout << "Enter Member ID: ";
        cin >> member_id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Email: ";
        getline(cin, email);

        registration_date = "today"; // simplified
        paid_status = false;
    }

    void save()
    {
        ofstream file("members.txt", ios::app);

        file << member_id << "|"
             << name << "|"
             << address << "|"
             << phone << "|"
             << email << "|"
             << registration_date << "|"
             << paid_status << endl;

        file.close();
    }
};

// ISSUE RECORD
class IssueRecord
{
public:
    int issue_id;
    int copy_id;
    int member_id;
    string issue_date;
    string return_date;
    string actual_return_date;
    float fine_amount;

    void save()
    {
        ofstream file("issues.txt", ios::app);

        file << issue_id << "|"
             << copy_id << "|"
             << member_id << "|"
             << issue_date << "|"
             << return_date << "|"
             << actual_return_date << "|"
             << fine_amount << endl;

        file.close();
    }
};

// PAYMENT
class Payment
{
public:
    int payment_id;
    int member_id;
    float amount;
    string transaction_time;
    string receipt_number;
    string date;

    void input()
    {
        cout << "Enter Payment ID: ";
        cin >> payment_id;

        cout << "Enter Member ID: ";
        cin >> member_id;

        cout << "Enter Amount: ";
        cin >> amount;

        transaction_time = "now";
        receipt_number = "R" + to_string(payment_id);
        date = "today";
    }

    void save()
    {
        ofstream file("payments.txt", ios::app);

        file << payment_id << "|"
             << member_id << "|"
             << amount << "|"
             << transaction_time << "|"
             << receipt_number << "|"
             << date << endl;

        file.close();
    }
};

class Library
{
public:
    bool idExists(string filename, int id)
    {
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            int existing_id = stoi(line.substr(0, line.find('|')));
            if (existing_id == id)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
    bool login()
    {
        string username, password;

        cout << "===== LIBRARY LOGIN =====\n";
        

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        // Hardcoded credentials
        if (username == "admin" && password == "1234")
        {
            cout << " Login Successful!\n";
            return true;
        }
        else
        {
            cout << " Invalid Credentials!\n";
            return false;
        }
    }
    string getTodayDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);

        return to_string(now->tm_mday) + "/" +
               to_string(now->tm_mon + 1) + "/" +
               to_string(now->tm_year + 1900);
    }
    int getAvailableCopy(int book_id)
    {
        ifstream file("copies.txt");
        string line;

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            int c_book_id = stoi(data[1]);
            string status = data[3];

            if (c_book_id == book_id && status == "available")
            {
                file.close();
                return stoi(data[0]); // return copy_id
            }
        }

        file.close();
        return -1;
    }
    void updateCopyStatus(int copy_id, string new_status)
    {
        ifstream in("copies.txt");
        ofstream out("temp.txt");

        string line;

        while (getline(in, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (stoi(data[0]) == copy_id)
            {
                data[3] = new_status;
            }

            for (int i = 0; i < data.size(); i++)
            {
                out << data[i];
                if (i != data.size() - 1)
                    out << "|";
            }
            out << endl;
        }

        in.close();
        out.close();

        remove("copies.txt");
        rename("temp.txt", "copies.txt");
    }

int getNextIssueId()
{
    ifstream file("issues.txt");
    string line;
    int last_id = 0;

    while (getline(file, line))
    {
        int id = stoi(line.substr(0, line.find('|')));
        last_id = id;
    }

    file.close();
    return last_id + 1;
}

   string addDays(string date, int days)
{
    int d, m, y;
    sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);

    d = d + days;   // simple add

    
    if (d > 30)
    {
        d = d - 30;
        m = m + 1;
    }

    if (m > 12)
    {
        m = 1;
        y = y + 1;
    }

    return to_string(d) + "/" + to_string(m) + "/" + to_string(y);
}
    int convertToDays(string date)
    {
        int d, m, y;
        sscanf(date.c_str(), "%d/%d/%d", &d, &m, &y);

        return y * 365 + m * 30 + d; // simple calculation
    }
    int calculateFine(string due_date, string today)
    {
        int due_days = convertToDays(due_date);
        int today_days = convertToDays(today);

        int late_days = today_days - due_days;

        if (late_days > 0)
            return late_days * 5;
        else
            return 0;
    }

    void returnBook()
    {
        int copy_id;
        cout << "Enter Copy ID: ";
        cin >> copy_id;

        ifstream in("issues.txt");
        ofstream out("temp.txt");

        string line;
        string today = getTodayDate();

        bool found = false;

        while (getline(in, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            int c_id = stoi(data[1]);

            // Find active issue (not returned yet)
            if (c_id == copy_id && data[5] == "Not Returned")
            {
                found = true;

                string due_date = data[4];
                int fine = calculateFine(due_date, today);

                data[5] = today;           // actual return date
                data[6] = to_string(fine); // fine amount

                cout << " Book Returned!\n";
                cout << "Fine = ₹" << fine << endl;

                // Update copy status
                updateCopyStatus(copy_id, "available");
            }

            // Write updated record
            for (int i = 0; i < data.size(); i++)
            {
                out << data[i];
                if (i != data.size() - 1)
                    out << "|";
            }
            out << endl;
        }

        if (!found)
        {
            cout << " No active issue found!\n";
        }

        in.close();
        out.close();

        remove("issues.txt");
        rename("temp.txt", "issues.txt");
    }
    void issueBook()
    {
        int member_id, book_id;

        cout << "Enter Member ID: ";
        cin >> member_id;

        if (!isMemberPaid(member_id))
        {
            cout << " Member has not paid!\n";
            return;
        }

        cout << "Enter Book ID: ";
        cin >> book_id;

        int copy_id = getAvailableCopy(book_id);

        if (copy_id == -1)
        {
            cout << " No available copy!\n";
            return;
        }

        IssueRecord issue;

        do
        {
            issue.issue_id = getNextIssueId();
        } while (idExists("issues.txt", issue.issue_id));

        issue.copy_id = copy_id;
        issue.member_id = member_id;

        issue.issue_date = getTodayDate();

        //  set due date = issue date + 7 days
        issue.return_date = addDays(issue.issue_date, 7);

        issue.actual_return_date = "Not Returned";
        issue.fine_amount = 0;

        issue.save();

        updateCopyStatus(copy_id, "issued");

        cout << " Book Issued Successfully!\n";
        cout << "Copy ID: " << copy_id << endl;
        cout << "Due Date: " << issue.return_date << endl; //  show due date
    }

    void viewMembers()
    {
        ifstream file("members.txt");
        string line;

        cout << "\n--- MEMBER LIST ---\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
    void makePayment()
    {
        Payment p;
        p.input();

        if (idExists("payments.txt", p.payment_id))
        {
            cout << " Duplicate Payment ID not allowed!\n";
            return;
        }

        p.save();

        ifstream in("members.txt");
        ofstream out("temp.txt");

        string line;

        while (getline(in, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (stoi(data[0]) == p.member_id)
            {
                data[6] = "1"; // paid = true
            }

            for (int i = 0; i < data.size(); i++)
            {
                out << data[i];
                if (i != data.size() - 1)
                    out << "|";
            }
            out << endl;
        }

        in.close();
        out.close();

        remove("members.txt");
        rename("temp.txt", "members.txt");

        cout << " Payment Successful!\n";
    }
    bool isMemberPaid(int member_id)
    {
        ifstream file("members.txt");
        string line;

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (stoi(data[0]) == member_id)
            {
                file.close();
                return data[6] == "1";
            }
        }

        file.close();
        return false;
    }

    void issuedBooks()
    {
        ifstream file("issues.txt");
        string line;

        cout << "\n--- ISSUED BOOKS ---\n";

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (data[5] == "Not Returned")
            {
                cout << "Issue ID: " << data[0]
                     << " | Copy ID: " << data[1]
                     << " | Member ID: " << data[2]
                     << " | Issue Date: " << data[3]
                     << " | Due Date: " << data[4] //  show due date
                     << endl;
            }
        }

        file.close();
    }

    void overdueBooks()
    {
        ifstream file("issues.txt");
        string line;

        string today = getTodayDate();

        cout << "\n--- OVERDUE BOOKS ---\n";

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (data[5] == "Not Returned")
            {
                string issue_date = data[3];

                int fine = calculateFine(issue_date, today);

                if (fine > 0)
                {
                    cout << line << " | Fine Till Now: " << fine << endl;
                }
            }
        }

        file.close();
    }

    void paidMembers()
    {
        ifstream file("members.txt");
        string line;

        cout << "\n--- PAID MEMBERS ---\n";

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            if (data[6] == "1")
            {
                cout << line << endl;
            }
        }

        file.close();
    }
    void totalFines()
    {
        ifstream file("issues.txt");
        string line;

        int total = 0;

        while (getline(file, line))
        {
            vector<string> data;
            string temp = "";

            for (char c : line)
            {
                if (c == '|')
                {
                    data.push_back(temp);
                    temp = "";
                }
                else
                    temp += c;
            }
            data.push_back(temp);

            total += stoi(data[6]); // fine amount
        }

        file.close();

        cout << "\nTotal Fine Collected = " << total << endl;
    }
    void addMember()
    {
        Member m;
        m.input();

        if (idExists("members.txt", m.member_id))
        {
            cout << " Duplicate Member ID not allowed!\n";
            return;
        }

        m.save();
        cout << " Member Added Successfully!\n";
    }

    void addBook()
    {
        Book b;
        b.input();

        if (idExists("books.txt", b.book_id))
        {
            cout << " Duplicate Book ID not allowed!\n";
            return;
        }

        b.save();
        cout << " Book Added Successfully!\n";
    }
    bool bookExists(int book_id)
    {
        ifstream file("books.txt");
        string line;

        while (getline(file, line))
        {
            int id = stoi(line.substr(0, line.find('|')));
            if (id == book_id)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
    void addCopy()
    {
        Copy c;
        c.input();

        if (idExists("copies.txt", c.copy_id))
        {
            cout << " Duplicate Copy ID not allowed!\n";
            return;
        }

        if (!bookExists(c.book_id))
        {
            cout << " Book ID does not exist!\n";
            return;
        }

        c.save();
        cout << " Copy Added Successfully!\n";
    }

    void viewCopies()
    {
        ifstream file("copies.txt");
        string line;

        cout << "\n--- COPY LIST ---\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
    void viewBooks()
    {
        ifstream file("books.txt");
        string line;

        cout << "\n--- BOOK LIST ---\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
};
int main()
{
    Library lib;
    int choice;
    while (true)
    {
        if (lib.login())
        {
            break;
        }
        cout << "Try Again...\n";
    }

    do
    {
        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Add Copy\n";
        cout << "4. View Copies\n";
        cout << "5. Add Member\n";
        cout << "6. View Members\n";
        cout << "7. Make Payment\n";
        cout << "8. Issue Book\n";
        cout << "9. Return Book\n";
        cout << "10. Issued Books Report\n";
        cout << "11. Overdue Books\n";
        cout << "12. Paid Members\n";
        cout << "13. Total Fines\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.viewBooks();
            break;
        case 3:
            lib.addCopy();
            break;
        case 4:
            lib.viewCopies();
            break;
        case 5:
            lib.addMember();
            break;
        case 6:
            lib.viewMembers();
            break;
        case 7:
            lib.makePayment();
            break;
        case 8:
            lib.issueBook();
            break;
        case 9:
            lib.returnBook();
            break;
        case 10:
            lib.issuedBooks();
            break;
        case 11:
            lib.overdueBooks();
            break;
        case 12:
            lib.paidMembers();
            break;
        case 13:
            lib.totalFines();
            break;
        }

    } while (choice != 0);

    return 0;
}