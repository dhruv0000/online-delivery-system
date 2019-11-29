/* this file contains all the managers - user, product and order manager
 * which contains all the main functions to order products, make payments,
 * register and login users, cancel orders, search products, etc. */

#include "utilities.hpp"

// main class to manage handling of products
class ProductManager {
    public:

    // if vendor has selected advertising, this function is called
    static void advertiseProduct(Product* product, Stock* stock) {
        if(stock->vendor->getWalletBalance() < Database::advertisingCost) return;
        stock->vendor->updateWalletBalance(-(Database::advertisingCost));
        Database::admin->updateWalletBalance(Database::advertisingCost);
        stock->advertised = true;
        Database::advertisedProducts.push(make_pair(product, stock));
    }

    // returns the advertisement string to display in advertisements section in CLI
    static string getAdvertisedProduct(int count = 1) {
        if(Database::currentUser->type == VENDOR) return "";
        if(((Customer*)(Database::currentUser))->primeMember) {
            return "You are a prime member! Enjoy " + to_string(Database::primeDiscount*100) + "% EXTRA DISCOUNT on every item!\n";
        }
        string advertisement = "Flat " + to_string(int(Database::discount*100)) + "% off on every item!!\n";
        for(int i = 0; i < min((int)(Database::advertisedProducts.size()), count); i++) {
            Product* product = Database::advertisedProducts.front().first;
            Stock* stock = Database::advertisedProducts.front().second;
            Database::advertisedProducts.pop();
            Database::advertisedProducts.push(make_pair(product, stock));
            advertisement.append("Buy " + product->name + " from " + stock->vendor->getUsername() + " at Rs. " + to_string(stock->price*(1-Database::discount)) + " only!\n");
        }
        advertisement.append("Limited offer! Search for these products now!\n");
        return advertisement;
    }

    // function to add new product in database
    static bool addProduct(string name, string type, int quantity, double price, string description = "none", bool advertise = false) {
        Stock* newStock = new Stock(0, (Vendor*) (Database::currentUser), quantity, price);
        bool found = false;
        for(auto product: Database::products) {
            if(compareStringIgnoreCase(name, product->name)) {          
                for (auto stock: product->stocks) {
                    if(Database::currentUser->getUsername() == stock->vendor->getUsername()) {
                        stock->quantity += quantity;
                        stock->price = price;
                        if(advertise) advertiseProduct(product, stock);
                        found = true;
                        break;
                    }
                }
                if(found) break;
                newStock->stockID = product->stocks.size();
                product->stocks.push_back(newStock);
                if(advertise) advertiseProduct(product, newStock);
                found = true;
                break;
            }
        }
        if(found) return true;
        Product* newProduct = new Product(name, type, newStock, description);
        newProduct->productID = Database::products.size();
        Database::products.push_back(newProduct);
        if(advertise) advertiseProduct(newProduct, newStock);
        return true;
    }
    
    // function to return vector of top products according to quantity sold
    static vector<Product*> getTopProducts(int count = 5) {
        vector<Product*> sortedProducts(Database::products);
        vector<Product*> productsToShow;
        sort(sortedProducts.begin(), sortedProducts.end(), Product::compareProduct);
        for(int i = 0; i < min((int)(sortedProducts.size()), count); i++) {
            productsToShow.push_back(sortedProducts[i]);
        }
        return productsToShow;
    }

    // function to return vector of products containing a given search term
    static vector<Product*> searchProducts(string query, int limit = 5) {
        vector<Product*> sortedProducts(Database::products);
        vector<Product*> productsToShow;
        sort(sortedProducts.begin(), sortedProducts.end(), Product::compareProduct);
        for (auto product : sortedProducts)
        {
            string lname, lquery, ltype;
            std::transform(product->name.begin(), product->name.end(), lname.begin(),[](unsigned char c){ return std::tolower(c); });
            std::transform(query.begin(), query.end(), lquery.begin(),[](unsigned char c){ return std::tolower(c); });
            std::transform(product->type.begin(), product->type.end(), ltype.begin(),[](unsigned char c){ return std::tolower(c); });
            
            if(lname.find(lquery) != string::npos || ltype.find(lquery) != string::npos) {
                if(productsToShow.size() < limit)
                    productsToShow.push_back(product);
                else
                    break;
            }
        }
        return productsToShow;
    }

