#include "customer.hpp"

//#include "book.hpp"
#include <iostream>
#include <ctime>

/* Customer:
* the constructor of the Customer class, takes the following parameters:
* - the customer's name (reference to const string), 
* - the customer number (reference to const string).
*/ 
Customer::Customer(std::string const& name, 
    std::string const& number) :
    name_(name),
    number_(number){
    }

/* GetName:
* returns the Customer's name as a string, takes no parameters.
* This function should not alter the Customer object's state, in other words the function should be const.
*/
std::string Customer::GetName() const{
    return name_;
}



/* GetID:
* returns the Customer's customer number as a string, takes no parameters. 
* This function should not alter the Customer object's state, in other words the function should be const.
*/
std::string Customer::GetID() const{
    return number_;
}

/* GetLoanAmount:
* returns the Customer's number of loans as an int, takes no parameters.
* This function should not alter the Customer object's state, in other words the function should be const.
*/
int Customer::GetLoanAmount() const{ //Run through vector of books and count them. Or just size of vector :DD
    return books_.size();
}

/* GetLoans:
* returns the Customer's loans as a vector<Book>, takes no parameters.
* This function should not alter the Customer object's state, in other words the function should be const.
*/
std::vector<Book> Customer::GetLoans() const{ //Return the private vector of books
    return books_;
}

/* LoanBook:
* loans a book for the customer
* takes a reference to a book as a parameter and returns the result of loaning (from Book loan-function).
*/
bool Customer::LoanBook(Book &target) { //This still needs testing in the Customer tests... even tho works in Book tests...
    if (target.GetStatus() == true){
        return false;
    }
    else{
        books_.push_back(target);
        target.Loan();

        return true;
    }
}


/* ReturnBook:
* returns a book from the customer
* takes a reference to a book as a parameter and returns nothing.
*/
void Customer::ReturnBook(Book target) {
    int n = books_.size();
    if (n > 0){ 
        for (auto it = 0; it < n; it++) {
            if (books_[it].GetISBN() == target.GetISBN()) {
                books_.erase(books_.begin() + it);
                target.Restore();
            }
        }
    }
}



/* Print:
* prints the customer's information to the standard output stream.
* The function takes no parameters and returns nothing. 
* The output format should be like the following (for 2 loans):
Customer: <name>, <customer_id>, has <number_of_loans> books on loan:\n
- Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due date: <day>.<month>.<year>\n
- Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due date: <day>.<month>.<year>\n
* This function should not alter the Customer object's state, in other words the function should be const.
*/
void Customer::Print() const{
    int n = books_.size();
    std::cout << "Customer: " << name_ << ", " << number_ << " has " << books_.size() << " books on loan:" << std::endl;
    if (books_.size() > 0) {
        for (auto it = 0; it < n; it++) {
            std::cout << "- Book: " << books_[it].GetName();
            std::cout << ", author: " << books_[it].GetAuthor();
            std::cout << ", ISBN: " << books_[it].GetISBN();
            std::cout << ", loaned " << (books_[it].GetStatus() ? "true" : "false");
            std::cout << ", due date: " << books_[it].GetDueDate().day << "." << books_[it].GetDueDate().month << "." << books_[it].GetDueDate().year << std::endl;
        }
    }
}


