#include<bits/stdc++.h>

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

class Password{
public:
    static bool checkStrength(string passwd);
    static unsigned long long hashValue(string passwd);
};

class Address{
private:
    string building,street,city,state;

public:
    Address();
    Address(string building, string street, string city, string state);
    void storeAddress();
    void displayAddress();
    string getDatabaseString();
};

class Wallet{
  double balance;
public:
  Wallet();
  Wallet(double d);
  double getBalance();
  void updateBalance(double increment);
};

class Order{
  int orderID;
  OrderStatus status;
  vector<CartProduct> cartProducts;
  string expectedDeliveryDate; //Can change to tm if time permites in future
  double cost;
  string deliverySlot;
  PaymentStatus paymentStatus;
  public:
  Order();
  int getOrderID();
};

class User{
protected:
  string username;
  unsigned long long password;
  Wallet wallet;
  vector<Order*> orders;
  string account;
  Address address;
  enum Type type;
public:
  User();
  User(string username, unsigned long password, string account, Address address,Type type);

  unsigned long long getPassword();
  string getUsername();
  int getType();
  string getUserString();
  void userFromDatabase(User* user, ifstream& fin);
  virtual string getDatabaseString();
  friend class UserManager;
};

class Vendor : public User{
  double rating;
  int numberOfRatings;
  vector<string> reviews;
public:
  Vendor();
  Vendor(string username,unsigned long long password,string accountNumber,Address address);
  double getRatings();
  void displayVendorRatings();
  string getDatabaseString();
  Vendor* objectFromDatabase(ifstream& fin);
};

class Stock{
    
    public:
    Vendor* vendor;
    int quantity;
    double price;
    Stock(Vendor* vendor, int quantity, double price);
    string getVendorName();
    string getDatabaseString();
};

class Product{
    string name;
    string type;
    vector<Stock*> stocks;
    string description;
    int quantitySold;
  public:
    Product();
    Product(string name, string type, Stock* stock, string description);
    static bool compareProduct(Product* prod1, Product* prod2);
    void displayProduct();
    string getDatabaseString();
    Product* objectFromDatabase(ifstream& fin); 
    string getProductName();
    friend class ProductManager;
};

class DCartProduct{
  Product *product;
  Stock *stock;
  int quantity;
  public:
  CartProduct(Product* product, Stock* stock, int quantity);
  string getDatabaseString();
  
};



class Cart{
  vector<CartProduct> cartProducts;
  friend class Customer;
};


class Customer : public User{
  Cart cart;
public:
  Customer();
  Customer(string username,unsigned long long password,string accountNumber,Address address);

  string getDatabaseString();
  Customer* objectFromDatabase(ifstream& fin);
};

namespace Database {
    vector<Order*> orders;
    vector<Product*> products;
    vector<User*> users;
    User* currentUser;
    User* admin;
    double discount;
    double deliveryCharge;

    template<typename T>
    void writeToDatabase(vector<T*> data, string fname) {
        ofstream fout;
        fout.open(fname);
        fout<<data.size()<<endl;
        for(auto item : data) {
            fout<<item->getDatabaseString();
        }
        fout.close();
    }
};