    // admin can set discount using this function
    static bool setDiscount(double discount) {
        Database::discount = discount;
        return true;
    }

    // to display all the vendors selling a given product
    static void searchAndDisplayVendor(Product* product){
        // printFlow();
        cout<<"Vendor Details Selling this product :"<<endl;
        for(int i=0;i<(product->stocks).size();i++){
            cout<<i+1<<":"<<endl;
            product->stocks[i]->vendor->displayUserInformation();
            cout<<"Quantity available :"<<product->stocks[i]->quantity<<endl;
            cout<<"Price offered by this vendor :"<<product->stocks[i]->price<<endl;
            product->stocks[i]->vendor->displayVendorRatings();
            
            
        }
        
    }

    // get the stock pointer to a particular stock of a product according to stock index
    static Stock* getStockPointer(Product *product,int vendorSelection){
        
        return product->stocks[min((int)(product->stocks.size()),vendorSelection)];
    }
    
    
    
};


// main class containing all functions for handling users
class UserManager{
public:

    // if customer wants prime membership
    static void makeCustomerPrimeMember(Customer* customer) {
        if(customer->getWalletBalance() < Database::primeMembershipCost) return;
        customer->updateWalletBalance(-(Database::primeMembershipCost));
        Database::admin->updateWalletBalance(Database::primeMembershipCost);
        customer->primeMember = true;
    }

    // to register a new user (customer or vendor)
    static bool registerUser(string username, unsigned long long hashPassword, string account, Address address, Type type, bool primeMembership = false){
        if(type == VENDOR){
            User* newVendor = new Vendor(username,hashPassword,account,address);
            newVendor->userID = Database::users.size();
            (Database :: users).push_back(newVendor);
        }
        else if(type == CUSTOMER){
            User* newCustomer = new Customer(username,hashPassword,account,address);
            newCustomer->userID = Database::users.size();
            (Database :: users).push_back(newCustomer);
            if(primeMembership) makeCustomerPrimeMember((Customer*)newCustomer);
        }

        return true;
    }

    // utility to check availability of username
    static bool checkUserNameAvailable(string username){
    
        for(auto presentUserNameCheck : Database::users){
            if(presentUserNameCheck->username == username) return false;
        }
        return true;
    }
    
    // to login a user
    static bool loginUser(string username, unsigned long long hashPassword){
        for(auto existingUser : (Database::users)){
            if(username == existingUser->username){
                if(hashPassword == existingUser->password){
                    Database :: currentUser = existingUser;
                    return true;
                }else{
                    return false;
                }
            }
        }
    return false;
    }

    // to logout the current (logged in) user
    static bool logoutUser(){
        if(Database :: currentUser == NULL) return false;
        Database :: currentUser = NULL;
        return true;
    }

    // utility to display user profile
    static bool showUserProfile(){
        if(Database :: currentUser){
            User* check = Database ::currentUser;
            cout<<"Following are your details :"<<endl;
            cout<<"User Name :\t\t"<<check->username<<endl;
            cout<<"Account Number :\t\t"<<check->account<<endl;
            cout<<"Address :\t\t"<<endl;
            (check->address).displayAddress();
            cout<<"Wallet balance :\t\t"<<(check->wallet).getBalance()<<endl;
            //Still we have to add show cart orders and pending orders
            return true; 
        }
        return false;

    }

    // add money to wallet from account
    static bool addMoneyFromAccount(double amount){
        cout<<"Directing to Bank Gateway"<<endl;
        ((Database::currentUser)->wallet).updateBalance(amount);
        return true;
    }

