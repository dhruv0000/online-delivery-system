/* this file contains utility functions and defines
 * all functions (including constructors) of the utility classes defined in database.hpp */

#include "database.hpp"
#include<ncurses.h>


int displayBox(string choices[],int n){
    start_color();
    noecho();
    cbreak();
    int xMax,yMax;
    getmaxyx(stdscr,yMax,xMax);
    init_pair(1,COLOR_GREEN,COLOR_WHITE);
    attron(PAIR_NUMBER(1));
    mvprintw(0,xMax/2-10,"Welcome to our online store");
    attroff(PAIR_NUMBER(1));

    mvprintw(yMax-13,5,"Select your Choice\n");
    
    // init_pair(1,COLOR_RED,COLOR_BLACK);
    
    WINDOW* menu = newwin(9,xMax-12,yMax-15,5);
    box(menu,0,0);

    string ad = Product::getAdvertisedProduct(1);
    mvprintw(yMax-4,5,"%s",ad.c_str());
    refresh();
    wrefresh(menu);


     keypad(menu,true);
    // string choices[]={"Manan","Manul","Dhruv"};
    int choice;
    int heighlight=0;
    while(1){
        for (int  i = 0; i < n; i++)
        {//    wattron(menu,COLOR_PAIR(1));
            if(i==heighlight)
                wattron(menu,A_REVERSE);
            
            mvwprintw(menu,i+1,1,choices[i].c_str());
            wattroff(menu,A_REVERSE);
            // wattroff(menu,COLOR_PAIR(1));
        }
        choice = wgetch(menu);

        switch( choice ) {
                case KEY_UP:
                            heighlight--;
                            heighlight = ( heighlight<0 ) ? n-1 : heighlight;
                            break;
                case KEY_DOWN:
                            heighlight++;
                            heighlight = ( heighlight>(n-1) ) ? 0 : heighlight;
                            break;
        }
        if(choice==10)
            break;
    }
    echo();
    wrefresh(menu);
    
    
    heighlight++;
    return heighlight;
}

int displayBoxHeader(string choices[],int n,char* header){
    start_color();
    noecho();
    cbreak();
    int xMax,yMax;
    getmaxyx(stdscr,yMax,xMax);
    init_pair(1,COLOR_GREEN,COLOR_WHITE);
    attron(PAIR_NUMBER(1));
    mvprintw(0,xMax/2-10,"Welcome to our online store");
    attroff(PAIR_NUMBER(1));

    mvprintw(yMax-11,5,"Select your Choice\n");
    
    // init_pair(1,COLOR_RED,COLOR_BLACK);
    
<<<<<<< HEAD
    WINDOW* menu = newwin(9,xMax-12,yMax-15,5);
=======
    WINDOW* menu = newwin(9,xMax-12,yMax-13,5);
>>>>>>> 3c0d570d07895cc22b4e31cc3252000a649cc15f
    box(menu,0,0);
    string ad = Product::getAdvertisedProduct(1);
    mvprintw(yMax-4,5,"%s",ad.c_str());
    refresh();
    wrefresh(menu);

    keypad(menu,true);
    int choice;
    int heighlight=0;
    while(1){
      mvwprintw(menu,1,1,header);
        for (int  i = 0; i < n; i++)
        {//    wattron(menu,COLOR_PAIR(1));
            if(i==heighlight)
                wattron(menu,A_REVERSE);
            
            mvwprintw(menu,i+2,1,choices[i].c_str());
            wattroff(menu,A_REVERSE);
            // wattroff(menu,COLOR_PAIR(1));
        }
        choice = wgetch(menu);

        switch( choice ) {
                case KEY_UP:
                            heighlight--;
                            heighlight = ( heighlight<0 ) ? n-1 : heighlight;
                            break;
                case KEY_DOWN:
                            heighlight++;
                            heighlight = ( heighlight>(n-1) ) ? 0 : heighlight;
                            break;
        }
        if(choice==10)
            break;
    }
    echo();
    wrefresh(menu);
    
    
    heighlight++;
    return heighlight;
}

