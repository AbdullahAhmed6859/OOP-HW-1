// Author: Abdullah Ahmed
// ID: aa09303
// Section: L1

// This program simulates a simple bank system where users can take on different roles:
// Customers can open accounts, deposit, withdraw, and generate account statements.
// Employees can view all accounts, deduct taxes, add bonuses, and change account statuses.
// The system runs until the user chooses to exit.


#include <iostream>
#include <string>
using namespace std;

// defining constant
constexpr unsigned int MIN_ACCOUNT_NUMBER = 10000000;
constexpr unsigned int MAX_ACCOUNT_NUMBER = 99999999;
constexpr unsigned int MIN_NAME_LEN = 3;
constexpr unsigned int MAX_NAME_LEN = 30;
constexpr float BONUS = 0.1;
constexpr float TAX = 0.1;
constexpr short int EXIT = 6;
constexpr short int ROLE_MENU = 5;
constexpr short int CUSTOMER = 1;
constexpr short int EMPLOYEE = 2;
constexpr short int MIN_CHOICE = 1;
constexpr short int MAX_CHOICE = 6;

// account status types
const string ACTIVE = "Active";
const string FROZEN = "Frozen";

struct BankAccount {
private:
    string name;
    unsigned int accountNumber = 0;
    string status = ACTIVE;
    double balance = 0;

public:
    string getName() {
        return name;
    }

    string getStatus() {
        return status;
    }

    double getBalance() const {
        return balance;
    }

    bool isActive() const {
        return status == ACTIVE;
    }

    bool exists() const {
        return accountNumber != 0;
    }

    bool hasFunds(const double &amount = 0) const {
        return amount <= balance;
    }

    void setName(const string &newName) {
        if (newName.length() < MIN_NAME_LEN || newName.length() > MAX_NAME_LEN)
            throw invalid_argument(newName.length() + " is not a valid name length");

        name = newName;
    }

    void setAccountNumber(const unsigned int newAccountNumber) {
        if (newAccountNumber < MIN_ACCOUNT_NUMBER || newAccountNumber > MAX_ACCOUNT_NUMBER)
            throw invalid_argument(to_string(newAccountNumber) + "is not a valid Account number");

        accountNumber = newAccountNumber;
    }

    void setAccountStatus(const string &newStatus) {
        if (status != ACTIVE && status != FROZEN)
            throw invalid_argument(newStatus + " is not a valid status");

        status = newStatus;
    }

    void deposit(const double amount) {
        if (status == FROZEN)
            throw runtime_error("Cannot add balance to a frozen account.");
        if (amount < 0) {
            throw invalid_argument("Amount: " + to_string(amount) + " cannot be deposited to a bank account");
        }

        balance += amount;
    }

    void withdraw(const double amount) {
        if (status == FROZEN)
            throw runtime_error("Cannot subtract balance from a frozen account.");
        if (amount < 0) {
            throw invalid_argument("Amount: " + to_string(amount) + " cannot be withdrawn from a bank account");
        }

        balance -= amount;
    }


    void print() const {
        cout << "Account Number: " << accountNumber << " Name: " << name
                << " Balance: " << balance << " Status: " << status << endl;
    }
};

unsigned int accountsCapacity = 4;
unsigned int numAccounts = 0;
BankAccount *accounts = new BankAccount[accountsCapacity];

// functions used in the main program declared above
void customerMenu();
void employeeMenu();
void inputRole(unsigned short int &role);
void bankAction(unsigned int role, unsigned int choice);
void inputChoice(short unsigned int &choice);

int main() {
    unsigned short int role, choice;
    bool run = true;
    cout << "Welcome to the Bank Simulation Program!" << endl;
    inputRole(role); // input the role from the user

    while (run) {
        // display the relenvant manu
        if (role == CUSTOMER)
            customerMenu();
        else if (role == EMPLOYEE)
            employeeMenu();

        // input the choice from the user
        inputChoice(choice);

        if (choice == EXIT)
            run = false; // exit the program

        else if (choice == ROLE_MENU)
            inputRole(role); // input the role from the user
        else
            bankAction(role, choice); // call actions based on role and choice
    }

    return 0;
}

// doubles the size of the array bank accounts array
void doubleCapacity() {
    // allocation twice the memory for bank accounts in the heap
    accountsCapacity *= 2;
    auto *temp = new BankAccount[accountsCapacity];

    // copy bank accounts in the new array
    for (int i = 0; i < numAccounts; i++)
        temp[i] = accounts[i];

    // delete the old array from the heap and store the pointer to the new array in accounts
    delete[] accounts;
    accounts = temp;
}


