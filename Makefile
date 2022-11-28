CXX=g++
CXXFLAGS=-g -Wall -std=c++11
BUILD = build
VALGRIND := valgrind --tool=memcheck --leak-check=yes
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=$(BUILD)/amazon.o $(BUILD)/user.o $(BUILD)/db_parser.o $(BUILD)/product.o $(BUILD)/product_parser.o $(BUILD)/util.o $(BUILD)/book.o $(BUILD)/clothing.o $(BUILD)/movie.o $(BUILD)/mydatastore.o

all: amazon

valgrind: amazon
	$(VALGRIND) ./amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

$(BUILD)/amazon.o: amazon.cpp lib/db_parser.h lib/mydatastore.h lib/product_parser.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
$(BUILD)/user.o: src/user.cpp lib/user.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/user.cpp
$(BUILD)/db_parser.o: src/db_parser.cpp lib/db_parser.h lib/product.h lib/product_parser.h lib/user.h lib/datastore.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/db_parser.cpp
$(BUILD)/product.o: src/product.cpp lib/product.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/product.cpp
$(BUILD)/product_parser.o: src/product_parser.cpp lib/product_parser.h lib/product.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/product_parser.cpp
$(BUILD)/util.o: src/util.cpp lib/util.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/util.cpp
$(BUILD)/book.o: src/book.cpp lib/book.h lib/product.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/book.cpp	
$(BUILD)/clothing.o: src/clothing.cpp lib/clothing.h lib/product.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/clothing.cpp
$(BUILD)/movie.o: src/movie.cpp lib/movie.h lib/product.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/movie.cpp
$(BUILD)/mydatastore.o: src/mydatastore.cpp lib/mydatastore.h lib/datastore.h build
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c src/mydatastore.cpp

clean:
	rm -rf $(BUILD) amazon

build:
	mkdir -p $(BUILD)

.PHONY:
	clean build