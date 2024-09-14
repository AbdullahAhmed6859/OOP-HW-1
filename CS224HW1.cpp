// Author Abdullah Ahmed
// 
#include <iostream>
#include <string>

using namespace std;

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

const string ACTIVE = "Active";
const string FROZEN = "Frozen";

char alphaHoles[7] = "ADOPQR";

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


void customerMenu();

void employeeMenu();

void inputRole(unsigned short int &role);

void bankAction(unsigned int role, unsigned int choice);

void inputChoice(short unsigned int &choice);

int main() {
    unsigned short int role, choice;
    bool run = true;
    cout << "Welcome to the Bank Simulation Program!" << endl;
    inputRole(role);

    while (run) {
        if (role == CUSTOMER)
            customerMenu();
        else if (role == EMPLOYEE)
            employeeMenu();

        inputChoice(choice);

        if (choice == EXIT)
            run = false;
        else if (choice == ROLE_MENU)
            inputRole(role);
        else
            bankAction(role, choice);
    }

    return 0;
}

void doubleCapacity() {
    accountsCapacity *= 2;
    auto *temp = new BankAccount[accountsCapacity];

    for (int i = 0; i < numAccounts; i++)
        temp[i] = accounts[i];

    delete[] accounts;
    accounts = temp;
    cout << accountsCapacity;
}

void inputVar(unsigned short int &var, const string &name, const int lowerBound, const int upperBound) {
    cin >> var;

    while (var < lowerBound || var > upperBound) {
        cout << "Invalid " << name << ". Enter a " << name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}

void inputVar(unsigned int &var, const string &name, const int lowerBound, const int upperBound) {
    cin >> var;

    while (var < lowerBound || var > upperBound) {
        cout << "Invalid " << name << ". Enter a " << name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}

void inputChoice(short unsigned int &choice) {
    cout << "Enter your choice:";
    inputVar(choice, "choice", MIN_CHOICE, MAX_CHOICE);
    system("cls");
}

void inputRole(unsigned short int &role) {
    cout << "Enter your role (" << CUSTOMER << ") for Customer, (" << EMPLOYEE << ") for Employee:";
    inputVar(role, "choice", CUSTOMER, EMPLOYEE);
    system("cls");
}


void inputName(string &name) {
    cout << "Enter your name (between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN << " allowed):";
    cin.ignore();
    getline(cin >> ws, name);

    while (name.length() < MIN_NAME_LEN || name.length() > MAX_NAME_LEN) {
        cout << "Try again, Name length is not between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN << ":";
        getline(cin >> ws, name);
    }
}


void inputStatus(string &status) {
    cout << "Enter new Status (Active/Frozen):";
    cin.ignore();
    getline(cin >> ws, status);
    while (status != ACTIVE && status != FROZEN) {
        cout << "Try again, status can either be 'Active' or 'Frozen':";
        getline(cin >> ws, status);
    }
}

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

void inputAccountNumber(unsigned int &accNumber) {
    cout << "Please enter your Account Number:";
    inputVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);
}

unsigned int findAccountIndex(const unsigned int accNumber) {
    const unsigned int i = accNumber - MIN_ACCOUNT_NUMBER;

    if (!accounts[i].exists())
        return -1;

    return i;
}

void customerMenu() {
    cout << "CUSTOMER MENU" << endl << endl;

    cout << "1. Open Account" << endl;
    cout << "2. Deposit Amount" << endl;
    cout << "3. Withdraw Amount" << endl;
    cout << "4. Generate Account Statement" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
}

void openAccount() {
    string accountName;
    if (numAccounts >= accountsCapacity * 3 / 4) doubleCapacity();
    cout << "OPEN ACCOUNT" << endl << endl;

    inputName(accountName);
    const unsigned int newAccNum = MIN_ACCOUNT_NUMBER + numAccounts;

    try {
        accounts[numAccounts].setName(accountName);
        accounts[numAccounts].setAccountNumber(newAccNum);
    } catch (const invalid_argument &e) {
        cout << e.what();
    }

    numAccounts++;

    cout << "Account Opened" << endl;
    cout << "Name: " << accountName << endl;
    cout << "Account Number: " << newAccNum << endl;
}

