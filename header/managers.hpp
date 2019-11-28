
#include "utilities.hpp"

class ProductManager {
    public:
    static bool addProduct(string name, string type, int quantity, double price, string description = "none") {
        // if(Database::currentUser->)
        Stock* newStock = new Stock((Vendor*) Database::currentUser, quantity, price);
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
        for(int i = 0; i < min((int)sortedProducts.size(), count); i++) {
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
            if(product->name.find(query) != string::npos || product->type.find(query) != string::npos) {
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
    

};



class UserManager{
public:
    static bool registerUser(string username, unsigned long long hashPassword, string account, Address address, Type type){
        if(type == VENDOR){
            User* newVendor = new Vendor(username,hashPassword,account,address);
            newVendor->userID = Database::users.size();
            (Database :: users).push_back(newVendor);
        }
        else{
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

    // static bool placeOrder(Product* product,Stock* stock,int qty) { //For single product
    // }

    // static bool addToCart(Product* product,Stock* stock,int qty) {
    //     OrderStatus lastOrder = (Database :: orders).back()->getOrderStatus();
    //     if(lastOrder != PENDING){
    //         Order* order = new Order((Database::orders).size());
    //         (Database::orders).push_back(order);
    //         (Database::currentUser)->orders.push_back(order);
    //     }
    //     Order* order = *(Database::orders).end();
    //     CartProduct* cartProduct = new CartProduct(product,stock,qty);
    //     order->cartProducts.push_back(*cartProduct);
    //     order->cost+=stock->price*qty;
    //     return true;
    // }

    // static void viewCartProduct(){

    // }

    // static bool makePayment(){
    //     User* currentUser = Database::currentUser;
    //     Order* lastOrder= *currentUser->orders.end();
    //     lastOrder->paymentStatus=WALLET;
    //         if(currentUser->wallet.getBalance() < lastOrder->cost||lastOrder->status!=PENDING)
    //             return false;
            
    //         currentUser->wallet.updateBalance(-1*lastOrder->cost);
    //         Database::admin->wallet.updateBalance(lastOrder->cost);
    //         return true;
    // }

    // static bool placeOrderFromCart() {
    //     User* currentUser = Database::currentUser;
    //     OrderStatus lastOrder = currentUser->orders.back()->status;
    //     if(lastOrder!=PENDING)
    //         return false;
    //     Order* order = currentUser->orders.back();
    //     for (int i = 0; i < order->cartProducts.size(); i++)
    //     {

    //     }
        
        

    // }

    
    //For payment
    static void makePayment(Stock* stock,int quantity,PaymentStatus status){
        
        if(status == CASH_ON_DELIVERY)return;
        ((Database :: currentUser))->updateWalletBalance(-(quantity * stock->price*(1-(Database::discount)) + (Database :: deliveryCharge)));
        Vendor* temp = stock->vendor;
        temp->updateWalletBalance(quantity * stock->price); 
        (Database :: admin)->updateWalletBalance(Database::deliveryCharge - quantity * stock->price*(Database::discount));

    }

    static bool placeOrder(Product* product,Stock* stock,int quantity,string deliverySlot,PaymentStatus paymentStatus){

        stock->quantity = stock->quantity - quantity;
        makePayment(stock,quantity,paymentStatus);
        CartProduct* newCartPoduct = new CartProduct(product,stock,quantity);
        int id = (Database :: orders).size();
        double amountToPay = ((stock->price*quantity)*(1-(Database :: discount)) + (Database :: deliveryCharge));
        Order* newOrder = new Order(id,*newCartPoduct,amountToPay,deliverySlot,paymentStatus);
        (Database :: currentUser)->orders.push_back(newOrder);
        (Database :: orders).push_back(newOrder);
        (stock->vendor)->orders.push_back(newOrder);
        return true;

    }

    static void addToCart(Product* product,Stock* stock,int quantity){
        CartProduct* newCartProduct = new CartProduct(product,stock,quantity);
        ((Customer*)Database :: currentUser)->addCartProduct(*newCartProduct);
        

    }

static void removeFromCart(int index){
        ((Customer*)Database :: currentUser)->removeCartProduct(*newCartProduct);
    }
    

};
