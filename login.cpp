#include "header/managers.hpp"
// #include <conio.h>

using namespace std;
// void blueStart(){
//     cout<<"\033[1;36m";
// }
// void redStart(){
//     cout<<"\033[1;31m";
// }
// void greenStart(){
//     cout<<"\033[1;32m";
// }
// void yellowStart(){
//     cout<<"\033[1;33m";
// }
// void cyanStart(){
//     cout<<"\033[1;36m";
// }

// void blueBackStart(){
//     cout<<"\033[1;44m";
// }
// void redBackStart(){
//     cout<<"\033[1;41m";
// }
// void greenbackStart(){
//     cout<<"\033[1;42m";
// }
// void yellowBackStart(){
//     cout<<"\033[1;43m";
// }
// void cyanBackStart(){
//     cout<<"\033[1;46m";
// }

// void end(){
//     cout<<"\033[0m";
// }


void printFlow(){
  cout<<"Enter the number corresponding to funtion you wish to perform"<<endl;
}

void getPassword(string *password) {
    char ch;
    ch = getchar();
    cout<<"\b ";

    while (ch!='\n')
    {
        password->push_back(ch);
        cout<<"\b ";
        ch = getchar();
    }
    
}

void printLoginChoice(){
    printFlow();
    // cyanStart();
    cout<<"1 : New User"<<endl;
    cout<<"2 : Login as Admin"<<endl;
    cout<<"3 : Login as Customer"<<endl;
    cout<<"4 : Login as Vendor"<<endl;
    cout<<"5 : Exit Store"<<endl;
    // end();
    }
void printUserChoice(){
    printFlow();
    cout<<"1: Register as Customer"<<endl;
    cout<<"2: Register as Vendor"<<endl;
    cout<<"3: Go to start menu"<<endl;
}

void getDetails(string& username,string& password,unsigned long long& hashPassword,string& rePassword,
    string& accountNumber,Address& address,Type& type,char wish){
    
    EnterNewUserName : 
        cout<<endl;  
        cout<<"Enter the following details"<<endl;
        cout<<"Enter your User Name(without space) : ";
        std :: cin>>username;
                
        if(!(UserManager :: checkUserNameAvailable(username))){
            cout<<endl;
            cout<<"This User Name already exists"<<endl;
            goto EnterNewUserName;
        }

        do{
            do{
                cout<<"Enter your Password(should contain  at least 6 characters,atleast 1 Upper Case,Lower Case and Digit character and should not contain  spaces) : ";
                std :: cin>>password;
                // getPassword(&password);

                if(Password :: checkStrength(password))
                    break;

                cout<<"Password is not strong enough "<<endl;
            
                }while(true);

                cout<<"Re-Enter your Password : ";
                std :: cin>>rePassword;
            
                if(password == rePassword)
                    break;
                cout<<endl;
                cout<<"Your Password didn't match"<<endl;
                cout<<endl;

        }while(true);

        cout<<"Enter your Account Number : ";
        std :: cin>>accountNumber;
        address.storeAddress();
        hashPassword = Password :: hashValue(password);
        if(wish == '1'){
            type = CUSTOMER;
        }else{
             type = VENDOR;
        }
        
}
void displayUsername(){
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<Database :: currentUser -> getUsername()<<endl;
}

void printAdminChoices(){
    cout<<"1: Set delivery charges"<<endl;
    cout<<"2: Set discount percentage"<<endl;
    cout<<"3: Logout"<<endl;
}


void setDeliveryCharges(){
    double charge;
    cout<<"Enter delivery charges : ";
    std :: cin>>charge;
    Database :: deliveryCharge = charge;
}

void setDiscountPercentage(){
    double percentage;
    cout<<"Enter the percentage : ";
    std :: cin>>percentage;
    Database :: discount = percentage;
}

void getUserDetails(string &username,string &password,unsigned long long &value){
    
    cout<<"Enter your username(without spaces) :";
    std :: cin>>username;
    cout<<"Enter your password :";
    std :: cin>>password;
    value = Password :: hashValue(password);

}

