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
    if(countUpper && countLower && countDigit && length >= 6)
        return true;

    return false;
}
unsigned long long Password::hashValue(string passwd){
    hash<string> h;
    return h(passwd);
}

Address::Address() {}

Address::Address(string building, string street, string city, string state) {
  this->building = building;
  this->street = street;
  this->city = city;
  this->state = state;
}

void Address::storeAddress(){
    cout<<"Enter all the details in one line each "<<endl;
    cout<<"Enter your Building/Appartment :";
    getchar();
    getline(std::cin,building);
    cout<<"Enter your Street :";
    getline(std::cin,street);
    cout<<"Enter your City :";
    getline(std::cin,city);
    cout<<"Enter your State :";
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

Order::Order(int id) {
  orderID = id;
  status = PENDING;
  cost=0;
  paymentStatus=CASH_ON_DELIVERY;
}

int Order::getOrderID() {
  return orderID;
}

OrderStatus Order::getOrderStatus() {
  return status;
}

Order ::Order(int id,CartProduct newCartProduct,double cost,string deliverySlot,PaymentStatus paymentStatus){
  this->orderID = id;
  this->status = ORDERED;
  this->cost = cost;
  this->deliverySlot = deliverySlot;
  this->paymentStatus = paymentStatus;
  (this->cartProducts).push_back(newCartProduct);
}
  


User::User() {}

User::User(string username, unsigned long password, string account, Address address,Type type){
  this->username = username;
  this->password = password;
  this->account = account;
  this->address = address;
  this->type = type;
  Wallet* newWallet = new Wallet(0);      // TODO: why allocation?
  this->wallet = *newWallet;

}

string User::getUsername() {
  return username;
}
unsigned long long User::getPassword() {
  return password;
}
int User::getType() {
  return type;
}

void User::updateWalletBalance(double amount){
  wallet.updateBalance(amount);
}
string User::getUserString() {
  string db = username + "\n" + to_string(password) + "\n" + to_string(wallet.getBalance()) + "\n" + account + "\n" + address.getDatabaseString() + to_string(type) + "\n" + to_string(orders.size()) + "\n";
  for(auto order: orders) {
    db.append(to_string(order->getOrderID()));
    db.append("\n");
  }
  return db;
}

void User::userFromDatabase(User* user, ifstream& fin) {
  string attrib[10];
  for(int i = 0; i < 10; i++) {
    getline(fin, attrib[i]);
  }
  user->username = attrib[0];
  user->password = stoull(attrib[1]);
  user->wallet = Wallet(stod(attrib[2]));
  user->account = attrib[3];
  user->address = Address(attrib[4], attrib[5], attrib[6], attrib[7]);
  user->type = static_cast<Type>(stoi(attrib[8]));
  int orderSize = stoi(attrib[9]);
  for(int i = 0; i < orderSize; i++) {
    string orderId;
    getline(fin, orderId);
    user->orders.push_back(Database::orders[stoi(orderId)]);
  }
}

string User::getDatabaseString(){}


Vendor::Vendor() : User() {}
Vendor::Vendor(string username,unsigned long long password,string accountNumber,Address address):User(username,password,accountNumber,address,VENDOR){
  rating = 0;
  numberOfRatings = 0;
}

void Vendor:: displayVendorRatings() {
  cout<<"Rating :"<<rating<<endl;
  cout<<"Number of ratings :"<<numberOfRatings<<endl;
  for(int i=0;i< min(3,(int)reviews.size());i++){
    cout<<"Review " <<i<< ":" <<reviews[i] <<endl;
  }

}

string Vendor::getDatabaseString() {
  string db = getUserString() + to_string(rating) + "\n" + to_string(numberOfRatings) + "\n" + to_string(reviews.size()) + "\n";
  for(auto review : reviews) {
    db.append(review);
    db.append("\n");
  }
  return db;
}

Vendor* Vendor::objectFromDatabase(ifstream& fin) {
  Vendor* vendor = new Vendor();
  userFromDatabase(vendor, fin);
  string attrib[3];
  for(int i = 0; i < 3; i++) {
    getline(fin, attrib[i]);
  }
  vendor->rating = stod(attrib[0]);
  vendor->numberOfRatings = stoi(attrib[1]);
  int numberOfReviews = stoi(attrib[2]);
  for(int i = 0; i < numberOfReviews; i++) {
    string review;
    getline(fin, review);
    vendor->reviews.push_back(review);
  }
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

Product::Product() {}

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
    cout<<"Name:"<<name<<endl;
    cout<<"Type:"<<type<<endl;
    cout<<"Description:"<<description<<endl;
    cout<<"Quantity Sold:"<<quantitySold<<endl;
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
Product* Product::objectFromDatabase(ifstream& fin) {
  Product* product = new Product();
  string attrib[5];
  for (int i = 0; i < 5; i++)
  {
    getline(fin, attrib[i]);
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
      getline(fin, stockAttrib[j]);
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

void Cart :: addCartProductToCart(CartProduct newCartProduct){
    cartProducts.push_back(newCartProduct);
}

void Cart :: removeCartProductToCart(int index){
    cartProducts.erase(index);
}

Customer::Customer() : User() {}

Customer::Customer(string username,unsigned long long password,string accountNumber,Address address) : User(username,password,accountNumber,address,CUSTOMER){}

void Customer :: addCartProduct(CartProduct newCartProduct){
  cart.addCartProductToCart(newCartProduct);
}

void Customer :: removerCartProduct(int index){
  cart.addCartProductToCart(index);
}

string Customer::getDatabaseString() {
  string db = getUserString() +  to_string(cart.cartProducts.size()) + "\n";
  for(auto product : cart.cartProducts) {
    db.append(product.getDatabaseString());
  }
  return db;
}

Customer* Customer::objectFromDatabase(ifstream& fin) {
  Customer* customer = new Customer();
  userFromDatabase(customer, fin);
  return customer;
}






















