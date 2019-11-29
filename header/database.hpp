#include<bits/stdc++.h>

using namespace std;

enum OrderStatus {PENDING, ORDERED, DISPATCHED, DELIVERED, CANCELLED};
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
  friend class UserManager;
  friend class OrderManager;
};

class Order{
  int orderID;
  OrderStatus status;
  vector<CartProduct> cartProducts;
  string expectedDeliveryDate; //Can change to tm if time permites in future
  double cost;
  string deliverySlot;
  PaymentStatus paymentStatus;
  Customer* customer;
  public:
  Order(int id);
  Order(int id,CartProduct newCartProduct,double cost,string delivrySlot,PaymentStatus paymentStatus, Customer* customer);
  int getOrderID();
  void displayOrderCustomer();
  void displayOrderVender();
  string getDatabaseString();
  static void objectFromDatabase(Order* order, ifstream& fin);
  OrderStatus getOrderStatus();
  friend class OrderManager;
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
  User(int id);
  User(string username, unsigned long password, string account, Address address,Type type);
  void displayUserInformation();
  unsigned long long getPassword();
  string getUsername();
  int getType();
  void updateWalletBalance(double);
  string getUserString();
  static void userFromDatabase(User* user, ifstream& fin);
  int getUserID();
  int getUserType();
  virtual string getDatabaseString();
  static void objectFromDatabase(User* user, ifstream& fin);
  friend class UserManager;
  friend class ProductManager;
  friend class OrderManager;
  friend int main();
};

class Vendor : public User{
  double rating;
  int numberOfRatings;
  vector<string> reviews;
public:
  Vendor(int id);
  Vendor(string username,unsigned long long password,string accountNumber,Address address);
  double getRatings();
  void displayVendorRatings();
  string getDatabaseString();
  static void objectFromDatabase(Vendor* vendor, ifstream& fin);
  friend class OrderManager;
};

class Stock{
    
    public:
    int stockID;
    Vendor* vendor;
    int quantity;
    double price;
    Stock(int id, Vendor* vendor, int quantity, double price);
    int getVendorID();
    string getDatabaseString();
    friend class OrderManager;
};

class Product{
    int productID;
    string name;
    string type;
    vector<Stock*> stocks;
    string description;
    int quantitySold;
  public:
    Product(int id);
    Product(string name, string type, Stock* stock, string description);
    static bool compareProduct(Product* prod1, Product* prod2);
    void displayProduct();
    string getDatabaseString();
    static void objectFromDatabase(Product* product, ifstream& fin); 
    string getProductName();
    int getProductID();
    Stock* getStock(int id);
    friend class ProductManager;
};

class CartProduct{
  Product *product;
  Stock *stock;
  int quantity;
  public:
  CartProduct(Product* product, Stock* stock, int quantity);
  void displayCartProduct();
  string getDatabaseString();
  friend class OrderManager;
  friend class Order;
};



class Cart{
  vector<CartProduct> cartProducts;
  void addCartProductToCart(CartProduct);
  void removeCartProductFromCart(int);
  void displayCartFromCart();
  friend class Customer;
  friend class OrderManager;
};


class Customer : public User{
  Cart cart;
public:
  Customer(int id);
  Customer(string username,unsigned long long password,string accountNumber,Address address);
  void addCartProduct(CartProduct);
  void displayCart();
  void removeCartProduct(int);
  string getDatabaseString();
  static void objectFromDatabase(Customer* customer, ifstream& fin);
  friend class OrderManager;
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
    int getType(T* record) {
      return -1;
    }
    template<>
    int getType<User>(User* user) {
      return user->getType();
    }

    template<typename T>
    void writeEntityToDatabase(vector<T*> data, string fname) {
        ofstream fout;
        fout.open(fname);
        fout<<data.size()<<endl;
        if(typeid(T) == typeid(User)) {
          for(auto user : data) {
            fout<<getType<T>(user);
          }
          fout<<endl;
        }
        for(auto item : data) {
            fout<<item->getDatabaseString();
        }
        fout.close();
    }
    template<typename T>
    T* newRecord(int type, int id) {
      return NULL;
    } 
    template<>
    User* newRecord<User>(int type, int id) {
      // cout<<"GGG"<<endl;
      User* user;
      if(type == CUSTOMER) user = new Customer(id);
      else user = new Vendor(id);
      return user;
    }

    template<typename T>
    void initializeDataVectors(vector<T*>& data, string fname) {
      ifstream fin;
      fin.open(fname);
      if(fin.peek() == ifstream::traits_type::eof()) {
        fin.close();
        return;
      }
      int size;
      fin>>size;
      string userTypes;
      if(typeid(T) == typeid(User)) {
        
        fin>>userTypes;
        // cout<<userTypes<<endl;
      }
      // cout<<size<<endl;
      for (int i = 0; i < size; i++)
      {
        T* record;
        if(typeid(T) == typeid(User)) {
          // cout<<userTypes[i]-'0'<<endl;
          record = newRecord<T>(userTypes[i]-'0', i);
        
        } else {
          record = new T(i);
        }
        data.push_back(record);
      }
      fin.close();
    }
    template<typename T>
    void getObjectFromFile(T* record, ifstream& fin) {

    }
    template<>
    void getObjectFromFile<User>(User* user, ifstream& fin) {
      if(user->getType() == CUSTOMER) {
        
        Customer::objectFromDatabase((Customer*)user, fin);
      } else {
        // cout<<"done"<<endl;
        Vendor::objectFromDatabase((Vendor*)user, fin);
      }
      // cout<<"done"<<endl;
    }
    template<typename T>
    void readEntityFromDatabase(vector<T*>& data, string fname) {
      // cout<<data.size()<<endl;
      ifstream fin;
      fin.open(fname);
      if(fin.peek() == ifstream::traits_type::eof()) {
        fin.close();
        return;
      }
      string sizeStr;
      getline(fin, sizeStr);
      // cout<<sizeStr.length()<<endl;
      int size = stoi(sizeStr);
      // cout<<size<<endl;
      // fin>>size;
      if(typeid(T) == typeid(User)) {
        string typeString;
        getline(fin, typeString);
        // cout<<typeString<<endl;
      }
      // int i = 0;
      for(auto record : data) {
        if(typeid(T) == typeid(User)) {
          // cout<<"done"<<endl;
          getObjectFromFile<T>(record, fin);
          
        } else {
        // cout<<<<endl;
          T::objectFromDatabase(record, fin);
          // cout<<"Fff"<<endl;
        }
      }
      fin.close();
    }
    void writeToDatabase() {
      writeEntityToDatabase<Product>(Database::products, "products.txt");
      writeEntityToDatabase<User>(Database::users, "users.txt");
      writeEntityToDatabase<Order>(Database::orders, "orders.txt");

    }
    void readFromDatabase() {
      Database::admin = new User("admin", Password::hashValue("admin"), "AdminAccount", Address("Hostel G6", "IIT Jodhpur", "Jodhpur", "Rajasthan"), ADMIN);
      
      initializeDataVectors<Product>(Database::products, "products.txt");
      initializeDataVectors<User>(Database::users, "users.txt");
      initializeDataVectors<Order>(Database::orders, "orders.txt");
      
      readEntityFromDatabase<Product>(Database::products, "products.txt");
      readEntityFromDatabase<User>(Database::users, "users.txt");
      readEntityFromDatabase<Order>(Database::orders, "orders.txt");
    }
};
