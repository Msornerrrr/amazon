#include <iostream>
#include "../lib/movie.h"
#include "../lib/util.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, std::string genre, std::string rating)
    : Product("movie", name, price, qty),
    genre_(genre),
    rating_(rating)
{ }

Movie::~Movie() { }

std::set<std::string> Movie::keywords() const{
    // the set of book's name
    set<string> s = parseStringToWords(name_);

    // add genre to the set
    s.insert(convToLower(genre_));

    // return union of two sets
    return s;
}

std::string Movie::displayString() const{
    return name_ + "\n"
        + "Genre: " + genre_ + " Rating: " + rating_ + "\n"
        + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}