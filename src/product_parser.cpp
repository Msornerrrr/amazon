#include <iostream>
#include <sstream>
#include "../lib/product_parser.h"
#include "../lib/book.h"
#include "../lib/clothing.h"
#include "../lib/movie.h"
#include "../lib/util.h"
using namespace std;


ProductParser::ProductParser()
{

}


ProductParser::~ProductParser()
{

}


Product* ProductParser::parse(string category,
                              istream& is,
                              bool& error,
                              string& errorMsg,
                              int& lineno)
{

    parseCommonProduct(is, error, errorMsg, lineno);
    if(error) return NULL;
    return parseSpecificProduct(category, is, error, errorMsg, lineno);
}

void ProductParser::parseCommonProduct(std::istream& is,
                                       bool& error,
                                       string& errorMsg,
                                       int& lineno)

{
    string myline;
    getline(is, myline);
    myline = trim(myline);
    if(myline.size() == 0) {
        error = true;
        errorMsg = "Unable to find a product name";
        return;
    }
    prodName_ = myline;

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the price";
        return;
    }
    stringstream ss1(myline);
    ss1 >> price_;
    if( ss1.fail() ) {
        error = true;
        errorMsg = "Unable to read price";
        return;
    }

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the quantity";
        return;
    }
    stringstream ss2(myline);
    ss2 >> qty_;
    if( ss2.fail() ) {
        error = true;
        errorMsg = "Unable to read quantity";
        return;
    }
    lineno++;
}

ProductBookParser::ProductBookParser() : ProductParser()
{
}

Product* ProductBookParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> isbn_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read ISBN";
        return NULL;
    }

    lineno++;
    getline(is, author_);
    if(is.fail()) {
        error = true;
        errorMsg = "Unable to read author";
        return NULL;
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();

}

std::string ProductBookParser::categoryID()
{
    return "book";
}


/**
 * Your job to fill in the code to create a new book product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductBookParser::makeProduct()
{
    // return a pointer to a Book object on the heap
    return new Book(prodName_, price_, qty_, isbn_, author_);
}


ProductClothingParser::ProductClothingParser()
{
}

Product* ProductClothingParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> size_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read size";
        return NULL;
    }

    lineno++;
    getline(is, brand_);
    if(is.fail() || (brand_.size() == 0)) {
        error = true;
        errorMsg = "Unable to read brand";
        return NULL;
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();

}

std::string ProductClothingParser::categoryID()
{
    return "clothing";
}


/**
 * Your job to fill in the code to create a new clothing product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductClothingParser::makeProduct()
{
    // return a pointer to a Clothing object on the heap
    return new Clothing(prodName_, price_, qty_, size_, brand_);
}



ProductMovieParser::ProductMovieParser()
{
}


Product* ProductMovieParser::parseSpecificProduct(std::string category,
        std::istream& is,
        bool& error,
        std::string& errorMsg,
        int& lineno)
{
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> genre_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read genre";
        return NULL;
    }

    lineno++;
    getline(is, myline);
    stringstream ss4(myline);
    ss4 >> rating_;
    if(ss4.fail()) {
        error = true;
        errorMsg = "Unable to read rating";
        return NULL;
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    lineno++;
    if(error) {
        return NULL;
    }
    return makeProduct();

}

std::string ProductMovieParser::categoryID()
{
    return "movie";
}


/**
 * Your job to fill in the code to create a new movie product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductMovieParser::makeProduct()
{
    // return a pointer to a Movie object on the heap
    return new Movie(prodName_, price_, qty_, genre_, rating_);
}