void depositAmount() {
    double amount;
    unsigned int accNumber = 0;
    cout << "DEPOSIT AMOUNT" << endl << endl;
    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist" << endl;
        cin.ignore();
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot deposit funds" << endl;
        cin.ignore();
        return;
    }

    inputAmount(amount);

    try {
        accounts[i].deposit(amount);
    } catch (invalid_argument &e) {
        cout << e.what();
    } catch (runtime_error &e) {
        cout << e.what();
    }

    cout << "Amount Deposited. Current Balance: " << accounts[i].getBalance() << endl;
}

void withdrawAmount() {
    double amount;
    unsigned int accNumber;
    cout << "WITHDRAW AMOUNT" << endl << endl;

    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist, cannot deposit funds" << endl;
        cin.ignore();
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot withdraw Funds" << endl;
        cin.ignore();
        return;
    }

    inputAmount(amount);

    try {
        accounts[i].withdraw(amount);
    } catch (runtime_error &e) {
        cout << e.what();
    } catch (invalid_argument &e) {
        cout << e.what();
    }
}

void generateAccountStatement() {
    string accountName;
    bool found = false;

    cout << "GENERATE ACCOUNT STATEMENT" << endl << endl;
    inputName(accountName);

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].getName() == accountName) {
            accounts[i].print();
            found = true;
        }
    }
    if (!found) cout << "No Accounts found with this name..." << endl;
}

void employeeMenu() {
    cout << "EMPLOYEE MENU" << endl << endl;

    cout << "1. View All Accounts" << endl;
    cout << "2. Deduct Tax" << endl;
    cout << "3. Add Bonus" << endl;
    cout << "4. Change Account Status" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
}

void viewAllAccounts() {
    cout << "VIEW ALL ACCOUNTS" << endl << endl;
    for (int i = 0; i < numAccounts; i++)
        accounts[i].print();

    cin.ignore();
}

void deductTax() {
    cout << "DEDUCT TAX" << endl << endl;

    unsigned int count = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].withdraw(accounts[i].getBalance() * TAX);
            count++;
        }
    }
    cout << "Tax Deducted from " << count << " account(s)" << endl;
    cin.ignore();
}

void addBonus() {
    cout << "ADD BONUS" << endl << endl;
    unsigned int count = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].deposit(accounts[i].getBalance() * BONUS);
            count++;
        }
    }
    cout << "Bonus Added to " << count << " account(s)" << endl;
    cin.ignore();
}


void changeAccountStatus() {
    string status;
    unsigned int accNumber;
    cout << "CHANGE ACCOUNT STATUS" << endl << endl;

    inputAccountNumber(accNumber);
    const unsigned int i = findAccountIndex(accNumber);

    if (i == -1) {
        cout << "Account does not exist, cannot change status" << endl;
        cin.ignore();
        return;
    }

    inputStatus(status);

    try {
        accounts[i].setAccountStatus(status);
        cout << "Account Status Changed to " << status << endl;
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
    }
}

void customerAction(const unsigned int choice) {
    if (choice == 1) openAccount();
    else {
        if (numAccounts == 0) {
            cout << "You must open an account first..." << endl;
            cin.ignore();
            return;
        }
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

void employeeActions(const unsigned int choice) {
    if (numAccounts == 0) {
        cout << "No Accounts were found..." << endl;
        cin.ignore();
        return;
    }
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

void bankAction(const unsigned int role, const unsigned int choice) {
    if (role == CUSTOMER)
        customerAction(choice);
    else if (role == EMPLOYEE)
        employeeActions(choice);

    if (choice != ROLE_MENU) {
        cout << endl;
        cout << "PRESS ENTER TO CONTINUE";
        cin.get();
    }
    system("cls");
}