void showTopSearch(vector<Product*> v){
    printFlow();
    for(int i=0;i<v.size();i++){
        printSeparator();
        cout<<"\033[1;36mBuy Product "<<i+1<<":\033[0m"<<endl;
        v[i]->displayProduct();
    }
}

void showFuntionality(int i){
    // blueStart();
    cout<<i+1<<":Search products"<<endl;
    cout<<i+2<<":Show cart"<<endl;
    cout<<i+3<<":Show wallet balance"<<endl;
    cout<<i+4<<":Show ordered products"<<endl;
    cout<<i+5<<":Logout"<<endl;
    // end();
}

void displaySearchProduct(vector<Product*> searchedProduct){
    printSeparator();
    cout<<"Enter the number of the product which you are liking"<<endl;
    int i=1;
    for(auto presentProduct : searchedProduct){
        cout<<i<<endl;
        presentProduct->displayProduct();
        printSeparator();
        i++;
    }
}

void displayVendorChoices(){
    printFlow();
    cout<<"1:Add product to our shop"<<endl;
    cout<<"2:Show Pending orders"<<endl;
    cout<<"3:Show wallet balance"<<endl;
    cout<<"4:See reviews and ratings"<<endl;
    cout<<"5:Add money from wallet to Bank Account"<<endl;
    cout<<"6:Logout"<<endl;
}

void getProductDetails(string &name,string &type,int &quantity,double &price,string &description){
    cout<<"\nEnter the followig details"<<endl;
    cout<<"Name your product name:";
    getchar();
    getline(cin,name);
    cout<<"Enter your product type:";
    getline(cin,type);
    cout<<"Enter quantity(must be an integer value):";
    cin>>quantity;
    cout<<"Enter price(must be decimal value):";
    cin>>price;
    cout<<"Would you liketo add description of your product?Y/N";
    char check;
    cin>>check;
    if(check == 'Y'||check=='y'){
        cout<<"Enter description in one line :"<<endl;
        getline(cin,description);
    }

}

void displayProductAcceptance(){
    printSeparator();
    displayUsername();
    printFlow();
    cout<<"1:Add to Cart"<<endl;
    cout<<"2:Buy Product"<<endl;
    cout<<"3:Go to Customer Choices"<<endl;
}

void getOrderInformation(string &slot,PaymentStatus &status){
    printSeparator();
    printFlow();
    cout<<"Enter the timimgs when you are available to take delivery "<<endl;
    cout<<"1:Morning"<<endl;
    cout<<"2:Afternoon"<<endl;
    cout<<"3:Evening"<<endl;
    cout<<"4:Night"<<endl;
    int time;
    cin>>time;
    if(time==1)slot = "Morning";
    else if(time==2)slot = "Afternoon";
    else if(time == 3)slot = "Evening";
    else slot = "Night";
    cout<<time<<endl;
    printSeparator();
    cout<<"Enter the payment mode"<<endl;
    cout<<"1:Cash On Delivery"<<endl;
    cout<<"2:Wallet Money"<<endl;
    // status=WALLET;
    int t;
    cin>>t;
    if(t==1)
        status = CASH_ON_DELIVERY;
    else 
        status = WALLET;
}

void cartChoices(){
    printSeparator();
    // blueStart();
    cout<<"1:Order the cart items"<<endl;
    cout<<"2:Remove from cart"<<endl;
    // end();
}

