#include<iostream>
#include<string>
using namespace std;

enum OrderStatus {ORDERED, DISPATCHED, DELIVERED, CANCELLED};
enum PaymentStatus {CASH_ON_DELIVERY,WALLET};
enum Type {ADMIN,VENDOR,CUSTOMER};

class ProductManager;
class UserManager;
class OrderManager;

void printSeparator() {
    for(int i = 0; i < 50; i++) cout<<"*";
    cout<<endl;
}

bool compareChar(char & c1, char & c2)
{
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}
 
bool compareStringIgnoreCase(std::string & str1, std::string &str2)
{
	return ( (str1.size() == str2.size() ) &&
			 std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}

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
    static bool compareProduct(const Product*& prod1, const Product*& prod2) {
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
    friend class ProductManager;
};

class Stock{
    Vendor* vendor;
    int quantity;
    double price;
    public:
    Stock(Vendor* vendor, int quantity, double price) {
        this->vendor = vendor;
        this->quantity = quantity;
        this->price = price;
    }
};

class Cart{
  vector<CartProduct> cartProducts;
};

class Order{
  OrderStatus status;
  vector<CartProduct> cartProducts;
  string expectedDeliveryDate;
  double cost;
  string deliverySlot;
  PaymentStatus paymentStatus;
};

class Vendor{
  double rating;
  int numberOfRatings;
  string reviews;
};

class Customer : public User{
  Cart cart;
};

class User{
  string username;
  string password;
  Wallet wallet;
  vector<Order*> orders;
  string account;
  string address;
  Type type;
};

class Wallet{
  double balance;
};
