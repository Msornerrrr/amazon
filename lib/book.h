#include "product.h"

class Book : public Product{
public:
    Book(const std::string name, double price, int qty, std::string ISBN, std::string author);

    ~Book();

    /* inherited from virtual functions in Product class */
    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string isbn_;
    std::string author_;
};