void inputVar(unsigned short int &var, const string &name, const int lowerBound, const int upperBound) {
    cin >> var;

    while (var < lowerBound || var > upperBound) {
        cout << "Invalid " << name << ". Enter a " << name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}

// input an unsigned int with its lower and upper bound and name
void inputVar(unsigned int &var, const string &name, const int lowerBound, const int upperBound) {
    cin >> var;

    while (var < lowerBound || var > upperBound) {
        cout << "Invalid " << name << ". Enter a " << name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}

// input choice from the user
void inputChoice(short unsigned int &choice) {
    cout << "Enter your choice:";
    inputVar(choice, "choice", MIN_CHOICE, MAX_CHOICE);
    system("cls"); // clear the screen
}

// input role from the user
void inputRole(unsigned short int &role) {
    cout << "Enter your role (" << CUSTOMER << ") for Customer, (" << EMPLOYEE << ") for Employee:";
    inputVar(role, "choice", CUSTOMER, EMPLOYEE);
    system("cls"); // clear the screen
}

// input name from the user
void inputName(string &name) {
    cout << "Enter your name (between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN << " allowed):";
    cin.ignore();
    getline(cin >> ws, name);

    while (name.length() < MIN_NAME_LEN || name.length() > MAX_NAME_LEN) {
        cout << "Try again, Name length is not between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN << ":";
        getline(cin >> ws, name);
    }
}

// input status from the user
void inputStatus(string &status) {
    cout << "Enter new Status (Active/Frozen):";
    cin.ignore();
    getline(cin >> ws, status);

    while (status != ACTIVE && status != FROZEN) {
        cout << "Try again, status can either be 'Active' or 'Frozen':";
        getline(cin >> ws, status);
    }
}

// input amount from the user
void inputAmount(double &amount) {
    cout << "Please enter amount:";
    cin.ignore();
    cin >> amount;

    while (amount < 0) {
        cout << "Amount should not be less than 0:";
        cin >> amount;
    }
    cin.ignore();
}

// input account number from the user
void inputAccountNumber(unsigned int &accNumber) {
    cout << "Please enter your Account Number:";
    inputVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);
}

// calculate the account index of the array using the account number
unsigned int findAccountIndex(const unsigned int accNumber) {
    // Convert account number to index based on a predefined range
    if (accNumber < MIN_ACCOUNT_NUMBER || accNumber > MAX_ACCOUNT_NUMBER)
        return -1;

    const unsigned int i = accNumber - MIN_ACCOUNT_NUMBER;
    if (!accounts[i].exists())
        return -1;

    return i;
}

// show the customer menu to the user
void customerMenu() {
    cout << "CUSTOMER MENU" << endl << endl;

    cout << "1. Open Account" << endl;
    cout << "2. Deposit Amount" << endl;
    cout << "3. Withdraw Amount" << endl;
    cout << "4. Generate Account Statement" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
}

// Function to open a new bank account
// Takes customer name as input, assigns a new account number, and stores it in the accounts array
void openAccount() {
    string accountName;
    // if the array is 75% ful double its capacity
    if (numAccounts >= accountsCapacity * 3 / 4)
        doubleCapacity();

    cout << "OPEN ACCOUNT" << endl << endl;

    // if accounts limit is reached donot proceed
    if (numAccounts >= MAX_ACCOUNT_NUMBER) {
        cout << "Accounts limit reached" << endl;
        return;
    }

    inputName(accountName);
    const unsigned int newAccNum = MIN_ACCOUNT_NUMBER + numAccounts;

    try {
        accounts[numAccounts].setName(accountName);
        accounts[numAccounts].setAccountNumber(newAccNum);
    } catch (const invalid_argument &e) {
        // Handle cases where an invalid argument is passed
        cout << e.what();
    }

    numAccounts++;

    cout << "Account Opened" << endl;
    cout << "Name: " << accountName << endl;
    cout << "Account Number: " << newAccNum << endl;
}

// Function to deposit amount in a bank account
// Takes an amount as input, deposits it into the account
void depositAmount() {
    double amount;
    unsigned int accNumber = 0;
    cout << "DEPOSIT AMOUNT" << endl << endl;
    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist" << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot deposit funds" << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }

    inputAmount(amount);

    try {
        accounts[i].deposit(amount);
    } catch (invalid_argument &e) {
        // Handle cases where an invalid argument is passed
        cout << e.what();
    } catch (runtime_error &e) {
        // Handle runtime errors, such as when trying to deposit into a frozen account
        cout << e.what();
    }

    cout << "Amount Deposited. Current Balance: " << accounts[i].getBalance() << endl;
}

