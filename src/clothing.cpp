#include <iostream>
#include "../lib/clothing.h"
#include "../lib/util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, std::string size, std::string brand)
    : Product("clothing", name, price, qty), 
    size_(size),
    brand_(brand)
{ }

Clothing::~Clothing() { }

std::set<std::string> Clothing::keywords() const{
    // the set of book's name
    set<string> nameSet = parseStringToWords(name_);

    // the set of brand names 
    set<string> brandSet = parseStringToWords(brand_);

    // return union of two sets
    return setUnion(nameSet, brandSet);
}

std::string Clothing::displayString() const{
    return name_ + "\n"
        + "Size: " + size_ + " Brand: " + brand_ + "\n"
        + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
