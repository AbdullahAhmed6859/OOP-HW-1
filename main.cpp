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

    double getBalance() const {
        return balance;
    }

    void setName(const string& newName) {
        if (newName.length() < MIN_NAME_LEN || newName.length() > MAX_NAME_LEN )
            throw invalid_argument( "Name length has to be between " + to_string(MIN_NAME_LEN) + " and " +
                to_string(MAX_NAME_LEN));

        name = newName;
    }

    void setAccountNumber(const unsigned int newAccountNumber) {
        if (newAccountNumber < MIN_ACCOUNT_NUMBER || newAccountNumber > MAX_ACCOUNT_NUMBER)
            throw invalid_argument(to_string(newAccountNumber) + "is not a valid Account number");

        accountNumber = newAccountNumber;
    }

    string getStatus() {
        return status;
    }

    bool isActive() const {
        return status == ACTIVE;
    }

    bool exists() const {
        return accountNumber != 0;
    }

    bool addBalance(const double amount) {
        if (status == FROZEN) return false;
        balance += amount;
        return true;
    }

    bool subtractBalance(const double amount) {
        if (status == FROZEN || balance < amount) return false;
        balance -= amount;
        return true;
    }

    bool changeAccountStatus() {
        if (accountNumber == 0) return false;

        status = status == ACTIVE ? FROZEN : ACTIVE;
        return true;
    }

    void print() const {
        cout << "Account Number: " << accountNumber<< " Name: " << name
        << " Balance: " << balance << " Status: " << status << endl;
    }
};


constexpr unsigned int accountsCapacity = 10;
BankAccount accounts[accountsCapacity];
unsigned int numAccounts = 0;


void customerMenu();
void employeeMenu();
void roleMenu(unsigned short int &role);
void bankAction(unsigned int role, unsigned int choice);
void getChoice(short unsigned int &choice);

int main() {
    unsigned short int role, choice;
    bool run = true;

    // cin.ignore(1000, '\n');
    cout << "Welcome to the Bank Simulation Program!" << endl;
    roleMenu(role);

    while (run) {
        if (role == CUSTOMER) {
            customerMenu();
        }
        else if (role == EMPLOYEE) {
            employeeMenu();
        }

        getChoice(choice);

        if (choice == EXIT) run = false;
        else if (choice == ROLE_MENU) roleMenu(role);

        bankAction(role, choice);
    }

    return 0;
}


void getVar(unsigned short int &var, const string& name, const int lowerBound, const int upperBound) {
    cin >> var;
    while (var < lowerBound or var > upperBound) {
        cout << "Invalid " << name <<". Enter a "<< name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}
void getVar(unsigned int &var, const string& name, const int lowerBound, const int upperBound) {
    cin >> var;
    while (var < lowerBound or var > upperBound) {
        cout << "Invalid " << name <<". Enter a "<< name << " between " << lowerBound << " and " << upperBound << ":";
        cin >> var;
    }
}

unsigned int getAccount() {
    unsigned int accNumber;
    cout << "Please enter your Account Number:";
    getVar(accNumber, "Account Number", MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);
    cin.ignore();
    const unsigned int i = accNumber - MIN_ACCOUNT_NUMBER;

    if (!accounts[i].exists()) return -1;

    return i;
}

void getChoice(short unsigned int &choice) {
    cout << "Enter your choice:";
    getVar(choice, "choice", MIN_CHOICE, MAX_CHOICE);
    system("cls");
}

string getName() {
    string accountName;
    cout << "Enter your name (between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN <<" allowed):";
    cin.ignore();
    getline(cin, accountName);

    while(accountName.length() < MIN_NAME_LEN || accountName.length() > MAX_NAME_LEN) {
        cout << "Try again, Name length is not between " << MIN_NAME_LEN << " and " << MAX_NAME_LEN << ":";
        getline(cin, accountName);
    }
    return accountName;
}

double getAmount() {
    double amount;
    cout << "Please enter amount:";
    cin >> amount;
    cin.ignore();
    return amount;
}

void roleMenu(unsigned short int &role) {
    cout << "Enter your role ("<< CUSTOMER <<") for Customer, ("<< EMPLOYEE <<") for Employee:";
    getVar(role, "choice", CUSTOMER, EMPLOYEE);
    system("cls");
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
    cout << "OPEN ACCOUNT" << endl << endl;

    const string accountName = getName();
    const unsigned int newAccNum = MIN_ACCOUNT_NUMBER + numAccounts;

    accounts[numAccounts].setName(accountName);
    accounts[numAccounts].setAccountNumber(newAccNum);

    numAccounts++;

    cout << "Account Opened" << endl;
    cout << "Name: " << accountName << endl;
    cout << "Account Number: " << newAccNum << endl;
}

void depositAmount() {

    cout << "DEPOSIT AMOUNT" << endl << endl;
    const unsigned int i = getAccount();

    if (i == -1) {
        cout << "Account does not exist" << endl;
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot deposit funds" << endl;;
        return;
    }

    const double amount = getAmount();

    accounts[i].addBalance(amount);
    cout << "Amount Deposited. Current Balance: " << accounts[i].getBalance() << endl;
}

void withdrawAmount() {
    cout << "WITHDRAW AMOUNT" << endl << endl;
    const unsigned int i = getAccount();

    if (i == -1) {
        cout << "Account does not exist, cannot deposit funds" << endl;
        return;
    }

    if (!accounts[i].isActive()) {
        cout << "Account is Frozen you cannot withdraw Funds" << endl;
        return;
    }

    const double amount = getAmount();

    const bool success = accounts[i].subtractBalance(amount);
    if (!success)
        cout << "Amount could not be withdrawn";
    else
        cout << "Amount Withdrawn. Current Balance: " << accounts[i].getBalance() << endl;
}

void generateAccountStatement() {
    bool found = false;

    cout << "GENERATE ACCOUNT STATEMENT" << endl << endl;
    const string accountName = getName();

    for (int i=0; i<numAccounts; i++) {
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
    for (int i=0; i<numAccounts; i++) {
        accounts[i].print();
    }

}

void deductTax() {
    cout << "DEDUCT TAX" << endl << endl;

    unsigned int count = 0;
    for (int i=0; i<numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].subtractBalance(accounts[i].getBalance() * TAX);
            count++;
        }
    }
    cout << "Tax Deducted from " << count << " account(s)" << endl;
}

void addBonus() {
    cout << "ADD BONUS" << endl << endl;
    unsigned int count = 0;
    for (int i=0; i<numAccounts; i++) {
        if (accounts[i].isActive()) {
            accounts[i].addBalance(accounts[i].getBalance() * BONUS);
            count++;
        }
    }
    cout << "Bonus Added to " << count << " account(s)" << endl;
}

void changeAccountStatus() {
    cout << "CHANGE ACCOUNT STATUS" << endl << endl;
    const unsigned int i = getAccount();
    if (i == -1) {
        cout << "Account does not exist, cannot change status" << endl;
        return;
    }

    if (!accounts[i].changeAccountStatus()) cout << "Account status could not be changed";
    else cout << "Account Status Changed to " << accounts[i].getStatus() << endl;
}

void customerAction(const unsigned int choice) {
    if (choice ==  1) openAccount();
    else {
        if (numAccounts == 0) cout << "You must open an account first..." << endl;
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
    cin.ignore();
    if (numAccounts == 0) {
        cout << "No Accounts were found..." << endl;
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

    if (choice != ROLE_MENU){
        cout << endl;
        cout << "PRESS ENTER TO CONTINUE";
        cin.get();
    }
    system("cls");
}