int main(){
    Database :: readFromDatabase();
    char wish;
    cout<<"\033[1;44mWelcome to our Online Store\033[0m"<<endl;
    
    SignIn: 
    printLoginChoice();
    std :: cin>>wish;

    if(wish == '1') {
        
        Registration:
        char userWish;
        printUserChoice();
        
        std :: cin>>userWish;
        
        if(userWish == '3')
            goto SignIn;

        string username,password,accountNumber,rePassword;
        unsigned long long hashPassword;
        Address address;
        Type type;

        if(userWish ==  '1' || userWish == '2'){
            getDetails(username,password,hashPassword,rePassword,accountNumber,address,type,userWish);
        }else{
            cout<<"You have entered wrong wish"<<endl;
            goto Registration;
        }

        if(UserManager :: registerUser(username, hashPassword, accountNumber, address, type)){
            printSeparator();
            cout<<"You have successfully created new account (:"<<endl;
            if(type == CUSTOMER)
                cout<<"Please login into your account to purchase our products"<<endl;
            else
                cout<<"Please login into your account to do business with us"<<endl;
            printSeparator();
            goto SignIn;
        }
        
    }else if(wish == '2') {
        // For Login as Admin
        string username,password;
        
        
        cout<<"Enter your username (without spaces):";
        std :: cin>>username;
        cout<<"Enter your password:";
        std :: cin>>password;
        unsigned long long hashValue = (Password :: hashValue(password));
        
        if((username == Database :: admin->getUsername()) &&  hashValue == (Database :: admin->getPassword())){
            
            AdminRun:
            
            printAdminChoices();
            char adminWish;
            std :: cin>>adminWish;
            if(adminWish == '1')setDeliveryCharges();
            else if(adminWish == '2')setDiscountPercentage();
            else if(adminWish == '3'){
                UserManager :: logoutUser();
                goto SignIn;
            }else{
                 cout<<"Admin Please enter correct choice"<<endl;
                 goto AdminRun;
            }

        }else{
            cout<<"You have entered wrong password"<<endl;
            goto SignIn;
        }
        goto SignIn;
        
    }
    else if(wish == '3'){
       
        string username,password;
        unsigned long long hashValue;
        printSeparator();
        getUserDetails(username,password,hashValue);
        printSeparator();
        
        if(!UserManager::loginUser(username,hashValue)){
            cout<<"\nYou have entered wrong username or password\n\n";
            goto SignIn;
        }
        if((Database :: currentUser)->getType() != CUSTOMER){
            cout<<"\nOops you are not CUSTOMER\n";
            cout<<"Please select proper category\n"<<endl;
            goto SignIn;
        }

        printSeparator();
        cout<<"You are Logged In successsfully (:"<<endl;
        displayUsername();
        vector<Product*> topSearch = ProductManager :: getTopProducts(3);
        
        int customerWish;
        CustomerChoices:

        showTopSearch(topSearch);
        showFuntionality(topSearch.size());
        cin>>customerWish;
        
        if(customerWish>=1 && customerWish <=(int)(topSearch.size())){
            ProductManager :: searchAndDisplayVendor(topSearch[--customerWish]);
            int vendorSelection;
            cin>>vendorSelection;
            vendorSelection--;
            Stock* stock = ProductManager :: getStockPointer(topSearch[customerWish],vendorSelection);
            // cout<<"Manan"<<endl;
            // cout<<stock->price<<endl;
            // cout<<"Manan"<<endl;
            TopProductAcceptance:

            int productAcceptance;
            displayProductAcceptance();
            cin>>productAcceptance;
                
            
            // if(quantity>stock->quantity){
            //     cout<<"Vendor does not have enough supply"<<endl;
            //     goto TopProductAcceptance;
            // }
                
            if(productAcceptance == 1){
                int quantity;
                cout<<"Number of quantity you want to purchase :";
                cin>>quantity;
                OrderManager :: addToCart(topSearch[customerWish],stock,quantity);
                cout<<"Your Product has bee added into cart (:"<<endl;
                goto CustomerChoices;
                
            }else if(productAcceptance == 2){
                int quantity;
                cout<<"Number of quantity you want to purchase :";
                cin>>quantity;    
                string deliverySlot;
                PaymentStatus paymentStatus;
                getOrderInformation(deliverySlot,paymentStatus);
                OrderManager :: placeOrder(topSearch[customerWish],stock,quantity,deliverySlot,paymentStatus);
                cout<<"Your order  hass"<<endl;
                goto CustomerChoices;

            }else if(productAcceptance == 3){
                goto CustomerChoices;
            }else{
                cout<<"You have Entered wrong choice"<<endl;
                    goto TopProductAcceptance;
            } 
        }
        else if(customerWish  == (int)(topSearch.size())+1){
            string searchString;
            cout<<"Enter about product which you wish to search :";
            cin>>searchString;
            vector<Product*>  searchProduct= ProductManager :: searchProducts(searchString);

            if(searchProduct.size() == 0){
                cout<<"\nSorry, Presently we don't have the required product.You can search for it afterwards at our store\n\n";
                goto CustomerChoices; 
            }

            
            int productWish;
            displaySearchProduct(searchProduct);
            cin>>productWish;
            

            if(productWish >= 1 && productWish <= (int)(searchProduct.size())){
                productWish--;
                ProductManager :: searchAndDisplayVendor(searchProduct[productWish]);
                // displayVendorList(availableVendors);
                int vendorSelection;
                cin>>vendorSelection;
                vendorSelection--;
                Stock* stock = ProductManager :: getStockPointer(searchProduct[productWish],vendorSelection);
                cout<<stock->price<<endl;
                ProductAcceptance:

                int productAcceptance;
                displayProductAcceptance();
                cin>>productAcceptance;
                
                
                // if(quantity>stock->quantity){
                //     cout<<"Vendor does not have enough supply"<<endl;
                //     goto ProductAcceptance;
                // }
                
                if(productAcceptance == 1){
                    int quantity;
                    cout<<"Number of quantity you want to purchase :";
                    cin>>quantity;
                    OrderManager :: addToCart(searchProduct[productWish],stock,quantity);
                    cout<<"Your Product has bee added into cart (:"<<endl;
                    goto CustomerChoices;
                
                }else if(productAcceptance == 2){
                    
                    int quantity;
                    cout<<"Number of quantity you want to purchase :";
                    cin>>quantity;
                    string deliverySlot;
                    PaymentStatus paymentStatus;
                    cout<<"Fff"<<endl;
                    getOrderInformation(deliverySlot,paymentStatus);
                    // cout<<paymentStatus<<" "<<deliverySlot<<endl;
                    cout<<stock->price<<endl;
                    cout<<searchProduct[0]->getProductName()<<endl;
                    OrderManager :: placeOrder(searchProduct[0],stock,quantity,deliverySlot,paymentStatus);
                    cout<<"Your order have been place successfully(:"<<endl;
                    printSeparator();

                }else if(productAcceptance == 3){
                    goto CustomerChoices;

                }else{
                    cout<<"You have Entered wrong choice"<<endl;
                    goto ProductAcceptance;
                }
            }else{
                goto CustomerChoices;
            }


        }else if((customerWish == (topSearch.size()+2))){
            //For Cart Department
            CartChoices:

            cout<<"\033[1;33mYour Cart Products are shown below :\033[0m"<<endl;
            OrderManager :: showCart();
            cartChoices();
            int cartChoice;
            cin>>cartChoice;
            
            if(cartChoice == 1){
                string deliverySlot;
                PaymentStatus paymentStatus;
                getOrderInformation(deliverySlot,paymentStatus);
                OrderManager :: placeOrderFromCart(deliverySlot,paymentStatus);

            }else if(cartChoice == 2){
                cout<<"Enter the cart product you wish to remove:";
                int cartChoice;
                cin>>cartChoice;
                CartProduct *cartProduct = OrderManager :: getCartProduct(cartChoice);
                cout<<"Your Product has been removed"<<endl;


            }else{
                // redStart();
                cout<<"You have entered wrong choice"<<endl;
                // end();
                goto CartChoices;
            }


            goto CustomerChoices;

        }else if(customerWish == (topSearch.size()+3)){
            char operation;
            cout<<"Your Wallet has "<<UserManager :: getWalletBalance()<<"rupees"<<endl;
            cout<<"Do you want to add money to your wallet from bank account(y/n)? ";
            cin>>operation;
            if(operation == 'y' ||operation == 'Y'){
                double amt;
                cout<<"Enter the amount you want to add: "<<endl;
                cin>>amt;
                UserManager :: addMoneyFromAccount(amt);
            }
            cout<<"Do you want to extract money from your wallet to bank account(y/n)? ";
            cin>>operation;
            if(operation == 'y' ||operation == 'Y'){
                double amt;
                cout<<"Enter the amount you want to extract: "<<endl;
                cin>>amt;
                UserManager :: addMoneyToAccount(amt);
            }
            cout<<"Your Wallet has "<<UserManager :: getWalletBalance()<<"rupees"<<endl;
            goto CustomerChoices;
        } else if (customerWish == (topSearch.size()+4)) {
            OrderManager::showOrder();
            goto CustomerChoices;
        }
        else if(customerWish==(int)(topSearch.size())+4){
            OrderManager::showOrder();
            goto CustomerChoices;
        }
        else if(customerWish == (int)(topSearch.size())+5){
            UserManager :: logoutUser();
            goto SignIn;
        }
        else{
            cout<<"\033[1;31mYou have entered wrong choice\033[0m"<<endl;
            goto CustomerChoices;
        }
       

    }
    else if (wish == '4') {
        string username,password;
        unsigned long long hashValue;
        getUserDetails(username,password,hashValue);

        if(!UserManager :: loginUser(username,hashValue)){
            cout<<"\nYou have entered wrong username or password\n\n";
            goto SignIn; 
        }
        if((Database :: currentUser)->getType() != VENDOR){
            cout<<"\nOops you are not VENDOR\n";
            cout<<"Please select proper category\n"<<endl;
            goto SignIn;
        }

        VendorChoices:
        
        displayUsername();
        char vendorWish;
        displayVendorChoices();
        cin>>vendorWish;
        
        if(vendorWish == '1'){
            string name,type,description;
            int quantity;
            double price;

            getProductDetails(name,type,quantity,price,description);

            if(!(ProductManager :: addProduct(name,type,quantity,price,description))){
                cout<<"Sorry something went wrong"<<endl;
                cout<<"Try after Sometime to add product"<<endl;
                goto VendorChoices;
            }
            cout<<"Your product have been added succesfully (:"<<endl;
            goto VendorChoices;

        }else if (vendorWish == '2'){
            OrderManager::showOrder();


        }
        else if(vendorWish == '3'){
            
            printSeparator();
            cout<<"Your wallet has "<<UserManager :: getWalletBalance()<<endl;
            goto VendorChoices;

        }else if(vendorWish == '4'){

            printSeparator();
            ((Vendor*)(Database :: currentUser))->displayVendorRatings();
            goto VendorChoices;
        
        }
        else if(vendorWish == '5'){
           
            printSeparator();
            cout<<"Your wallet has "<<UserManager :: getWalletBalance()<<endl;
            cout<<"Enter the amount you wish to add to your bank account"<<endl;
            double amount;
            cin>>amount;
            if(amount > UserManager :: getWalletBalance()){
                printSeparator();
                cout<<"Sorry you don't haveenough balance"<<endl;
                goto VendorChoices;
            }
            UserManager :: addMoneyToAccount(amount);
            //Last mai dekhege...
            // if((Database :: currentUser)->getWalletBalance()<0){
            //     cout<<"You don't have enough money in account"
            // }
            cout<<"Now your wallet has "<<UserManager :: getWalletBalance()<<endl;
            goto VendorChoices;

        }
        else if(vendorWish == '6')
            goto SignIn;
        else{
            printSeparator();
            cout<<"You have entered wrong choice"<<endl;
            printSeparator();
            goto VendorChoices;
        }

    }
    else if (wish != '5'){
        cout<<"You have entered wrong choice"<<endl;
        goto SignIn;
    }

    Database::writeToDatabase();
    // Database :: writeToDatabase<User>(Database::vendors,"user.txt");
    
}