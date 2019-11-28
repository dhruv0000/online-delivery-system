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

////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////

Wallet::Wallet(){}
Wallet::Wallet(double balance){
  this->balance = balance;
}
double Wallet::getBalance(){
  return this->balance;
}
void Wallet::updateBalance(double increment){
  this->balance = this->balance + increment;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order::Order(int id) {
  orderID = id;
  status = PENDING;
  cost=0;
  paymentStatus=CASH_ON_DELIVERY;
}

int Order::getOrderID() {
  return orderID;
}

string Order::getDatabaseString() {
  string db = to_string(status) + "\n" + expectedDeliveryDate + "\n" + to_string(cost) + "\n" + deliverySlot + "\n" + to_string(paymentStatus) + "\n" + to_string(cartProducts.size()) + "\n";
  for(auto cartProduct : cartProducts) {
    db.append(cartProduct.getDatabaseString());
  }
  return db;
}

void Order::objectFromDatabase(Order* order, ifstream& fin) {
  string attrib[6];
  for (int i = 0; i < 6; i++)
  {
    getline(fin, attrib[i]);
  }
  order->status = static_cast<OrderStatus>(stoi(attrib[0]));
  order->expectedDeliveryDate = attrib[1];
  order->cost = stod(attrib[2]);
  order->deliverySlot = attrib[3];
  order->paymentStatus = static_cast<PaymentStatus>(stoi(attrib[4]));
  int cartSize = stoi(attrib[5]);
  for (int i = 0; i < cartSize; i++)
  {
    string cartAttrib[3];
    for (int j = 0; j < 3; j++)
    {
      getline(fin, cartAttrib[j]);
    }
    CartProduct cartProduct(Database::products[stoi(cartAttrib[0])], Database::products[stoi(cartAttrib[0])]->getStock(stoi(cartAttrib[1])), stoi(cartAttrib[2]));
    order->cartProducts.push_back(cartProduct);
  }
  
  
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
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

User::User(int id) {userID = id;}

User::User(string username, unsigned long password, string account, Address address,Type type){
  this->username = username;
  this->password = password;
  this->account = account;
  this->address = address;
  this->type = type;
  this->wallet = Wallet(0);

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
  // cout<<attrib[0]<<endl;
  user->username = attrib[0];
  user->password = stoull(attrib[1]);
  // cout<<attrib[2]<<endl;
  user->wallet = Wallet(stod(attrib[2]));
  // cout<<user->wallet.getBalance()<<endl;
  user->account = attrib[3];
  user->address = Address(attrib[4], attrib[5], attrib[6], attrib[7]);
  user->type = static_cast<Type>(stoi(attrib[8]));
  // cout<<attrib[8]<<endl;
  int orderSize = stoi(attrib[9]);
  
  for(int i = 0; i < orderSize; i++) {
    string orderId;
    getline(fin, orderId);
    user->orders.push_back(Database::orders[stoi(orderId)]);
  }
}

int User::getUserID() {
  return userID;
}

int User::getUserType() {
  return type;
}

string User::getDatabaseString(){}

void User::objectFromDatabase(User* user, ifstream& fin){}

Vendor::Vendor(int id) : User(id) {type = VENDOR;}

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

void Vendor::objectFromDatabase(Vendor* vendor, ifstream& fin) {
  userFromDatabase(vendor, fin);
  string attrib[3];
  for(int i = 0; i < 3; i++) {
    getline(fin, attrib[i]);
  }
  // cout<<attrib[0]<<endl;
  vendor->rating = stod(attrib[0]);
  vendor->numberOfRatings = stoi(attrib[1]);
  int numberOfReviews = stoi(attrib[2]);
  for(int i = 0; i < numberOfReviews; i++) {
    string review;
    getline(fin, review);
    vendor->reviews.push_back(review);
  }
}

//////////////////////////////////////////////////////////////////////////////////

Stock::Stock(int id, Vendor* vendor, int quantity, double price) {
    this->stockID = id;
    this->vendor = vendor;
    this->quantity = quantity;
    this->price = price;
}
int Stock::getVendorID() {
  return vendor->getUserID();
}
string Stock::getDatabaseString() {
  return to_string(vendor->getUserID()) + "\n" + to_string(quantity) + "\n" + to_string(price) + "\n";
}

Product::Product(int id) {
  productID = id;
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
void Product::objectFromDatabase(Product* product, ifstream& fin) {
  string attrib[5];
  for (int i = 0; i < 5; i++)
  {
    getline(fin, attrib[i]);
  }
  // cout<<attrib[3]<<endl;
  product->name = attrib[0];
  product->type = attrib[1];
  product->description = attrib[2];
  product->quantitySold = stoi(attrib[3]);
  int stockCnt = stoi(attrib[4]);
  // cout<<"yay"<<endl;
  for(int i = 0; i < stockCnt; i++) {
    string stockAttrib[3];
    for (int j = 0; j < 3; j++)
    {
      getline(fin, stockAttrib[j]);
    }
    Vendor* vendor = (Vendor *) Database::users[stoi(stockAttrib[0])];
    Stock* new_stock = new Stock(i, vendor, stoi(stockAttrib[1]), stod(stockAttrib[2]));
    product->stocks.push_back(new_stock);
  }
  // cout<<"yay";
} 
string Product::getProductName() {
  return name;
}

int Product::getProductID() {
  return productID;
}
//////////////////////////////////////////////////////////////////////////////////

Stock* Product::getStock(int id) {
  return stocks[id];
}

CartProduct::CartProduct(Product* product, Stock* stock, int quantity) {
    this->product = product;
    this->stock = stock;
    this->quantity = quantity;
}

string CartProduct::getDatabaseString() {
  string db;
  db = to_string(product->getProductID()) + "\n" + to_string(stock->stockID) + "\n" + to_string(quantity) + "\n";
  return db;
}

void CartProduct :: displayCartProduct(){
    product->displayProduct();
    cout<<"Vendor Name :"<<stock->vendor->getUsername();
    cout<<"Quantity in Cart :"<<stock->quantity;
}

//////////////////////////////////////////////////////////////////////////////////////
void Cart :: addCartProductToCart(CartProduct newCartProduct){
    cartProducts.push_back(newCartProduct);
}

void Cart :: displayCartFromCart(){
  int i = 1;
  for(auto presentCartProduct : cartProducts){
   printSeparator();
   cout<<"Product "<<i<<endl;
   presentCartProduct.displayCartProduct();
    i++;
  }

}

void Cart :: removeCartProductFromCart(int index){
    vector<CartProduct> :: iterator itr = cartProducts.begin(); 
    for(int i=0;i<min((int)cartProducts.size(),index);i++){
      itr++;
    }
    cartProducts.erase(itr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


Customer::Customer(int id) : User(id) {type = CUSTOMER;}

Customer::Customer(string username,unsigned long long password,string accountNumber,Address address) : User(username,password,accountNumber,address,CUSTOMER){}

void Customer :: addCartProduct(CartProduct newCartProduct){
  cart.addCartProductToCart(newCartProduct);
}

void Customer :: removeCartProduct(int index){
  cart.removeCartProductFromCart(index);
}

void Customer :: displayCart(){
  cart.displayCartFromCart();
}

string Customer::getDatabaseString() {
  string db = getUserString() +  to_string(cart.cartProducts.size()) + "\n";
  for(auto product : cart.cartProducts) {
    db.append(product.getDatabaseString());
  }
  return db;
}

void Customer::objectFromDatabase(Customer* customer, ifstream& fin) {
  userFromDatabase(customer, fin);
  string cartSizeStr;
  getline(fin, cartSizeStr);
  int cartSize = stoi(cartSizeStr);
  for (int i = 0; i < cartSize; i++)
  {
    string cartAttrib[3];
    for(int j = 0; j < 3; j++) {
      getline(fin, cartAttrib[j]);
    }
    CartProduct cartProduct(Database::products[stoi(cartAttrib[0])], Database::products[stoi(cartAttrib[0])]->getStock(stoi(cartAttrib[1])), stoi(cartAttrib[2]));
    customer->cart.cartProducts.push_back(cartProduct);
  }
  
}
