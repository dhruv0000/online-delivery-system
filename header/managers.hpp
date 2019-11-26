#include<iostream>
#include<vector>
#include<algorithm>
#include "database.hpp"
using namespace std;

class ProductManager {
    public:
    static bool addProduct(string name, string type, int quantity, double price, string description = "none") {
        // if(Database::currentUser->)
        Stock* newStock = new Stock((Vendor*) Database::currentUser, quantity, price);
        bool found = false;
        for(auto product: Database::products) {
            if(compareStringIgnoreCase(name, product->name)) {          
                for (auto stock: product->stocks) {
                    if(Database::currentUser->getUsername() == stock->vendor->getUsername()) {
                        stock->quantity += quantity;
                        stock->price = price;
                        found = true;
                        break;
                    }
                }
                if(found) break;
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
    
    static vector<Product*> getTopProducts(int count = 10) {
        vector<Product*> sortedProducts(Database::products);
        vector<Product*> productsToShow;
        sort(sortedProducts.begin(), sortedProducts.end(), Product::compareProduct);
        for(int i = 0; i < min((int)sortedProducts.size(), count); i++) {
            productsToShow.push_back(sortedProducts[i]);
        }
        return productsToShow;
    }

    static vector<Product*> searchProducts(string query, int limit = 10) {
        vector<Product*> sortedProducts(Database::products);
        vector<Product*> productsToShow;
        sort(sortedProducts.begin(), sortedProducts.end(), Product::compareProduct);
        for (auto product : sortedProducts)
        {
            if(product->name.find(query) != string::npos || product->type.find(query) != string::npos) {
                productsToShow.push_back(product);
            }
        }
        return productsToShow;
    }

    static bool setDiscount(double discount) {
        Database::discount = discount;
        return true;
    }
    

};


class UserManager{


public:
    static bool registerUser(string username, unsigned long long hashPassword, string account, Address address, Type type){
        if(type == VENDOR){
            Vendor* newVendor = new Vendor(username,hashPassword,account,address);
            (Database :: users).push_back((User*)newVendor);
        }
        else{
            Customer* newCustomer = new Customer(username,hashPassword,account,address);
            (Database :: users).push_back((User*)newCustomer);
        }

        return true;
    }
    static bool checkUserNameAvailable(string username){
    
        for(auto presentUserNameCheck : Database::users){
            if(presentUserNameCheck->username == username) return false;
        }
        return true;
    }
    static bool loginUser(string username, unsigned long long hashPassword){
        for(auto existingUser : (Database::users)){
            if(username == existingUser->username){
                if(hashPassword == existingUser->password){
                    Database :: currentUser = existingUser;
                    return true;
                }else{
                    return false;
                }
            }
        }
    return false;
    }

    static bool logoutUser(){
        if(Database :: currentUser == NULL) return false;
        Database :: currentUser = NULL;
        return true;
    }

    static bool showUserProfile(){
        if(Database :: currentUser){
            User* check = Database ::currentUser;
            cout<<"Following are your details :"<<endl;
            cout<<"User Name :\t\t"<<check->username<<endl;
            cout<<"Account Number :\t\t"<<check->account<<endl;
            cout<<"Address :\t\t"<<endl;
            (check->address).displayAddress();
            cout<<"Wallet balance :\t\t"<<(check->wallet).getBalance()<<endl;
            //Still we have to add show cart orders and pending orders
            return true; 
        }
        return false;

    }

    static bool addMoneyFromAccount(double amount){
        printSeparator();
        cout<<"Directing to Bank Gateway"<<endl;
        ((Database::currentUser)->wallet).updateBalance(amount);
        printSeparator();
        return true;
    }

    static int getWalletBalance(){
        return ((Database::currentUser)->wallet).getBalance();
    }

};
