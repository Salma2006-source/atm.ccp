#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Account {
    string username;
    int pin;
    double balance;
};

void printLine() {
    cout << "----------------------------------------\n";
}

void welcomeMessage() {
    printLine();
    cout << "        Welcome to Simple ATM System     \n";
    printLine();
}

void showMenu() {
    printLine();
    cout << "ATM Main Menu\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Exit\n";
    printLine();
    cout << "Enter your choice: ";
}

int login(Account accounts[], int size) {
    string user;
    int pin;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter PIN: ";
    cin >> pin;
    for (int i = 0; i < size; i++) {
        if (accounts[i].username == user && accounts[i].pin == pin) {
            cout << "\nLogin successful! Welcome, " << user << ".\n";
            return i;
        }
    }
    cout << "Invalid username or PIN!\n";
    return -1;
}

int registerAccount(Account accounts[], int &size, int maxSize) {
    if (size >= maxSize) {
        cout << "Sorry! Cannot add more accounts.\n";
        return -1;
    }
    string newUser;
    int newPin;
    double initialDeposit;
    cout << "\n=== Register New Account ===\n";
    cout << "Enter new username: ";
    cin >> newUser;
    for (int i = 0; i < size; i++) {
        if (accounts[i].username == newUser) {
            cout << "Username already exists! Try again.\n";
            return -1;
        }
    }
    cout << "Set a 4-digit PIN: ";
    cin >> newPin;
    if (cin.fail() || newPin < 1000 || newPin > 9999) {
        cout << "Invalid PIN! Must be 4 digits.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cout << "Enter initial deposit: ";
    cin >> initialDeposit;
    if (cin.fail() || initialDeposit < 0) {
        cout << "Invalid deposit amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    accounts[size].username = newUser;
    accounts[size].pin = newPin;
    accounts[size].balance = initialDeposit;
    cout << "Account created successfully! Welcome, " << newUser << ".\n";
    size++;
    return size - 1;
}

void checkBalance(Account &acc) {
    printLine();
    cout << "Your current balance is: " << acc.balance << " EGP\n";
}

void deposit(Account &acc) {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (!cin.fail() && amount > 0) {
        acc.balance += amount;
        cout << "Deposited " << amount << " EGP successfully.\n";
        checkBalance(acc);
    } else {
        cout << "Invalid amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void withdraw(Account &acc) {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (!cin.fail() && amount > 0 && amount <= acc.balance) {
        acc.balance -= amount;
        cout << "Please collect your cash: " << amount << " EGP\n";
        checkBalance(acc);
    } else if (amount > acc.balance) {
        cout << "Insufficient funds!\n";
    } else {
        cout << "Invalid amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    const int MAX_ACCOUNTS = 10;
    Account accounts[MAX_ACCOUNTS] = {
        {"salma", 1234, 1500.0},
        {"ali",   1111, 2000.0},
        {"nora",  2222, 500.0}
    };
    int size = 3;
    welcomeMessage();
    cout << "Do you have an account? (y/n): ";
    char choice;
    cin >> choice;
    int index = -1;
    if (choice == 'y' || choice == 'Y') {
        index = login(accounts, size);
    } else if (choice == 'n' || choice == 'N') {
        index = registerAccount(accounts, size, MAX_ACCOUNTS);
    } else {
        cout << "Invalid input!\n";
        return 0;
    }
    if (index != -1) {
        int option;
        do {
            showMenu();
            cin >> option;
            if (cin.fail()) {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            switch (option) {
                case 1:
                    checkBalance(accounts[index]);
                    break;
                case 2:
                    deposit(accounts[index]);
                    break;
                case 3:
                    withdraw(accounts[index]);
                    break;
                case 4:
                    cout << "Thank you for using our ATM. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (option != 4);
    } else {
        cout << "Access denied. Please restart program.\n";
    }
    return 0;
}