// Function to withdraw amount in a bank account
// Takes an amount as input, withdraws it from the account
void withdrawAmount() {
    double amount;
    unsigned int accNumber;
    cout << "WITHDRAW AMOUNT" << endl << endl;

    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist, cannot deposit funds" << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot withdraw Funds" << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }

    inputAmount(amount);

    try {
        accounts[i].withdraw(amount);
    } catch (const runtime_error &e) {
        // Handle runtime errors, such as when trying to deposit into a frozen account
        cout << e.what();
    } catch (const invalid_argument &e) {
        // Handle cases where an invalid argument is passed
        cout << e.what();
    }
}

// takes a name as input and finds all the accounts with that name
// prints their information
void generateAccountStatement() {
    string accountName;
    bool found = false;

    cout << "GENERATE ACCOUNT STATEMENT" << endl << endl;
    inputName(accountName);

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].getName() == accountName) {
            accounts[i].print();
            found = true; // set to true so it does not output the accounts not found message
        }
    }

    if (!found)
        cout << "No Accounts found with this name..." << endl;
}

// shows the employee menu to the user
void employeeMenu() {
    cout << "EMPLOYEE MENU" << endl << endl;

    cout << "1. View All Accounts" << endl;
    cout << "2. Deduct Tax" << endl;
    cout << "3. Add Bonus" << endl;
    cout << "4. Change Account Status" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
}

// prints information of all accounts
void viewAllAccounts() {
    cout << "VIEW ALL ACCOUNTS" << endl << endl;
    for (int i = 0; i < numAccounts; i++)
        accounts[i].print();

    cin.ignore(); // so the user can wait to see the output before the screen clears
}

// charges a percentage tax from all active accounts
void deductTax() {
    cout << "DEDUCT TAX" << endl << endl;

    unsigned int count = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].withdraw(accounts[i].getBalance() * TAX); // charge tax from the account
            count++;
        }
    }
    cout << "Tax Deducted from " << count << " account(s)" << endl;
    cin.ignore(); // so the user can wait to see the output before the screen clears
}

// adds a percentage bonus to all active accounts
void addBonus() {
    cout << "ADD BONUS" << endl << endl;
    unsigned int count = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].deposit(accounts[i].getBalance() * BONUS); // add bonus to the account
            count++;
        }
    }
    cout << "Bonus Added to " << count << " account(s)" << endl;
    cin.ignore(); // so the user can wait to see the output before the screen clears
}

// inputs account status from the user and changes it as the user wants
void changeAccountStatus() {
    string status;
    unsigned int accNumber;
    cout << "CHANGE ACCOUNT STATUS" << endl << endl;

    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist, cannot change status" << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }

    inputStatus(status);

    try {
        accounts[i].setAccountStatus(status);
        cout << "Account Status Changed to " << status << endl;
    } catch (const invalid_argument &e) {
        // Handle cases where an invalid argument is passed
        cout << e.what() << endl;
    }
}

// calls one of the customer actions based on the choice
void customerAction(const unsigned int choice) {
    if (choice == 1) openAccount();
    else {
        if (numAccounts == 0) {
            cout << "You must open an account first..." << endl;
            cin.ignore(); // so the user can wait to see the output before the screen clears
            return;
        }
        // if accounts exist call the relevant action
        switch (choice) {
            case 2:
                depositAmount();
                break;
            case 3:
                withdrawAmount();
                break;
            case 4:
                generateAccountStatement();
                break;
            default:
                break;
        }
    }
}

// calls one of the employee actions based on the choice
void employeeActions(const unsigned int choice) {
    if (numAccounts == 0) {
        cout << "No Accounts were found..." << endl;
        cin.ignore(); // so the user can wait to see the output before the screen clears
        return;
    }
    // if accounts exist call the relevant action
    switch (choice) {
        case 1:
            viewAllAccounts();
            break;
        case 2:
            deductTax();
            break;
        case 3:
            addBonus();
            break;
        case 4:
            changeAccountStatus();
            break;
        default:
            break;
    }
}

// Call the relevant action based on whether the user is a customer or an employee
void bankAction(const unsigned int role, const unsigned int choice) {
    if (role == CUSTOMER)
        customerAction(choice);
    else if (role == EMPLOYEE)
        employeeActions(choice);

    // Prompt user to press ENTER after every action except for returning to the role menu
    if (choice != ROLE_MENU) {
        cout << endl;
        cout << "PRESS ENTER TO CONTINUE";
        cin.get(); // wait for user input
    }
    // Clear the screen after the action is performed
    system("cls");
}
