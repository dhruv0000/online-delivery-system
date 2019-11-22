#include<iostream>
#include<vector>
#include<algorithm>
#include "database.hpp"
using namespace std;



class ProductManager {
    public:
    bool addProduct(string name, string type, string description, int quantity, double price) {
        // if(Database::currentUser->)
        Stock* newStock = new Stock((Vendor*) Database::currentUser, quantity, price);
        bool found = false;
        for(auto& product: Database::products) {
            if(compareStringIgnoreCase(name, product->name)) {
                product->stocks.push_back(newStock);
                found = true;
                break;
            }
        }
        if(found) return true;
        Product* newProduct = new Product(name, type, newStock, description);
        Database::products.push_back(newProduct);
        return true;
    }
    
    void showTopProducts(int count = 10) {
        vector<Product*> productsToShow(Database::products);
        sort(productsToShow.begin(), productsToShow.end(), Product::compareProduct);
        printSeparator();
        for(int i = 0; i < min((int)productsToShow.size(), count); i++) {
            productsToShow[i]->displayProduct();
            printSeparator();
        }
    }

    void searchProducts(string query, int limit = 10) {
        vector<Product*> productsToShow(Database::products);
        sort(productsToShow.begin(), productsToShow.end(), Product::compareProduct);
        printSeparator();
        for (auto& product : productsToShow)
        {
            if(product->name.find(query) != string::npos || product->type.find(query) != string::npos) {
                product->displayProduct();
                printSeparator();
            }
        }
    }

    bool setDiscount(double discount) {
        Database::discount = discount;
        return true;
    }


}
