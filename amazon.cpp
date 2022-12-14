#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "lib/product.h"
#include "lib/db_parser.h"
#include "lib/product_parser.h"
#include "lib/util.h"
#include "lib/mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    string filepath;
    if(argc < 2) {
        filepath = "db/default_database.txt";
    } else {
        filepath = "db/" + string(argv[1]);
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;


    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(filepath, ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT (new_db_filename / override)  " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    if(filename == "override") {
                        filename = filepath;
                    } else {
                        filename = "db/" + filename;
                    }
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	        /* Add support for other commands here */
            else if( cmd == "ADD" ){
                string username;
                unsigned int search_hit_number;
                
                // fetch username and product index
                if(ss >> username >> search_hit_number){
                    // no product in hits
                    if(hits.size() == 0){
                        cout << "Invalid request" << endl;
                    }
                    // index out of range
                    else if(search_hit_number < 1 || search_hit_number > hits.size()){
                        cout << "Invalid request" << endl;
                    }
                    else{
                        Product* target = hits[search_hit_number - 1];
                        username = convToLower(username);
                        if(!ds.addToCart(username, target)){
                            // user is not found
                            cout << "Invalid request" << endl;
                        }
                    }
                } else {
                    // fetch failed
                    cout << "Invalid request" << endl;
                }
            }
            else if( cmd == "VIEWCART" ){
                string username;
                if(ss >> username){
                    username = convToLower(username);
                    if(!ds.printCart(username, cout)){
                        // user is not found
                        cout << "Invalid username" << endl;
                    }
                } else{
                    // fail to take input
                    cout << "Invalid username" << endl;
                }
            }
            else if(cmd == "BUYCART"){
                string username;
                if(ss >> username){
                    username = convToLower(username);
                    if(!ds.buyCart(username)){
                        // user is not found
                        cout << "Invalid username" << endl;
                    }
                } else{
                    // fail to take input
                    cout << "Invalid username" << endl;
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