    // transfer money from wallet back to account
    static bool addMoneyToAccount(double amount){
        
        cout<<"Directing to Bank Gateway"<<endl;
        ((Database::currentUser)->wallet).updateBalance(-amount);
        return true;
    
    }

    // utility to return wallet balance
    static int getWalletBalance(){
        return ((Database::currentUser)->wallet).getBalance();
    }

    // to give ratings and reviews to a vendor
    static void rateVendor(Vendor* vendor, double rating, string review) {
        vendor->rating = (vendor->rating*vendor->numberOfRatings + rating)/(vendor->numberOfRatings+1);
        vendor->numberOfRatings++;
        vendor->reviews.push_back(review);
    }

};

// main class defining functions for handling orders
class OrderManager {
public:
    
    // make payment to a vendor and update customer's and admin's wallets
    static void makePayment(Order* order){
        Vendor* vendor = order->cartProducts[0].stock->vendor;

        double discount = order->cost*order->discount;
        vendor->updateWalletBalance(order->cost);
        if(order->paymentStatus == CASH_ON_DELIVERY) {
            Database::admin->updateWalletBalance(-order->cost);
            return;
        }
        (Database :: currentUser)->updateWalletBalance(-(order->cost - discount) - (order->deliveryCharge));
        (Database :: admin)->updateWalletBalance(order->deliveryCharge - discount);
    }

    // customer can confirm delivery upon receiving his order
    static bool confirmDelivery(Order* order) {
        if(order->status != DISPATCHED) return false;
        order->status = DELIVERED;

        if(order->paymentStatus == CASH_ON_DELIVERY) {
            Database::admin->updateWalletBalance(order->deliveryCharge + order->cost*(1-order->discount));
        }
        return true;
    }

    // to place an order for a single product and the chosen vendor selling it
    static bool placeOrder(Product* product,Stock* stock,int quantity,string deliverySlot,PaymentStatus paymentStatus){
        double discount = Database::discount;
        if(((Customer*)(Database::currentUser))->primeMember) discount += Database::primeDiscount;
        double amountToPay = ((stock->price*quantity)*(1-(discount)) + (Database :: deliveryCharge));
        if(quantity > stock->quantity || amountToPay > Database::currentUser->wallet.getBalance()) return false;
               
        stock->quantity = stock->quantity - quantity;
        product->quantitySold += stock->quantity;
        CartProduct* newCartPoduct = new CartProduct(product,stock,quantity);
        int id = (Database :: orders).size();
        Order* newOrder = new Order(id,*newCartPoduct,stock->price*quantity,discount, Database::deliveryCharge,deliverySlot,paymentStatus, (Customer*)(Database::currentUser));
        makePayment(newOrder);
        (Database :: currentUser)->orders.push_back(newOrder);
        (Database :: orders).push_back(newOrder);
        (stock->vendor)->orders.push_back(newOrder);
        return true;

    }

    // to add a product to cart alongwith the desired vendor and quantity
    static void addToCart(Product* product,Stock* stock,int quantity){
        CartProduct* newCartProduct = new CartProduct(product,stock,quantity);
        ((Customer*)(Database :: currentUser))->addCartProduct(*newCartProduct);
        
    }

    // to remove a product from cart according to its index in the cart
    static void removeFromCart(int index){
        ((Customer*)(Database :: currentUser))->removeCartProduct(index);
    }

    // display contents of the cart
    static void showCart(){
        ((Customer*)(Database::currentUser))->displayCart();
    }
    
    // to get a cart product according to index
    static CartProduct* getCartProduct(int choice){
        return &(((Customer*)(Database :: currentUser))->cart.cartProducts[choice]);
    }