void displayWindow(char in[],const char* c,char in1[] = NULL){
    
    // clear();
    cbreak();
    mvprintw(2,5,"Enter the following details");
    int xMax,yMax;
    getmaxyx(stdscr,yMax,xMax);

<<<<<<< HEAD
    WINDOW* input = newwin(9,xMax-12,yMax-15,5);
=======
    WINDOW* input = newwin(9,xMax-12,yMax-13,5);
>>>>>>> 3c0d570d07895cc22b4e31cc3252000a649cc15f
    box(input,0,0);
    string ad = Product::getAdvertisedProduct(1);
    mvprintw(yMax-4,5,"%s",ad.c_str());
    refresh();
    wrefresh(input);

    if(in1!=NULL){
    mvwprintw(input,1,1,"%s ",in1);
    }
    mvwprintw(input,2,1,"%s ",in);
    wscanw(input,"%[^\n]s",c);
    refresh();
    
}

// utility to compare chars ignoring case
bool compareCharIgnoreString(char & c1, char & c2)
{
  if (c1 == c2||std::toupper(c1) == std::toupper(c2)||std::toupper(c1) == c2||c1 == std::toupper(c2))
    return true;
  return false;
}
 
//utility to comapare strings ignoring case
bool compareStringIgnoreCase(std::string & str1, std::string &str2)
{
  return ( (str1.size() == str2.size() ) &&
       std::equal(str1.begin(), str1.end(), str2.begin(), &compareCharIgnoreString) );
}

///////////////////////////////////// PASSWORD //////////////////////////////////////////
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

/////////////////////////////////////// ADDRESS ///////////////////////////////////////////

Address::Address() {}

Address::Address(string building, string street, string city, string state) {
  this->building = building;
  this->street = street;
  this->city = city;
  this->state = state;
}

void Address::storeAddress(){
    
    char temp[100];
    
    clear();
    char c1[] = "Enter your Address ";
    char d1[] = "Enter your Building :";
    displayWindow(d1,temp,c1);
    building = string(temp);

    clear();
    char c2[] = "Enter your Address ";
    char d2[] = "Enter your Street :";
    displayWindow(d2,temp,c2);
    street = string(temp);

    clear();
    char c3[] = "Enter your Address ";
    char d3[] = "Enter your City :";
    displayWindow(d3,temp,c3);
    city = string(temp);

    clear();
    char c4[] = "Enter your Address " ;
    char d4[] = "Enter your State :";
    displayWindow(d4,temp,c4);
    state = string(temp);

}

void Address::displayAddress(int i){

    mvprintw(i,5,"Building/Apartment : %s",building.c_str());
    mvprintw(i,5,"Street : %s",street.c_str());
    mvprintw(i,5,"City : %s",city.c_str());
    mvprintw(i,5,"State : %s",state.c_str());
}

void Address::displayAddress(){

    printw("    Building/Apartment : %s\n",building.c_str());
    printw("    Street : %s\n",street.c_str());
    printw("    City : %s\n",city.c_str());
    printw("    State : %s\n",state.c_str());
}

string Address::getDatabaseString() {
  return building + "\n" + street + "\n" + city + "\n" + state + "\n";
}

////////////////////////////////////////////////// WALLET ////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////// ORDER ////////////////////////////////////////////////////////

Order::Order(int id) {
  orderID = id;
}

Order ::Order(int id,CartProduct newCartProduct,double cost,double discount, double deliveryCharge, string deliverySlot,PaymentStatus paymentStatus, Customer* customer){
  this->orderID = id;
  this->status = ORDERED;
  this->cost = cost;
  this->discount = discount;
  this->deliveryCharge = deliveryCharge;
  this->deliverySlot = deliverySlot;
  this->paymentStatus = paymentStatus;
  (this->cartProducts).push_back(newCartProduct);
  this->customer = customer;
}

int Order::getOrderID() {
  return orderID;
}

// void Order :: displayOrderCustomer(){

//   for(int i=0;i<(int)(cartProducts.size());i++){
//     cartProducts[i].displayOrderProduct(5);
//   }

//   cout<<"Cost: "<<cost<<endl;
//   cout<<"Discount: "<<cost*discount<<endl;
//   cout<<"DeliveryCharges: "<<deliveryCharge<<endl;
//   cout<<"Total :"<<cost*(1-discount)+deliveryCharge<<endl;
//   cout<<endl;
//   cout<<"Vendor Name :"<<cartProducts[0].stock->vendor->getUsername();
//   cout<<"Status:";
//   if(status == DISPATCHED)cout<<"DISPATCHED"<<endl;
//   if(status == ORDERED)cout<<"ORDERED"<<endl;
//   if(status == DELIVERED)cout<<"DELIVERED"<<endl;
//   if(status == CANCELLED)cout<<"CANCELLED"<<endl;
//   cout<<"Delivery Slot: "<<deliverySlot<<endl;

