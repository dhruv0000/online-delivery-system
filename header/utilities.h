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

class Password{
public:
    static bool checkStrength(string passwd){
        int length = passwd.length();
        int countUpper = 0,countLower = 0,countDigit = 0;
        for(int i=0;i<len;i++){
            if(passwd[i] >= 65 && passwd[i] <= 90)
                countUpper++;
            if(passwd[i] >= 97 && passwd[i] <= 122)
                countLower++;
            if(passwd[i] >= 48 && passwd[i] <= 57)
                countDigit++;
        }
        if(countUpper && countLower && countDigit)
            return false;

        return true;
    }
    static unsigned long hashValue(string passwd){
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
        getline(str,building);
        cout<<"Enter your Street :\t\t ";
        getline(str,street);
        cout<<"Enter your City :\t\t ";
        getline(str,city);
        cout<<"Enter your State :\t\t ";
        getline(str,state);
    }

    void displayAddress(){
        cout<<"Building/Appartment : "<<bulding<<endl;
        cout<<"Street : "<<street<<endl;
        cout<<"City : "<<city<<endl;
        cout<<"State : "<<state<<endl;
    }
};


class User{
  string username;
  unsigned long password;
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
    Wallet* newWallet = new Wallet(0);
    this->wallet = *newWallet;

  }
  static bool checkUserNameAvailable(string userName){
    
    for(auto presentUserNameCheck : Database::users){
      if(presentUserNameCheck->username == userName)return false;
    }
    return true;
  }


};


class Wallet{
  double balance;
public:
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
