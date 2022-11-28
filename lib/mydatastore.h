#include "datastore.h"
#include <map>
#include <deque>

class MyDataStore : public DataStore{
public:
    ~MyDataStore();

    void addProduct(Product* p);

    void addUser(User* u);

    /* for adding products to user's cart */
    bool addToCart(std::string u, Product* p);

    /* for print product info in user's cart */
    bool printCart(std::string u, std::ostream& os);

    /* for buy products in user's cart */
    bool buyCart(std::string u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

private:
    // store set of Products & Users available
    std::set<Product*> products;
    std::set<User*> users;

    /* map is fast for seraching */

    // single user name -> pair(a User, a deque of products in cart)
    std::map<std::string, std::pair<User*, std::deque<Product*>>> userMap;

    // single keyword -> a set of Products
    std::map<std::string, std::set<Product*>> keywordMap;
};