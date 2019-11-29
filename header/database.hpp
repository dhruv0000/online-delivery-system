// Contains declarations of all utility classes and database shared by the system

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


// utility functions for manipulating passwords
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

// user wallet which stores user balance
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

// contains details of orders placed, every order corresponds to only one vendor
class Order{
  int orderID;
  OrderStatus status;
  vector<CartProduct> cartProducts;
  double cost;
  double discount;
  double deliveryCharge;
  string deliverySlot;
  PaymentStatus paymentStatus;
  Customer* customer;
  public:
  Order(int id);
  Order(int id,CartProduct newCartProduct,double cost,double discount, double deliveryCharge, string deliverySlot,PaymentStatus paymentStatus, Customer* customer);
  int getOrderID();
  void displayOrderCustomer();
  void displayOrderVender();
  string getDatabaseString();
  static void objectFromDatabase(Order* order, ifstream& fin);
  OrderStatus getOrderStatus();
  friend class OrderManager;
};

// basic user class containing common attributes of users
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
  double getWalletBalance();
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

// subclass of user containing vendor specific attributes like rating, review, etc.
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
  friend class UserManager;
};

// stores the vendor of a particular product alongwith its price and quantity
class Stock{
    
    public:
    int stockID;
    Vendor* vendor;
    int quantity;
    double price;
    bool advertised;
    Stock(int id, Vendor* vendor, int quantity, double price);
    int getVendorID();
    string getDatabaseString();
    friend class OrderManager;
};

// represents a product and stores all its stocks
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
    friend class OrderManager;
};

// represents ready-to-order product which can be added to an order
class CartProduct{
  Product *product;
  Stock *stock;
  int quantity;
  public:
  CartProduct(Product* product, Stock* stock, int quantity);
  void displayCartProduct();
  void displayOrderProduct();
  string getDatabaseString();
  friend class OrderManager;
  friend class Order;
};

// stores cart products
class Cart{
  vector<CartProduct> cartProducts;
  void addCartProductToCart(CartProduct);
  void removeCartProductFromCart(int);
  void displayCartFromCart();
  friend class Customer;
  friend class OrderManager;
};

// subclass of user containing customer specific attributes like cart, membership etc.
class Customer : public User{
  Cart cart;
  bool primeMember;
public:
  Customer(int id);
  Customer(string username,unsigned long long password,string accountNumber,Address address);
  void addCartProduct(CartProduct);
  void displayCart();
  void removeCartProduct(int);
  string getDatabaseString();
  static void objectFromDatabase(Customer* customer, ifstream& fin);
  friend class OrderManager;
  friend class UserManager;
  friend class ProductManager;
};

// main shared database alongwith functions to read and write into database
namespace Database {
    vector<Order*> orders;
    vector<Product*> products;
    vector<User*> users;
    queue< pair<Product*, Stock*> > advertisedProducts;
    User* currentUser;
    User* admin;
    double discount;
    double deliveryCharge;
    double advertisingCost;
    double primeMembershipCost;
    double primeDiscount;

    //utility to get user type
    template<typename T>
    int getType(T* record) {
      return -1;
    }
    template<>
    int getType<User>(User* user) {
      return user->getType();
    }

    // generic function to write entity (product, order or user) to file
    template<typename T>
    void writeEntityToDatabase(vector<T*> data, string fname) {
        ofstream fout;
        fout.open(fname);
        fout<<data.size()<<endl;
        if(typeid(T) == typeid(User)) {             //typeid is used to check class type of entity
          for(auto user : data) {
            fout<<getType<T>(user);
          }
          fout<<endl;
        }
        for(auto item : data) {
            fout<<item->getDatabaseString();        //gets the particular entity's database representation string
        }
        fout.close();
    }

    // utility to create new customer or vendor depending on user type
    template<typename T>
    T* newRecord(int type, int id) {
      return NULL;
    } 
    template<>
    User* newRecord<User>(int type, int id) {
      User* user;
      if(type == CUSTOMER) user = new Customer(id);
      else user = new Vendor(id);
      return user;
    }

