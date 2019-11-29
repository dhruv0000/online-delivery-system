
#include "utilities.hpp"

class ProductManager {
    public:
    static bool addProduct(string name, string type, int quantity, double price, string description = "none") {
        // if(Database::currentUser->)
        Stock* newStock = new Stock(0, (Vendor*) Database::currentUser, quantity, price);
        bool found = false;
        for(auto product: Database::products) {
            if(compareStringIgnoreCase(name, product->name)) {          
                for (auto stock: product->stocks) {
                    if(Database::currentUser->getUsername() == stock->vendor->getUsername()) {
                        stock->quantity += quantity;
                        stock->price = price;
                        found = true;
                        break;
                    }
                }
                if(found) break;
                newStock->stockID = product->stocks.size();
                product->stocks.push_back(newStock);
                found = true;
                break;
            }
        }
        if(found) return true;
        Product* newProduct = new Product(name, type, newStock, description);
        newProduct->productID = Database::products.size();
        Database::products.push_back(newProduct);
        return true;
    }
    
    static vector<Product*> getTopProducts(int count = 5) {
        vector<Product*> sortedProducts(Database::products);
        vector<Product*> productsToShow;
        sort(sortedProducts.begin(), sortedProducts.end(), Product::compareProduct);
        for(int i = 0; i < min((int)(sortedProducts.size()), count); i++) {
            productsToShow.push_back(sortedProducts[i]);
        }
        return productsToShow;
    }

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

    static bool setDiscount(double discount) {
        Database::discount = discount;
        return true;
    }

    static void searchAndDisplayVendor(Product* product){
        printSeparator();
        // printFlow();
        cout<<"Vendor Details Selling this product :"<<endl;
        for(int i=0;i<(product->stocks).size();i++){
            cout<<i+1<<":"<<endl;
            product->stocks[i]->vendor->displayUserInformation();
            cout<<"Quantity available :"<<product->stocks[i]->quantity<<endl;
            cout<<"Price offered by this vendor :"<<product->stocks[i]->price<<endl;
            product->stocks[i]->vendor->displayVendorRatings();
            
            
            printSeparator();
        }
        
    }
    static Stock* getStockPointer(Product *product,int vendorSelection){
        
        return product->stocks[min((int)(product->stocks.size()),vendorSelection)];
    }
    
    
    
};



class UserManager{
public:

    static bool registerUser(string username, unsigned long long hashPassword, string account, Address address, Type type){
        if(type == VENDOR){
            User* newVendor = new Vendor(username,hashPassword,account,address);
            newVendor->userID = Database::users.size();
            (Database :: users).push_back(newVendor);
        }
        else if(type == CUSTOMER){
            User* newCustomer = new Customer(username,hashPassword,account,address);
            newCustomer->userID = Database::users.size();
            (Database :: users).push_back(newCustomer);
        }

        return true;
    }

    static bool checkUserNameAvailable(string username){
    
        for(auto presentUserNameCheck : Database::users){
            if(presentUserNameCheck->username == username) return false;
        }
        return true;
    }
    
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

    static bool logoutUser(){
        if(Database :: currentUser == NULL) return false;
        Database :: currentUser = NULL;
        return true;
    }

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

    static bool addMoneyFromAccount(double amount){
        printSeparator();
        cout<<"Directing to Bank Gateway"<<endl;
        ((Database::currentUser)->wallet).updateBalance(amount);
        printSeparator();
        return true;
    }

    static bool addMoneyToAccount(double amount){
        
        printSeparator();
        cout<<"Directing to Bank Gateway"<<endl;
        ((Database::currentUser)->wallet).updateBalance(-amount);
        printSeparator();
        return true;
    
    }

    static int getWalletBalance(){
        return ((Database::currentUser)->wallet).getBalance();
    }

};

class OrderManager {
public:
    
    static void makePayment(Order* order){
        Vendor* vendor = order->cartProducts[0].stock->vendor;
        double amountToPay = 0;
        for(auto cartProduct : order->cartProducts) {
            amountToPay += cartProduct.quantity * cartProduct.stock->price;
        }
        double discount = amountToPay*Database::discount;
        vendor->updateWalletBalance(amountToPay);
        if(order->paymentStatus == CASH_ON_DELIVERY) {
            Database::admin->updateWalletBalance(-amountToPay);
            return;
        }
        (Database :: currentUser)->updateWalletBalance(-(amountToPay - discount) - (Database :: deliveryCharge));
        (Database :: admin)->updateWalletBalance(Database::deliveryCharge - discount);
    }