    // to check that the quantity demanded is in stock and customer wallet has enough credit
    static bool checkCartOrderValidity() {
        double discount = Database::discount;
        if(((Customer*)(Database::currentUser))->primeMember) discount += Database::primeDiscount;
        double amountToPay = 0;
        unordered_map<int, bool> vendorPresent;
        int totalVendors = 0;
        for(auto cartProduct : ((Customer*)(Database::currentUser))->cart.cartProducts) {
            if (cartProduct.stock->quantity < cartProduct.quantity) return false;
            amountToPay += cartProduct.quantity*cartProduct.stock->price;
            if(vendorPresent.find(cartProduct.stock->getVendorID())==vendorPresent.end()) {
                totalVendors++;
                vendorPresent[cartProduct.stock->getVendorID()] = true;
            }
        }
        amountToPay = amountToPay - amountToPay*discount + totalVendors*Database::deliveryCharge;
        if(Database::currentUser->wallet.getBalance() < amountToPay) return false;
        return true;
    }

    // to order all products from the cart
    static bool placeOrderFromCart(string deliverySlot, PaymentStatus paymentStatus) {
        if(!checkCartOrderValidity()) return false;
        unordered_map<int, Order*> orders;
        Customer* customer = (Customer*) (Database::currentUser);
        double discount = Database::discount;
        if(((Customer*)(Database::currentUser))->primeMember) discount += Database::primeDiscount;
        for(auto cartProduct : customer->cart.cartProducts) {
            cartProduct.stock->quantity -= cartProduct.quantity;
            cartProduct.product->quantitySold += cartProduct.quantity;
            int vendorID = cartProduct.stock->getVendorID();
            if(orders.find(vendorID) == orders.end()) {
                orders[vendorID] = new Order(0, cartProduct, cartProduct.quantity*cartProduct.stock->price, discount, Database::deliveryCharge, deliverySlot, paymentStatus, (Customer*)(Database::currentUser));
            }
            else {
                orders[vendorID]->cartProducts.push_back(cartProduct);
                orders[vendorID]->cost += cartProduct.quantity*cartProduct.stock->price;
            }
        }
        for(auto order = orders.begin(); order!=orders.end(); order++) {
            order->second->orderID = Database::orders.size();
            makePayment(order->second);
            customer->orders.push_back(order->second);
            order->second->cartProducts[0].stock->vendor->orders.push_back(order->second);
            Database::orders.push_back(order->second);
        }
        return true;
    }

    // to display information about a product
    static void showOrder() {
        User* user = (Database::currentUser);
        for(auto itr:user->orders){
            if(user->type==VENDOR&&itr->status==ORDERED){
                itr->displayOrderVender();                
            }
            else if(user->type==CUSTOMER){
                itr->displayOrderCustomer();
            }
        }

    }

    // to cancel a placed order, with refund
    static bool cancelOrder(Order* order) {
        if(order->status == DELIVERED || order->status == CANCELLED) return false;
        
        for(auto cartProduct : order->cartProducts) {
            cartProduct.product->quantitySold -= cartProduct.quantity;
            cartProduct.stock->quantity += cartProduct.quantity;
        }
        

        if(order->paymentStatus == CASH_ON_DELIVERY) {
            order->cartProducts[0].stock->vendor->updateWalletBalance(-order->cost);
            Database::admin->updateWalletBalance(order->cost);
            return true;
        }
        if(order->status == ORDERED) {
            Database::admin->wallet.updateBalance(-order->deliveryCharge+order->discount*order->cost);
            (Database::currentUser)->wallet.updateBalance(order->cost*(1-order->discount) + order->deliveryCharge);
            order->cartProducts[0].stock->vendor->updateWalletBalance(-order->cost);
            return true;
        }
        order->cartProducts[0].stock->vendor->updateWalletBalance(-order->cost);
        Database::admin->wallet.updateBalance(order->discount*order->cost);
        (Database::currentUser)->wallet.updateBalance(order->cost*(1-order->discount));

        order->status = CANCELLED;
        return true;
    }

    
    // static void viewCustomerOrder(){
    //     for(int i=0;i<(int)((Database :: currentUser)->orders.size());i++){
    //         printSeparator();
    //         (Database::currentUser)->orders[i].
    //     }    
    // }

};