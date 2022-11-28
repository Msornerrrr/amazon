#include "product.h"

class Movie : public Product{
public:
    Movie(const std::string name, double price, int qty, std::string genre, std::string rating);

    ~Movie();

    /* inherited from virtual functions in Product class */
    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};