#include "database.hpp"

void printSeparator() {
    for(int i = 0; i < 50; i++) 
      cout<<"*";
    cout<<endl;
}

bool compareCharIgnoreString(char & c1, char & c2)
{
  if (c1 == c2||std::toupper(c1) == std::toupper(c2)||std::toupper(c1) == c2||c1 == std::toupper(c2))
    return true;
  return false;
}
 
bool compareStringIgnoreCase(std::string & str1, std::string &str2)
{
  return ( (str1.size() == str2.size() ) &&
       std::equal(str1.begin(), str1.end(), str2.begin(), &compareCharIgnoreString) );
}

bool Password::checkStrength(string passwd){
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
    if(countUpper && countLower && countDigit && length >= 6 && (length>=8))
        return true;

    return false;
}
unsigned long long Password::hashValue(string passwd){
    hash<string> h;
    return h(passwd);
}



void Address::storeAddress(){
    cout<<"Enter all the details in one line each "<<endl;
    cout<<"Enter your Building/Appartment :\t\t ";
    getline(std::cin,building);
    cout<<"Enter your Street :\t\t ";
    getline(std::cin,street);
    cout<<"Enter your City :\t\t ";
    getline(std::cin,city);
    cout<<"Enter your State :\t\t ";
    getline(std::cin,state);
}

void Address::displayAddress(){
    cout<<"Building/Apartment : "<<building<<endl;
    cout<<"Street : "<<street<<endl;
    cout<<"City : "<<city<<endl;
    cout<<"State : "<<state<<endl;
}

string Address::getDatabaseString() {
  return building + "\n" + street + "\n" + city + "\n" + state + "\n";
}


Wallet::Wallet(){}
Wallet::Wallet(double d){
  this->balance = balance;
}
double Wallet::getBalance(){
  return this->balance;
}
void Wallet::updateBalance(double increment){
  this->balance = this->balance + increment;
}



int Order::getOrderID() {
  return orderID;
}


User::User(string username, unsigned long password, string account, Address address,Type type){
  this->username = username;
  this->password = password;
  this->account = account;
  this->address = address;
  this->type = type;
  Wallet* newWallet = new Wallet(0);      //why allocation?
  this->wallet = *newWallet;

}

class Vendor : public User{
  double rating;
  int numberOfRatings;
  vector<string> reviews;
public:
  Vendor(string username,unsigned long long password,string accountNumber,Address address):User(username,password,accountNumber,address,VENDOR){
    rating = 0;
    numberOfRatings = 0;
string User::getUsername() {
  return username;
}
unsigned long long User::getPassword() {
  return password;
}
int User::getType() {
  return type;
}

string User::getUserString() {
  string db = username + "\n" + to_string(password) + "\n" + to_string(wallet.getBalance()) + "\n" + account + "\n" + address.getDatabaseString() + to_string(type) + "\n" + to_string(orders.size()) + "\n";
  for(auto order: orders) {
    db.append(to_string(order->getOrderID()));
    db.append("\n");
  }
  return db;
}

Vendor::Vendor(string username,unsigned long long password,string accountNumber,Address address):User(username,password,accountNumber,address,VENDOR){
  rating = 0;
  numberOfRatings = 0;
}

string Vendor::getDatabaseString() {
  string db = getUserString() + "\n" + to_string(rating) + "\n" + to_string(numberOfRatings) + "\n" + to_string(reviews.size()) + "\n";
  for(auto review : reviews) {
    db.append(review);
    db.append("\n");
  }
  return db;
}


Stock::Stock(Vendor* vendor, int quantity, double price) {
    this->vendor = vendor;
    this->quantity = quantity;
    this->price = price;
}
string Stock::getVendorName() {
  return vendor->getUsername();
}
string Stock::getDatabaseString() {
  return vendor->getUsername() + "\n" + to_string(quantity) + "\n" + to_string(price) + "\n";
}


Product::Product(string name, string type, Stock* stock, string description) {
    this->quantitySold = 0;
    this->name = name;
    this->type = type;
    this->stocks.push_back(stock);
    this->description = description;
}
bool Product::compareProduct(Product* prod1, Product* prod2) {
    return prod1->quantitySold > prod2->quantitySold;
}
void Product::displayProduct() {
    cout<<"Name:\t\t"<<name<<endl;
    cout<<"Type:\t\t"<<type<<endl;
    cout<<"Description:\t\t"<<description<<endl;
    cout<<"Quantity Sold:\t\t"<<quantitySold<<endl;
    if(stocks.size() == 0) cout<<"Product is currently out of stock.\n";
    else cout<<"Product in stock. "<<stocks.size()<<" vendors available.\n";
}
string Product::getDatabaseString() {
    string db = name + "\n" + type + "\n" + description + "\n" + to_string(quantitySold) + "\n" + to_string(stocks.size()) + "\n";
    for(auto stock: stocks) {
      db.append(stock->getDatabaseString());
    } 
    return db;
}
void Product::objectFromDatabase(Product* product, string db) {
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
string Product::getProductName() {
  return name;
}



CartProduct::CartProduct(Product* product, Stock* stock, int quantity) {
    this->product = product;
    this->stock = stock;
    this->quantity = quantity;
}
string CartProduct::getDatabaseString() {
  string db;
  db = product->getProductName() + "\n" + stock->getVendorName() + "\n";
  return db;
}


Customer::Customer(string username,unsigned long long password,string accountNumber,Address address) : User(username,password,accountNumber,address,CUSTOMER){
  
}

string Customer::getDatabaseString() {
  string db = getUserString() +  to_string(cart.cartProducts.size()) + "\n";
  for(auto product : cart.cartProducts) {
    db.append(product.getDatabaseString());
  }
  return db;
}