    // static bool confirmDelivery(Order* order) {
    //     if(order->status != DISPATCHED) return false;
    //     order->status = DELIVERED;
    //     if(order->paymentStatus == CASH_ON_DELIVERY) {
    //         Database::admin->updateWalletBalance(Database::deliveryCharge - )
    //     }
    // }

    static bool placeOrder(Product* product,Stock* stock,int quantity,string deliverySlot,PaymentStatus paymentStatus){
        double amountToPay = ((stock->price*quantity)*(1-(Database :: discount)) + (Database :: deliveryCharge));
        if(quantity > stock->quantity || amountToPay > Database::currentUser->wallet.getBalance()) return false;
               
        stock->quantity = stock->quantity - quantity;
        CartProduct* newCartPoduct = new CartProduct(product,stock,quantity);
        int id = (Database :: orders).size();
        Order* newOrder = new Order(id,*newCartPoduct,amountToPay,deliverySlot,paymentStatus, (Customer*)(Database::currentUser));
        makePayment(newOrder);
        cout<<"AfterrMakePaymentFuck"<<endl;
        (Database :: currentUser)->orders.push_back(newOrder);
        (Database :: orders).push_back(newOrder);
        (stock->vendor)->orders.push_back(newOrder);
        return true;

    }

    static void addToCart(Product* product,Stock* stock,int quantity){
        CartProduct* newCartProduct = new CartProduct(product,stock,quantity);
        ((Customer*)(Database :: currentUser))->addCartProduct(*newCartProduct);
        

    }

    static void removeFromCart(int index){
        ((Customer*)(Database :: currentUser))->removeCartProduct(index);
    }
    static void showCart(){
        ((Customer*)(Database::currentUser))->displayCart();
    }
    static bool checkCartOrderValidity() {
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
        amountToPay = amountToPay - amountToPay*Database::discount + totalVendors*Database::deliveryCharge;
        if(Database::currentUser->wallet.getBalance() < amountToPay) return false;
        return true;
    }
    static bool placeOrderFromCart(string deliverySlot, PaymentStatus paymentStatus) {
        if(!checkCartOrderValidity()) return false;
        unordered_map<int, Order*> orders;
        Customer* customer = (Customer*) (Database::currentUser);
        for(auto cartProduct : customer->cart.cartProducts) {
            cartProduct.stock->quantity -= cartProduct.quantity;
            int vendorID = cartProduct.stock->getVendorID();
            if(orders.find(vendorID) == orders.end()) {
                orders[vendorID] = new Order(0, cartProduct, cartProduct.quantity*cartProduct.stock->price, deliverySlot, paymentStatus, (Customer*)(Database::currentUser));
            }
            else {
                orders[vendorID]->cartProducts.push_back(cartProduct);
                orders[vendorID]->cost += cartProduct.quantity*cartProduct.stock->price;
            }
        }
        for(auto order = orders.begin(); order!=orders.end(); order++) {
            order->second->cost -= Database::discount*order->second->cost;
            order->second->cost += Database::deliveryCharge;
            order->second->orderID = Database::orders.size();
            makePayment(order->second);
            customer->orders.push_back(order->second);
            order->second->cartProducts[0].stock->vendor->orders.push_back(order->second);
            Database::orders.push_back(order->second);
        }
        return true;
    }

    static void showOrder() {
        User* user = (Database::currentUser);
        for(auto itr:user->orders){
            printSeparator();
            if(user->type==VENDOR){
                itr->displayOrderVender();                
            }
            else if(user->type==CUSTOMER){
                itr->displayOrderCustomer();
            }
        }

    }

    
    // static bool cancelOrder(Order* order) {
    //     if(order->status == DELIVERED || order->status == CANCELLED) return false;
    //     if(order->paymentStatus == CASH_ON_DELIVERY) {
    //         order->cartProducts
    //     }
    //     if(order->paymentStatus == WALLET && (order->status == PENDING || order->status == ORDERED)) {
    //         Database::admin->wallet.updateBalance(-Database::deliveryCharge);
    //         ((Customer*)(Database::currentUser))->wallet.updateBalance(Database::deliveryCharge);
    //     }

    //     for(auto cartProduct : order->cartProducts) {
            
    //     }
    //     order->status = CANCELLED;
    // }

    // static void viewCustomerOrder(){
    //     for(int i=0;i<(int)((Database :: currentUser)->orders.size());i++){
    //         printSeparator();
    //         (Database::currentUser)->orders[i].
    //     }    
    // }

};
