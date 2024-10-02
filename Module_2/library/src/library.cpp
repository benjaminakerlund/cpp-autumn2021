#include <iostream>
#include "book.hpp"
#include "customer.hpp"
#include "library.hpp"


Library::Library(std::string const& name) : name_(name){
}


/* GetName:
* returns the library's name as a string, takes no parameters.
* This function should not alter the Library object's state, in other words the function should be const.
*/
std::string Library::GetName() const{
    return name_;
}

/* GetBooks:
* returns the Library's books as a reference to a vector<Book>, takes no parameters.
*/
std::vector<Book>& Library::GetBooks() {
    return books_;
}


/* GetCustomers:
* returns the Library's customers as a reference to a vector<Customer>, takes no parameters.
*/
std::vector<Customer>& Library::GetCustomers() {
    return customers_;
}


/* FindBookByName:
* returns a Book, takes a const reference to a string as a parameter,
* if a Book is not found, a new book with (an) empty strings as parameters 
* for the name, author and isbn is returned.
*/
Book Library::FindBookByName(std::string const& target) const{
    int n = books_.size();
    Book ret = {"", "", ""};
    for (auto i = 0; i < n; i++){
        if (target == books_[i].GetName()){
            ret = books_[i];
        }
    }
    return ret;
}


/* FindBooksByAuthor:
* returns a vector of Books, takes a const reference to a string as a parameter,
* if no books are found, an empty vector is returned.
*/
std::vector<Book> Library::FindBooksByAuthor(std::string const& target) const{
    int n = books_.size();
    std::vector<Book> authored;
    for (auto i = 0; i < n; i++){
        if (target == books_[i].GetAuthor()){
            authored.push_back(books_[i]);
        }
        else{
            Book newBook = {"", "", ""};
            authored.push_back(newBook);
        }
    }
    return authored;
}



/* FindAllLoanedBooks():
* returns a vector of Books, takes no parameters,
* if no books are found, an empty vector is returned.
*/
std::vector<Book> Library::FindAllLoanedBooks() const{
    int n = books_.size();
    std::vector<Book> loanedBooks;
    for(auto i = 0; i < n; i++){
        if (books_[i].GetStatus() == true) { //add to vector of loaned books
            loanedBooks.push_back(books_[i]);
        }
    }
    return loanedBooks;
}


/* FindCustomer:
* returns a Customer, takes a const reference to a string representing the Customer's id as a parameter,
* if a Customer is not found, a new Customer with empty strings are parameters 
* for name and id is returned.
*/
Customer Library::FindCustomer(std::string const& target) const{
    Customer newCustomer = {"", ""};
    int n = customers_.size();
    for (auto i = 0; i < n; i++) {
        if (target == customers_[i].GetID()) {
            newCustomer = customers_[i];
        }
    }
    return newCustomer;
}


