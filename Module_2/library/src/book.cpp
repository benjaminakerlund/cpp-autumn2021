#include "book.hpp"

#include <ctime>
#include <iostream>




Book::Book(std::string const& name, 
    std::string const& author, 
    std::string const& isbn, 
    bool loaned, 
    Date due_date) :
    name_(name),
    author_(author),
    isbn_(isbn),
    loaned_(loaned),
    due_date_(due_date){
    }


/* GetName:
* returns the Book's name as a string, takes no parameters.
* This function should not alter the Book object's state, in other words the function should be const.
*/
std::string Book::GetName() const {
    return name_;
}

/* GetAuthor:
* returns the Book's author as a string, takes no parameters. 
* This function should not alter the Book object's state, in other words the function should be const.
*/
std::string Book::GetAuthor() const {
    return author_;
}


/* GetISBN:
* returns the Book's ISBN as a string, takes no parameters.
* This function should not alter the Book object's state, in other words the function should be const.
*/
std::string Book::GetISBN() const {
    return isbn_;
}


/* GetStatus:
* returns the Book's status as a bool, takes no parameters.
* This function should not alter the Book object's state, in other words the function should be const.
*/
bool Book::GetStatus() const {
    return loaned_;
}


/* GetDueDate:
* returns the Book's due date, takes no parameters.
* This function should not alter the Book object's state, in other words the function should be const.
*/
Date Book::GetDueDate() const {
    return due_date_;
}


/* Loan:
* sets the due date to current date + 1 month, e.g. loaned on 1.9. => due date 1.10.
* sets the status to true
* returns true if loaning was succesful and false if it was not
* Hint: there is a function Today in the Date struct that returns the current date
*/
bool Book::Loan() {
    Date today = Date::Today();
    Date due_date;
    //Checks wether book is already loaned
    if (loaned_ == true) {
        return false;
    }
    else {
        if(today.month == 12) {
            due_date.day = today.day;
            due_date.month = 1;
            due_date.year = today.year +1;
        }
        else {
            due_date.day = today.day;
            due_date.month = today.month +1;
            due_date.year = today.year;
        }
        due_date_ = due_date;
        loaned_ = true;
        return true;
    }
}


/* Restore:
* sets the due date to 0-0-0
* sets the status to false
* returns nothing
*/
void Book::Restore() {
    due_date_.day = 0;
    due_date_.month = 0;
    due_date_.year = 0;
    loaned_ = false;
}


/* Print:
* prints the book's information to the standard output stream.
* The function takes no parameters and returns nothing. 
* The output format should be like the following:
Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due date: <day>.<month>.<year>\n
* This function should not alter the Book object's state, in other words the function should be const.
*/
void Book::Print() {
    std::cout << "Book: " << name_ << ", ";
    std::cout << "author: " << author_ << ", ";
    std::cout << "ISBN: " << isbn_ << ", ";
    std::cout << "loaned " << (loaned_ ? "true" : "false") << ", ";
    std::cout << "due date: " << due_date_.day << "." << due_date_.month << "." << due_date_.year << std::endl;   
}