// }

void Order :: dispatchOrder(){
  if(status==ORDERED)
    status=DISPATCHED;
    
}

bool Order :: displayOrderVendor(){

  clear();
  int i=0;
  for(;i<(int)(cartProducts.size());i++){
    cartProducts[i].displayOrderProduct(i);
  }

  i++;

  mvprintw(4*i,5,"Cost of Package: %d",cost);
  mvprintw(4*i+1,5,"User Info:");
  mvprintw(4*i+2,5,"Delivery Slot: %d",deliverySlot);
  customer->displayUserInformation(4*i+3);

  string in[] = {"1:Dispatch this order","2:See next order","3:Exit"};
  int choice = displayBox(in,3);
  if(choice == 1){
    dispatchOrder();
    return true;
  }
  else if (choice == 2)
    return true;
  return false;

}











string Order::getDatabaseString() {
  string db = to_string(status) + "\n" + to_string(cost) + "\n" + to_string(discount) + "\n" + to_string(deliveryCharge) + "\n" + deliverySlot + "\n" + to_string(paymentStatus) + "\n" + to_string(customer->getUserID()) + "\n" + to_string(cartProducts.size()) + "\n";
  for(auto cartProduct : cartProducts) {
    db.append(cartProduct.getDatabaseString());
  }
  return db;
}

