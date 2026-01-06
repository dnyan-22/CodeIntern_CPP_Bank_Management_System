#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// ---------- Account Class ----------
class Account {
public:
    int accountNumber;
    string name;
    double balance;

    Account() {
        balance = 0.0;
    }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        cout << "Amount deposited successfully!\n";
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amount;
        cout << "Amount withdrawn successfully!\n";
    }

    // Display account info
    void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Balance       : " << balance << endl;
    }
};

// ---------- Function Prototypes ----------
void addAccount();
void displayAccount();
void depositMoney();
void withdrawMoney();
void saveToFile();
void loadFromFile();
void clearInputBuffer();

// ---------- Global Variables ----------
const string FILENAME = "accounts.txt";
Account accounts[100];
int accountCount = 0;

// ---------- Utility Functions ----------
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Load accounts from file
void loadFromFile() {
    ifstream file(FILENAME);
    if (!file) return;
    file >> accountCount;
    for (int i = 0; i < accountCount; i++) {
        file >> accounts[i].accountNumber;
        file.ignore();
        getline(file, accounts[i].name);
        file >> accounts[i].balance;
    }
    file.close();
}

// Save accounts to file
void saveToFile() {
    ofstream file(FILENAME);
    file << accountCount << endl;
    for (int i = 0; i < accountCount; i++) {
        file << accounts[i].accountNumber << endl;
        file << accounts[i].name << endl;
        file << accounts[i].balance << endl;
    }
    file.close();
}

// ---------- Feature Implementations ----------
void addAccount() {
    Account acc;
    acc.accountNumber = accountCount + 1;

    clearInputBuffer();
    cout << "Enter Account Holder Name: ";
    getline(cin, acc.name);

    cout << "Enter Initial Deposit: ";
    cin >> acc.balance;
    if (acc.balance < 0) {
        cout << "Deposit cannot be negative. Setting balance to 0.\n";
        acc.balance = 0;
    }

    accounts[accountCount] = acc;
    accountCount++;
    saveToFile();
    cout << "Account created successfully! Account Number: " << acc.accountNumber << endl;
}

void displayAccount() {
    int accNo;
    cout << "Enter Account Number to display: ";
    cin >> accNo;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNo) {
            accounts[i].display();
            return;
        }
    }
    cout << "Account not found.\n";
}

void depositMoney() {
    int accNo;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNo;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNo) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[i].deposit(amount);
            saveToFile();
            return;
        }
    }
    cout << "Account not found.\n";
}

void withdrawMoney() {
    int accNo;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNo;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNo) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            accounts[i].withdraw(amount);
            saveToFile();
            return;
        }
    }
    cout << "Account not found.\n";
}

// ---------- Main Menu ----------
int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Add Account\n";
        cout << "2. Display Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addAccount(); break;
            case 2: displayAccount(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
