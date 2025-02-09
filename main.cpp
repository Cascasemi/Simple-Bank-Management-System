#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class BankAccount {
private:
    long long accountNumber; // 10-digit bank number
    string accountHolderName;
    double balance;

public:
    BankAccount(long long accNum, string accHolderName) : accountNumber(accNum), accountHolderName(accHolderName), balance(0) {}

    long long getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully. New balance: GHS " << balance << endl;
        } else {
            cout << "Invalid deposit amount. Please try again." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Amount withdrawn successfully. New balance: GHS " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance. Please try again." << endl;
        }
    }
};

class BankManagementSystem {
private:
    vector<BankAccount> accounts;
    long long nextAccountNumber;

public:
    BankManagementSystem() {
        srand(time(0)); // Seed the random number generator with the current time
        nextAccountNumber = rand() % 10000000000 + 1000000000; // Generate a random 10-digit number
    }

    void createAccount() {
        string name;
        cout << "Enter account holder name: ";
        cin.ignore(); // Ignore any remaining newline character from previous inputs
        getline(cin, name);

        BankAccount newAccount(nextAccountNumber, name);
        accounts.push_back(newAccount);
        nextAccountNumber++;

        cout << "Account created successfully. Account number: " << newAccount.getAccountNumber() << endl;
    }

    BankAccount* findAccount(long long accNum) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    void displayAccountDetails(long long accNum) {
        BankAccount* account = findAccount(accNum);
        if (account != nullptr) {
            cout << "Account Number: " << account->getAccountNumber() << endl;
            cout << "Account Holder Name: " << account->getAccountHolderName() << endl;
            cout << "Account Balance: GHS " << account->getBalance() << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }

    void performDeposit(long long accNum, double amount) {
        BankAccount* account = findAccount(accNum);
        if (account != nullptr) {
            account->deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void performWithdrawal(long long accNum, double amount) {
        BankAccount* account = findAccount(accNum);
        if (account != nullptr) {
            account->withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }
};

int main() {
    BankManagementSystem bank;

    int choice;
    do {
        cout << "\nBank Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Account Details\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                long long accNum;
                cout << "Enter account number: ";
                cin >> accNum;
                bank.displayAccountDetails(accNum);
                break;
            case 3:
                long long depositAccNum;
                double depositAmount;
                cout << "Enter account number: ";
                cin >> depositAccNum;
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                bank.performDeposit(depositAccNum, depositAmount);
                break;
            case 4:
                long long withdrawAccNum;
                double withdrawAmount;
                cout << "Enter account number: ";
                cin >> withdrawAccNum;
                cout << "Enter amount to withdraw: ";
                cin >> withdrawAmount;
                bank.performWithdrawal(withdrawAccNum, withdrawAmount);
                break;
            case 5:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
