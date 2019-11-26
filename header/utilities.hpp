#include <bits/stdc++.h> 
using namespace std;

enum OrderStatus {ORDERED, DISPATCHED, DELIVERED, CANCELLED};
enum PaymentStatus {CASH_ON_DELIVERY,WALLET};
enum Type {ADMIN,VENDOR,CUSTOMER};

class ProductManager;
class UserManager;
class OrderManager;
class User;
class Vendor;
class Customer;
class Product;
class Stock;
class CartProduct;
class Cart;
class Wallet;
class Order;


void printSeparator() {
    for(int i = 0; i < 50; i++) cout<<"*";
    cout<<endl;
}

bool compareCharIgnoreCase(char & c1, char & c2)
{
  if (c1 == c2||c1 == std::toupper(c2)||std::toupper(c1)==c2||std::toupper(c1) == std::toupper(c2))
    return true;
  else if (std::toupper(c1) == std::toupper(c2))//Comparing upperCase
    return true;
  return false;
}
 
bool compareStringIgnoreCase(std::string & str1, std::string &str2)
{
  return ( (str1.size() == str2.size() ) &&
       std::equal(str1.begin(), str1.end(), str2.begin(), &compareCharIgnoreCase) );
}



class Password{
public:
    static bool checkStrength(string passwd){
        int length = passwd.length();
        int countUpper = 0,countLower = 0,countDigit = 0;
        for(int i=0;i<length;i++){
            if(passwd[i] >= 65 && passwd[i] <= 90)
                countUpper++;
            if(passwd[i] >= 97 && passwd[i] <= 122)
                countLower++;
            if(passwd[i] >= 48 && passwd[i] <= 57)
                countDigit++;
        }
        if(countUpper && countLower && countDigit && length >= 6 && length <= 10)
            return true;

        return false;
    }
    static unsigned long long hashValue(string passwd){
        hash<string> h;
        return h(passwd);
    }

};

class Address{
private:
    string building,street,city,state;

public:
    void storeAddress(){
        cout<<"Enter all the details in one line each "<<endl;
        cout<<"Enter your Building/Appartment : ";
        getline(cin,building);
        cout<<"Enter your Street :\t\t ";
        getline(cin,street);
        cout<<"Enter your City :\t\t ";
        getline(cin,city);
        cout<<"Enter your State :\t\t ";
        getline(cin,state);
    }

    void displayAddress(){
        cout<<"Building/Apartment : "<<building<<endl;
        cout<<"Street : "<<street<<endl;
        cout<<"City : "<<city<<endl;
        cout<<"State : "<<state<<endl;
    }

    string getDatabaseString() {
      return building + "\n" + street + "\n" + city + "\n" + state + "\n";
    }
};

class Wallet{
  double balance;
public:
  Wallet(){}
  Wallet(double d){
    this->balance = balance;
  }
  double getBalance(){
    return this->balance;
  }
  void updateBalance(double increment){
    this->balance = this->balance + increment;
  }
};

class Order{
  int orderID;
  OrderStatus status;
  vector<CartProduct> cartProducts;
  string expectedDeliveryDate;
  double cost;
  string deliverySlot;
  PaymentStatus paymentStatus;
  public:
  int getOrderID() {
    return orderID;
  }
};

class User{
  string username;
  unsigned long long password;
  Wallet wallet;
  vector<Order*> orders;
  string account;
  Address address;
  enum Type type;
public:
  User(string username, unsigned long password, string account, Address address,Type type){
    this->username = username;
    this->password = password;
    this->account = account;
    this->address = address;
    this->type = type;
    Wallet* newWallet = new Wallet(0);      //why allocation?
    this->wallet = *newWallet;

  }

  string getUsername() {
    return username;
  }
  int getType() {
    return type;
  }

  string getUserString() {
    string db = username + "\n" + to_string(password) + "\n" + to_string(wallet.getBalance()) + "\n" + account + "\n" + address.getDatabaseString() + to_string(type) + "\n" + to_string(orders.size()) + "\n";
    for(auto order: orders) {
      db.append(to_string(order->getOrderID()));
      db.append("\n");
    }
  }
  friend class UserManager;
};

