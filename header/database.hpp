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
  int getOrderID();
  string getDatabaseString();
};

class User{
protected:
  int userID;
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
  static void userFromDatabase(User* user, ifstream& fin);
  int getUserID();
  int getUserType();
  virtual string getDatabaseString();
  virtual void objectFromDatabase(User* user, ifstream& fin);
  friend class UserManager;
};

class Vendor : public User{
  double rating;
  int numberOfRatings;
  vector<string> reviews;
public:
  Vendor();
  Vendor(string username,unsigned long long password,string accountNumber,Address address);
  string getDatabaseString();
  static void objectFromDatabase(Vendor* vendor, ifstream& fin);
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
    int productID;
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
    static void objectFromDatabase(Product* product, ifstream& fin); 
    string getProductName();
    int getProductID();
    friend class ProductManager;
};

class CartProduct{
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
  static void objectFromDatabase(Customer* customer, ifstream& fin);
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
    void writeEntityToDatabase(vector<T*> data, string fname) {
        ofstream fout;
        fout.open(fname);
        fout<<data.size()<<endl;
        if(typeid(T) == typeid(User)) {
          for(auto user : data) {
            fout<<user->getUserType();
          }
          fout<<endl;
        }
        for(auto item : data) {
            fout<<item->getDatabaseString();
        }
        fout.close();
    }
    template<typename T>
    void initializeDataVectors(vector<T*> data, string fname) {
      ifstream fin;
      fin.open(fname);
      int size;
      fin>>size;
      for (int i = 0; i < size; i++)
      {
        T* record;
        if(typeid(T) == typeid(User)) {
          string userTypes;
          fin>>userTypes;
          for(auto type : userTypes) {
            if(type-'0' == CUSTOMER) {
              record = new Customer();
            } else {
              record = new Vendor();
            }
          }
        } else {
          record = new T();
        }
        data.push_back(record);
      }
      fin.close();
    }
    template<typename T>
    void readEntityFromDatabase(vector<T*> data, string fname) {
      
      ifstream fin;
      fin.open(fname);
      int size;
      fin>>size;
      if(typeid(T) == typeid(User)) {
        string typeString;
        fin>>typeString;
      }
      for(auto record : data) {
        T::objectFromDatabase(record, fin);
      }
      fin.close();
    }
    void writeToDatabase() {
      writeEntityToDatabase<User>(Database::users, "users.txt");
      writeEntityToDatabase<Product>(Database::products, "products.txt");
      writeEntityToDatabase<Order>(Database::orders, "orders.txt");

    }
    void readFromDatabase() {
      initializeDataVectors<User>(Database::users, "users.txt");
      initializeDataVectors<Product>(Database::products, "products.txt");
      initializeDataVectors<Order>(Database::orders, "orders.txt");
      
      readEntityFromDatabase<User>(Database::users, "users.txt");
      readEntityFromDatabase<Product>(Database::products, "products.txt");
      readEntityFromDatabase<Order>(Database::orders, "orders.txt");
    }
};
