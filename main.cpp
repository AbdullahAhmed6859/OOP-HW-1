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
const string ACTIVE = "Active";
const string FROZEN = "Frozen";

struct BankAccount {
    string name;
    unsigned int accountNumber = 0;
    double balance = 0;
    string status = ACTIVE;

    void setName(const string& newName) {
        if (newName.length() < MIN_NAME_LEN || newName.length() > MAX_NAME_LEN )
            throw invalid_argument( "Name length has to be between 3 and 30");

        name = newName;
    }

    void setAccountNumber(const unsigned int newAccountNumber) {
        if (newAccountNumber < MIN_ACCOUNT_NUMBER || newAccountNumber > MAX_ACCOUNT_NUMBER)
            throw invalid_argument(to_string(newAccountNumber) + "is not a valid Account number");

        accountNumber = newAccountNumber;
    }

    bool isActive() const {
        return status == ACTIVE;
    }

    bool deposit(const double amount) {
        if (status == FROZEN) return false;
        balance += amount;
        return true;
    }

    bool withdraw(const double amount) {
        if (status == FROZEN || balance < amount) return false;
        balance -= amount;
        return true;
    }

    void changeAccountStatus() {
        status = status == ACTIVE ? FROZEN : ACTIVE;
    }

    void print() const {
        cout << "Acount Number: " << accountNumber<< " Name: " << name
        << " Balance: " << balance << " Status: " << status << endl;
    }
};


constexpr unsigned int accountsCapacity = 10;
BankAccount accounts[accountsCapacity];
unsigned int numAccounts = 0;


void getVar(unsigned short int &var, const string& name, const int lowerBound, const int upperBound) {
    cin >> var;
    while (var < lowerBound or var > upperBound) {
        cout << "Invalid " << name <<". Enter a "<< name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
    cout << endl;
}
void getVar(unsigned int &var, const string& name, const int lowerBound, const int upperBound) {
    cin >> var;
    while (var < lowerBound or var > upperBound) {
        cout << "Invalid " << name <<". Enter a "<< name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
    cout << endl;
}

unsigned int getIndex(const unsigned int accNumber) {
    return accNumber - MIN_ACCOUNT_NUMBER;
}


void roleMenu(unsigned short int &role) {
    cout << "Enter your role (1) for Customer, (2) for Employee:";
    getVar(role, "choice", 1, 2);
}


void customerMenu(unsigned short int &choice) {
    cout << "1. Open Account" << endl;
    cout << "2. Deposit Amount" << endl;
    cout << "3. Withdraw Ammount" << endl;
    cout << "4. Generate Account Statement" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice:";
    getVar(choice, "choice", 1, 6);
}


void openAccount() {
    string accountName;
    cout << "Enter your name (between 3 and 3 character allowed):";
    getline(cin, accountName);

    while(accountName.length() < MIN_NAME_LEN || accountName.length() > MAX_NAME_LEN) {
        cout << "Try again, Name length is not between 3 and 30:";
        getline(cin, accountName);
    }

    const unsigned int newAccNum = MIN_ACCOUNT_NUMBER + numAccounts;

    accounts[numAccounts].setName(accountName);
    accounts[numAccounts].setAccountNumber(newAccNum);

    numAccounts++;
    cout << "Account Opened" << endl;
    cout << "Name: " << accountName << endl;
    cout << "Account Number: " << newAccNum << endl;
}


void depositAmmount() {
    unsigned int accNumber;
    double amount;

    cout << "Please enter your Account Number:";
    getVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);

    cout << "Please enter amount to deposit:";
    cin >> amount;

    accounts[getIndex(accNumber)].deposit(amount);
    cout << "Ammount Depositied" << endl;
}


void withdrawAmmount() {
    unsigned int accNumber;
    double amount;

    cout << "Please enter your Account Number:";
    getVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);

    cout << "Please enter ammount to withdraw";
    cin >> amount;

    const bool success = accounts[getIndex(accNumber)].withdraw(amount);
    if (!success)
        cout << "Amount could not be withdrawn";
    else
        cout << "Ammount Withdrawn" << endl;
}


void generateAccountStatement() {
    string accountName;
    cout << "Enter your name (between 3 and 30 character allowed):";
    getline(cin, accountName);

    while(accountName.length() < MIN_NAME_LEN || accountName.length() > MAX_NAME_LEN) {
        cout << "Try again, Name length is not between 3 and 30:";
        getline(cin, accountName);
    }

    for (int i=0; i<numAccounts; i++) {
        if (accounts[i].name == accountName)
            accounts[i].print();
    }
}


void employeeMenu(unsigned short int &choice) {
    cout << "1. View All Accounts" << endl;
    cout << "2. Deduct Tax" << endl;
    cout << "3. Add Bonus" << endl;
    cout << "4. Change Account Status" << endl;
    cout << "5. Return to Role Menu" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    getVar(choice, "choice", 1, 6);
}


void viewAllAccounts() {
    cout << "Shwoing All Accounts" << endl;
    for (int i=0; i<numAccounts; i++) {
        accounts[i].print();
    }
}


void deductTax() {
    for (int i=0; i<numAccounts; i++) {
        if(accounts[i].isActive()) {
            accounts[i].withdraw(accounts[i].balance * TAX);
        }
    }
    cout << "Tax Deducted" << endl;
}


void addBonus() {
    for (int i=0; i<numAccounts; i++) {
        if(accounts[i].isActive()) {
            accounts[i].deposit(accounts[i].balance * BONUS);
        }
    }
    cout << "Bonus Added" << endl;
}


void changeAccountStatus() {
    unsigned int accNumber;

    cout << "Please enter an Account Number:";
    getVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);

    accounts[numAccounts].changeAccountStatus();
    cout << "Account Status Chnged" << endl;
}

bool bankAction(const unsigned int role, const unsigned int choice) {
    if (role == CUSTOMER) {
        switch (choice) {
            case 1:
                openAccount();
                break;
            case 2:
                depositAmmount();
                break;
            case 3:
                withdrawAmmount();
                break;
            case 4:
                generateAccountStatement();
                break;
            default:
                return false;
        }
    }
    else if (role == EMPLOYEE) {
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
                return false;
        }
    }
    cout << endl;
    return true;
}


int main() {
    unsigned short int role, choice;
    bool run = true;

    // cin.ignore(1000, '\n');
    cout << "Welcome to the Bank Simulation Program!" << endl;
    roleMenu(role);

    while (run) {
        if (role == CUSTOMER) customerMenu(choice);
        else if (role == EMPLOYEE) employeeMenu(choice);

        if (choice == EXIT) run = false;
        else if (choice == ROLE_MENU) roleMenu(role);
        else if (const bool success = bankAction(role, choice); !success) {
            return 1;
        }
    }

    return 0;
}
