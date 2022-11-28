#include <iostream>
#include "../lib/book.h"
#include "../lib/util.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, std::string isbn, std::string author)
    : Product("book", name, price, qty),
    isbn_(isbn),
    author_(author)
{ }

Book::~Book(){ }

std::set<std::string> Book::keywords() const{
    // the set of book's name
    set<string> nameSet = parseStringToWords(name_);

    // the set of author's name
    set<string> autherNameSet = parseStringToWords(author_);

    // union those two sets
    set<string> s = setUnion(nameSet, autherNameSet);

    // add ISBN to set
    /* Note
    ISBN is a bunch of numbers with dash, it's not possible to have repeated element in names
    */
    s.insert(isbn_);

    return s;
}

std::string Book::displayString() const{
    return name_ + "\n"
        + "Author: " + author_ + " ISBN: " + isbn_ + "\n" 
        + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}