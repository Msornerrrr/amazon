#include "product.h"

class Clothing : public Product{
public:
    Clothing(const std::string name, double price, int qty, std::string size, std::string brand);

    ~Clothing();

    /* inherited from virtual functions in Product class */
    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};