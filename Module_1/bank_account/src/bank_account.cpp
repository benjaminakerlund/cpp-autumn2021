#include "bank_account.hpp"
#include <iostream>

/*
// define your Person class' functions here
Person::Person(std::string name, int birthyear){
    name_ = name;
    birthyear_ = birthyear;
}


std::string& Person::GetName(){
    return name_;
}

int Person::GetAge(int year) {
    int age = year - birthyear_;
    return age;
}
*/




BankAccount::BankAccount(std::string const& owner, std::string const& account_number, double balance)
                    : owner_(owner), account_number_(account_number), balance_(balance){
                    }


std::string BankAccount::GetOwner() const {
    return owner_;
}

std::string BankAccount::GetNumber() const {
    return account_number_;
}

double BankAccount::GetBalance() const {
    return balance_;
}

void BankAccount::Deposit(double amount) {
    balance_ += amount;
}

bool BankAccount::Withdraw(double amount) {
    if (balance_ >= amount) {
        balance_ -= amount;
        return true;
    }
    else {
        return false;
    }
}

void BankAccount::Print() const {
    std::cout << "Account num: " << account_number_ << ", owned by: " << owner_ << ", balance: " << balance_ << " eur." << std::endl;
}

/* Transfer:
 * Transfers money from the source account to the target account. 
 * If the parameter amount is bigger than the current balance of the source account, 
 * the function returns false and no transfer is made. 
 * If the amount is valid, that is smaller than the source account's current balance, 
 * the function adds the parameter amount to the target account's balance, 
 * reduces the amount from the source account's balance and returns true.
 */
bool Transfer(BankAccount& source_account, BankAccount& target_account, double amount){
    if (source_account.GetBalance() >= amount) {
        source_account.Withdraw(amount);
        target_account.Deposit(amount);
        return true;
    }
    else {
        return false;
    }
    
}
