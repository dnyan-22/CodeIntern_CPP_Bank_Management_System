#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class BankAccount {
private:
    string holderName;
    long long accountNumber;
    string accountType;
    double balance;

public:
    void openAccount() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n--- Open New Bank Account ---\n";
        cout << "Enter Account Holder Name: ";
        getline(cin, holderName);

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Account Type (Savings/Current): ";
        cin >> accountType;

        cout << "Enter Initial Deposit (Minimum 500): ";
        cin >> balance;

        if (balance < 500) {
            cout << "Minimum balance must be 500. Setting balance to 500.\n";
            balance = 500;
        }

        cout << "Account Successfully Created!\n";
    }

    void display() const {
        cout << "\n----------------------------\n";
        cout << "Account Holder : " << holderName << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Type   : " << accountType << endl;
        cout << "Available Bal. : " << balance << endl;
        cout << "----------------------------\n";
    }

    long long getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        cout << "Amount deposited successfully.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }
        if (balance - amount < 500) {
            cout << "Withdrawal denied! Minimum balance of 500 must be maintained.\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawal successful.\n";
    }
};

int main() {
    vector<BankAccount> accounts;
    int choice;

    do {
        cout << "\n========= BANK MANAGEMENT SYSTEM =========\n";
        cout << "1. Open New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Amount\n";
        cout << "4. Withdraw Amount\n";
        cout << "5. Balance Enquiry\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            BankAccount acc;
            acc.openAccount();
            accounts.push_back(acc);
        }

        else if (choice == 2) {
            if (accounts.empty()) {
                cout << "No accounts available!\n";
            } else {
                for (const auto &acc : accounts)
                    acc.display();
            }
        }

        else if (choice >= 3 && choice <= 5) {
            if (accounts.empty()) {
                cout << "No accounts available!\n";
                continue;
            }

            long long accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;

            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNo) {
                    found = true;

                    if (choice == 3) {
                        double amt;
                        cout << "Enter Deposit Amount: ";
                        cin >> amt;
                        acc.deposit(amt);
                    }
                    else if (choice == 4) {
                        double amt;
                        cout << "Enter Withdrawal Amount: ";
                        cin >> amt;
                        acc.withdraw(amt);
                    }
                    else if (choice == 5) {
                        acc.display();
                    }
                    break;
                }
            }

            if (!found) {
                cout << "Account not found!\n";
            }
        }

        else if (choice == 6) {
            cout << "Thank you for banking with us!\n";
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