    // generic function to initialize data vectors for different entities
    template<typename T>
    void initializeDataVectors(vector<T*>& data, string fname) {
      ifstream fin;
      fin.open(fname);
      if(fin.fail()) return;
      if(fin.peek() == ifstream::traits_type::eof()) {
        fin.close();
        return;
      }
      int size;
      fin>>size;
      string userTypes;
      if(typeid(T) == typeid(User)) {
        
        fin>>userTypes;
      }
      for (int i = 0; i < size; i++)
      {
        T* record;
        if(typeid(T) == typeid(User)) {
          record = newRecord<T>(userTypes[i]-'0', i);
        
        } else {
          record = new T(i);
        }
        data.push_back(record);
      }
      fin.close();
    }

    // utility to read object of customer or vendor from file according to user type
    template<typename T>
    void getObjectFromFile(T* record, ifstream& fin) {

    }
    template<>
    void getObjectFromFile<User>(User* user, ifstream& fin) {
      if(user->getType() == CUSTOMER) {
        
        Customer::objectFromDatabase((Customer*)user, fin);
      } else {
        Vendor::objectFromDatabase((Vendor*)user, fin);
      }
    }

    // generic function to read different entities from file, and update their attributes in data vectors
    template<typename T>
    void readEntityFromDatabase(vector<T*>& data, string fname) {
      ifstream fin;
      fin.open(fname);
      if(fin.fail()) return;
      if(fin.peek() == ifstream::traits_type::eof()) {
        fin.close();
        return;
      }
      string sizeStr;
      getline(fin, sizeStr);
      int size = stoi(sizeStr);
      if(typeid(T) == typeid(User)) {
        string typeString;
        getline(fin, typeString);
      }
      for(auto record : data) {
        if(typeid(T) == typeid(User)) {
          getObjectFromFile<T>(record, fin);
          
        } else {
          T::objectFromDatabase(record, fin);         // sets the entity's attributes according to the file contents
        }
      }
      fin.close();
    }

    // wrapper function to handle writing of all entities to file at program termination
    void writeToDatabase() {
      ofstream fout;
      fout.open("charges.db");
      fout<<Database::discount<<endl;
      fout<<Database::deliveryCharge<<endl;
      fout<<Database::advertisingCost<<endl;
      fout<<Database::primeMembershipCost<<endl;
      fout<<Database::primeDiscount<<endl;
      fout<<Database::admin->getWalletBalance()<<endl;
      fout.close();

      writeEntityToDatabase<Product>(Database::products, "products.db");
      writeEntityToDatabase<User>(Database::users, "users.db");
      writeEntityToDatabase<Order>(Database::orders, "orders.db");

    }

    // wrapper function to handle reading of all entities from file at program beginning
    void readFromDatabase() {
      Database::admin = new User("admin", Password::hashValue("admin"), "AdminAccount", Address("Hostel G6", "IIT Jodhpur", "Jodhpur", "Rajasthan"), ADMIN);
      Database::discount = 0.05;
      Database::deliveryCharge = 20;
      Database::advertisingCost = 50;
      Database::primeMembershipCost = 100;
      Database::primeDiscount = 0.1;
      Database::currentUser = NULL;
      ifstream fin;
      fin.open("charges.db");
      if(!fin.fail()) {
        if(fin.peek() != ifstream::traits_type::eof()) {
          double adminWalletBalance;
          fin>>discount>>deliveryCharge>>advertisingCost>>primeMembershipCost>>primeDiscount>>adminWalletBalance;
          admin->updateWalletBalance(adminWalletBalance);
        }
        fin.close();
      }

      initializeDataVectors<Product>(Database::products, "products.db");
      initializeDataVectors<User>(Database::users, "users.db");
      initializeDataVectors<Order>(Database::orders, "orders.db");
      
      readEntityFromDatabase<Product>(Database::products, "products.db");
      readEntityFromDatabase<User>(Database::users, "users.db");
      readEntityFromDatabase<Order>(Database::orders, "orders.db");
    }
};
