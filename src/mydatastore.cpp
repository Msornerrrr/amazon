#include "../lib/mydatastore.h"
#include "../lib/util.h"
using namespace std;

/* destructor for my datastore */
MyDataStore::~MyDataStore() {
    set<Product*>::iterator pIt;
    set<User*>::iterator uIt;

    // for each product or user, deallocate data
    for(pIt = products.begin(); pIt != products.end(); ++pIt) {
        delete *pIt;
    }

    for(uIt = users.begin(); uIt != users.end(); ++uIt) {
        delete *uIt;
    }

    /* clear the set
    products.clear();
    users.clear();
    userMap.clear();
    keywordMap.clear();
    */
}

void MyDataStore::addProduct(Product* p){
    /* fill up map<string, set<Product*>> keywordMap; */
    set<string> keywords = p->keywords(); // get all keywords

    // for each keyword
    for(set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
        // iterator that hold result of keyword
        map<string, set<Product*>>::iterator item = keywordMap.find(*it);

        // if keyword is not find
        if(item == keywordMap.end()){
            set<Product*> tempProducts; // new set with Product p inside
            tempProducts.insert(p);
            keywordMap[*it] = tempProducts; // add new set to map
        }
        // if keyword already in the keys
        else{
            item->second.insert(p); // insert Product p to set
        }
    }

    /* fill up set<Product*> products */
    products.insert(p);
}

void MyDataStore::addUser(User* u){
    /* fill up map<string, deque<Product*>> userMap; */
    deque<Product*> cart; // create a empty cart
    string username = convToLower(u->getName());

    // username -> (user, cart)
    userMap[username] = make_pair(u, cart);

    /* fill up map<User*> users */
    users.insert(u);
}

/* methods only for mydatastore */
bool MyDataStore::addToCart(string u, Product* p){
    map<string, pair<User*, deque<Product*>>>::iterator it = userMap.find(u);
    // if provided user is not in the database
    if(it == userMap.end()){
        return false;
    }

    it->second.second.push_back(p); // add product to cart
    return true;
}

bool MyDataStore::printCart(string u, ostream& os){
    map<string, pair<User*, deque<Product*>>>::iterator it = userMap.find(u);
    // if provided user is not in the database
    if(it == userMap.end()){
        return false;
    }

    unsigned int count = 1; // number list
    deque<Product*>& cart = it->second.second; // reference

    // iterate over cart deque
    for(deque<Product*>::iterator p = cart.begin(); p != cart.end(); ++p){
        os << "Item " << count << "\n";
        os << (*p)->displayString() << "\n";
        os << "\n";
        count++;
    }
    return true;
}

bool MyDataStore::buyCart(std::string u){
    map<string, pair<User*, deque<Product*>>>::iterator it = userMap.find(u);
    // if provided user is not in the database
    if(it == userMap.end()){
        return false;
    }

    User*& user = it->second.first; // reference
    deque<Product*>& cart = it->second.second; // reference
    deque<Product*>::iterator p = cart.begin(); // iterator

    // iterate over cart deque
    while(p != cart.end()){
        int qty = (*p)->getQty();
        double price = (*p)->getPrice();
        double balance = user->getBalance();

        // if quantity > 0 and price less than user's balance
        if(qty > 0 && price <= balance){
            user->deductAmount(price); // deduct balance
            (*p)->subtractQty(1); // deduct amount
            p = cart.erase(p); // erase while keep track of iterator
        } 
        // user cannot pay the price
        else{
            ++p; // go to next product
        }
    }

    return true;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    // store set of matched products for all terms
    set<Product*> results;

    // keep track of first iteration
    bool firstIteration = true;

    // for each term
    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        // iterator for keywordMap
        map<string, set<Product*>>::iterator item = keywordMap.find(*it);

        // if term is not in the keys
        if(item == keywordMap.end()){
            continue; // skip to next loop
        }

        // the resulting set of products
        set<Product*> result = item->second;

        // for first iteration, always union the first set of products
        if(firstIteration){
            results = setUnion(results, result);
            firstIteration = false;
        }
        // for other iteration, do the union or intersection
        else{
            // AND search, intersect each result
            if(type == 0){
                results = setIntersection(results, result);
            }

            // OR search, union each result
            else if(type == 1){
                results = setUnion(results, result);
            }
        }
    }

    // convert results from set to vector
    vector<Product*> matchedList;
    for(set<Product*>::iterator it = results.begin(); it != results.end(); ++it){
        matchedList.push_back(*it);
    }
    return matchedList;
}

void MyDataStore::dump(std::ostream& ofile){
    // dump each product in products set
    ofile << "<products>" << endl;
    for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;

    // dump each user in users set
    ofile << "<users>" << endl;
    for(set<User*>::iterator it = users.begin(); it != users.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}