void Order::objectFromDatabase(Order* order, ifstream& fin) {
  string attrib[8];
  for (int i = 0; i < 8; i++)
  {
    getline(fin, attrib[i]);
  }
  order->status = static_cast<OrderStatus>(stoi(attrib[0]));
  order->cost = stod(attrib[1]);
  order->discount = stod(attrib[2]);
  order->deliveryCharge = stod(attrib[3]);
  order->deliverySlot = attrib[4];
  order->paymentStatus = static_cast<PaymentStatus>(stoi(attrib[5]));
  order->customer = (Customer*) (Database::users[stoi(attrib[6])]);
  int cartSize = stoi(attrib[7]);
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


  
////////////////////////////////////////////////////// USER /////////////////////////////////////////////////////

User::User(int id) {userID = id;}

User::User(string username, unsigned long password, string account, Address address,Type type){
  this->username = username;
  this->password = password;
  this->account = account;
  this->address = address;
  this->type = type;
  this->wallet = Wallet(0);

}

void User :: displayUserInformation(int i){
  mvprintw(i,5,"Name: %s",username.c_str());
  mvprintw(i+1,5,"Address : ");
  address.displayAddress(i+2);

}

void User :: displayUserInformation(){
  printw("    Name: %s\n",username.c_str());
  printw("    Address : \n");
  address.displayAddress();

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

double User::getWalletBalance() {
  return wallet.getBalance();
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

int User::getUserID() {
  return userID;
}

int User::getUserType() {
  return type;
}

string User::getDatabaseString(){}

void User::objectFromDatabase(User* user, ifstream& fin){}

///////////////////////////////////////////////// VENDOR //////////////////////////////////////////////////////////

Vendor::Vendor(int id) : User(id) {type = VENDOR;}

Vendor::Vendor(string username,unsigned long long password,string accountNumber,Address address):User(username,password,accountNumber,address,VENDOR){
  rating = 0;
  numberOfRatings = 0;
}

void Vendor:: displayVendorRatings() {
  
  mvprintw(5,5,"Rating :%lf",rating);
  mvprintw(6,5,"Number of ratings: %d",numberOfRatings);

  for(int i=0;i< min(3,(int)reviews.size());i++){
    printw("Review %d : %s\n",i,reviews[i]);
  }


}

void Vendor:: displayVendorRatings(int a) {
  
  printw("    Rating :%lf\n",rating);
  printw("    Number of ratings: %d\n",numberOfRatings);

  for(int i=0;i< min(3,(int)reviews.size());i++){
    printw("    Review %d : %s\n",i,reviews[i]);
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

/////////////////////////////////////////////// STOCK //////////////////////////////////////////////////////////////

Stock::Stock(int id, Vendor* vendor, int quantity, double price) {
    this->stockID = id;
    this->vendor = vendor;
    this->quantity = quantity;
    this->price = price;
    this->advertised = false;
}
int Stock::getVendorID() {
  return vendor->getUserID();
}
string Stock::getDatabaseString() {
  return to_string(vendor->getUserID()) + "\n" + to_string(quantity) + "\n" + to_string(price) + "\n" + to_string(advertised) + "\n";
}

//////////////////////////////////////////////// PRODUCT /////////////////////////////////////////////////////////////

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

    printw("      Name: %s\n",name.c_str());
    printw("      Type: %s\n",type.c_str());
    printw("      Description: %s\n",description.c_str());
    printw("      Quantity Sold: %d\n",quantitySold);
    if(stocks.size() == 0) printw("     Product is currently out of stock.\n");
    else printw("      Product in stock.%d vendors available.\n",stocks.size());

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
    string stockAttrib[4];
    for (int j = 0; j < 4; j++)
    {
      getline(fin, stockAttrib[j]);
    }
    Vendor* vendor = (Vendor *) Database::users[stoi(stockAttrib[0])];
    Stock* new_stock = new Stock(i, vendor, stoi(stockAttrib[1]), stod(stockAttrib[2]));
    new_stock->advertised = stoi(attrib[3]);
    if(new_stock->advertised) Database::advertisedProducts.push(make_pair(product, new_stock));
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

Stock* Product::getStock(int id) {
  return stocks[id];
}
string Product::getAdvertisedProduct(int count = 1) {
    if(Database::currentUser == NULL) return "";
    if(Database::currentUser->getUserType() == VENDOR) return "";
    if(((Customer*)(Database::currentUser))->getMembershipStatus()) {
        return "You are a prime member! Enjoy " + to_string(Database::primeDiscount*100) + "% EXTRA DISCOUNT on every item!\n";
    }
    string advertisement = "Flat " + to_string(int(Database::discount*100)) + "% off on every item!!\n";
    for(int i = 0; i < min((int)(Database::advertisedProducts.size()), count); i++) {
        Product* product = Database::advertisedProducts.front().first;
        Stock* stock = Database::advertisedProducts.front().second;
        Database::advertisedProducts.pop();
        Database::advertisedProducts.push(make_pair(product, stock));
        advertisement.append("Buy " + product->name + " from " + stock->vendor->getUsername() + " at Rs. " + to_string(stock->price*(1-Database::discount)) + " only!\n     ");
    }
    advertisement.append("Limited offer! Search for these products now!\n");
    return advertisement;
}

///////////////////////////////////// CART PRODUCT //////////////////////////////////////////////////////

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
    printw("     Quantity in Cart :%d",stock->quantity);
}

void CartProduct :: displayOrderProduct(int i){
    
    mvprintw(4*i+5,5,"Product Name: %s",product->getProductName().c_str());
    mvprintw(4*i+6,5,"No. of quantities: %d",quantity);
    mvprintw(4*i+7,5,"Product Price: %d",stock->price);

}


void CartProduct :: displayOrderProduct(){
    
    printw("     Product Name: %s\n",product->getProductName().c_str());
    printw("     No. of quantities: %d\n",quantity);
    printw("     Product Price: %d\n",stock->price);

}

///////////////////////////////////////////// CART //////////////////////////////////////////////////////////

void Cart :: addCartProductToCart(CartProduct newCartProduct){
    cartProducts.push_back(newCartProduct);
}

void Cart :: displayCartFromCart(){
  int i = 1;
  for(auto presentCartProduct : cartProducts){
    printw("     Product %d:",i);
    presentCartProduct.displayCartProduct();
    i++;
  }

}

void Cart :: removeCartProductFromCart(int index){
    cartProducts.erase(cartProducts.begin()+index);
}

////////////////////////////////////////////////// CUSTOMER /////////////////////////////////////////////////////


Customer::Customer(int id) : User(id) {type = CUSTOMER;}

Customer::Customer(string username,unsigned long long password,string accountNumber,Address address) : User(username,password,accountNumber,address,CUSTOMER){
  primeMember = false;
}

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
  string db = getUserString() + to_string(primeMember) + "\n" + to_string(cart.cartProducts.size()) +  "\n";
  for(auto product : cart.cartProducts) {
    db.append(product.getDatabaseString());
  }
  return db;
}

void Customer::objectFromDatabase(Customer* customer, ifstream& fin) {
  userFromDatabase(customer, fin);
  string primeMembership;
  getline(fin, primeMembership);
  customer->primeMember = stoi(primeMembership);
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

bool Customer::getMembershipStatus() {
  return primeMember;
}
