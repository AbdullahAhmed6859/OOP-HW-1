// BankAccount.cpp
#include "BankAccount.h"
#include <stdexcept>
#include <iostream>

string BankAccount::getName() const {
    return name;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setName(const string& newName) {
    if (newName.length() < MIN_NAME_LEN || newName.length() > MAX_NAME_LEN)
        throw invalid_argument("Name length has to be between " + to_string(MIN_NAME_LEN) + " and " + to_string(MAX_NAME_LEN));
    name = newName;
}

void BankAccount::setAccountNumber(const unsigned int newAccountNumber) {
    if (newAccountNumber < MIN_ACCOUNT_NUMBER || newAccountNumber > MAX_ACCOUNT_NUMBER)
        throw invalid_argument(to_string(newAccountNumber) + " is not a valid Account number");
    accountNumber = newAccountNumber;
}

string BankAccount::getStatus() {
    return status;
}

bool BankAccount::isActive() const {
    return status == ACTIVE;
}

bool BankAccount::exists() const {
    return accountNumber != 0;
}

bool BankAccount::addBalance(const double amount) {
    if (status == FROZEN) return false;
    balance += amount;
    return true;
}

bool BankAccount::subtractBalance(const double amount) {
    if (status == FROZEN || balance < amount) return false;
    balance -= amount;
    return true;
}

bool BankAccount::changeAccountStatus() {
    if (accountNumber == 0) return false;
    status = status == ACTIVE ? FROZEN : ACTIVE;
    return true;
}

void BankAccount::print() const {
    cout << "Account Number: " << accountNumber << " Name: " << name
         << " Balance: " << balance << " Status: " << status << endl;
}