class Vendor : public User{
  double rating;
  int numberOfRatings;
  vector<string> reviews;
public:
  Vendor(string username,unsigned long long password,string accountNumber,Address address):User(username,password,accountNumber,address,VENDOR){
    rating = 0;
    numberOfRatings = 0;
  }
};

class Stock{
    
    public:
    Vendor* vendor;
    int quantity;
    double price;
    Stock(Vendor* vendor, int quantity, double price) {
        this->vendor = vendor;
        this->quantity = quantity;
        this->price = price;
    }
    string getVendorName() {
      return vendor->getUsername();
    }
    string getDatabaseString() {
      return vendor->getUsername() + "\n" + to_string(quantity) + "\n" + to_string(price) + "\n";
    }
};

class Product{
    string name;
    string type;
    vector<Stock*> stocks;
    string description;
    int quantitySold;
    public:
    Product(string name, string type, Stock* stock, string description) {
        this->quantitySold = 0;
        this->name = name;
        this->type = type;
        this->stocks.push_back(stock);
        this->description = description;
    }
    static bool compareProduct(Product* prod1, Product* prod2) {
        return prod1->quantitySold > prod2->quantitySold;
    }
    void displayProduct() {
        cout<<"Name:\t\t"<<name<<endl;
        cout<<"Type:\t\t"<<type<<endl;
        cout<<"Description:\t\t"<<description<<endl;
        cout<<"Quantity Sold:\t\t"<<quantitySold<<endl;
        if(stocks.size() == 0) cout<<"Product is currently out of stock.\n";
        else cout<<"Product in stock. "<<stocks.size()<<" vendors available.\n";
    }
    string getDatabaseString() {
        string db = name + "\n" + type + "\n" + description + "\n" + to_string(quantitySold) + "\n" + to_string(stocks.size()) + "\n";
        for(auto stock: stocks) {
          db.append(stock->getDatabaseString());
        } 
        return db;
    }
    void objectFromDatabase(Product* product, string db) {
      stringstream str(db);
      string attrib[5];
      for (int i = 0; i < 5; i++)
      {
        getline(str, attrib[i]);
      }
      product->name = attrib[0];
      product->type = attrib[1];
      product->description = attrib[2];
      product->quantitySold = stoi(attrib[3]);
      int stockCnt = stoi(attrib[4]);
      for(int i = 0; i < stockCnt; i++) {
        string stockAttrib[3];
        for (int j = 0; j < 3; j++)
        {
          getline(str, stockAttrib[j]);
        }
        Vendor* vendor;
        for(auto curVendor : Database :: users) {     // users must be filled first!
          if(curVendor->getUsername() == stockAttrib[0]) {
            vendor = (Vendor*) curVendor;
          }
        }
        Stock* new_stock = new Stock(vendor, stoi(attrib[1]), stod(attrib[2]));
        product->stocks.push_back(new_stock);
      }
    } 
    string getProductName() {
      return name;
    }
    friend class ProductManager;
};

class CartProduct{
  Product *product;
  Stock *stock;
  int quantity;
  public:
  CartProduct(Product* product, Stock* stock, int quantity) {
      this->product = product;
      this->stock = stock;
      this->quantity = quantity;
  }
  string getDatabaseString() {
    string db;
    db = product->getProductName() + "\n" + stock->getVendorName() + "\n";
    return db;
  }
};



class Cart{
  vector<CartProduct> cartProducts;
  friend class Customer;
};


class Customer : public User{
  Cart cart;
  public:
  Customer(string username,unsigned long long password,string accountNumber,Address address) : User(username,password,accountNumber,address,CUSTOMER){
    
  }

  string getDatabaseString() {
    string db = getUserString() +  to_string(cart.cartProducts.size()) + "\n";
    for(auto product : cart.cartProducts) {
      db.append(product.getDatabaseString());
    }
    return db;
  }
};






















