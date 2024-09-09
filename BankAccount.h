// BankAccount.h
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

using namespace std;

const string ACTIVE = "ACTIVE";
const string FROZEN = "FROZEN";
constexpr int MIN_NAME_LEN = 3;
constexpr int MAX_NAME_LEN = 50;
constexpr unsigned int MIN_ACCOUNT_NUMBER = 10000000;
constexpr unsigned int MAX_ACCOUNT_NUMBER = 99999999;

struct BankAccount {
private:
    string name;
    unsigned int accountNumber = 0;
    string status = ACTIVE;
    double balance = 0;

public:
    string getName() const;
    double getBalance() const;
    void setName(const string& newName);
    void setAccountNumber(unsigned int newAccountNumber);
    string getStatus();
    bool isActive() const;
    bool exists() const;
    bool addBalance(double amount);
    bool subtractBalance(double amount);
    bool changeAccountStatus();
    void print() const;
};

#endif
