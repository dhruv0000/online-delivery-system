#include "header/managers.hpp"
// #include <conio.h>

using namespace std;





void printFlow(){
    
}

// void getPassword(string *password) {
//     char ch;
//     ch = getchar();
//     cout<<"\b ";

//     while (ch!='\n')
//     {
//         password->push_back(ch);
//         cout<<"\b ";
//         ch = getchar();
//     }
    
// }

int printLoginChoice(){ 

    string s[] = {"1 : New User","2 : Login as Admin","3 : Login as Customer","4 : Login as Vendor","5 : Exit Store"};
    return displayBox(s,5);

}

int printUserChoice(){
    string s[] = {"1:Register as Customer","2: Register as Vendor","3: Go to start menu"};
    return displayBox(s,3);
}


void getDetails(string username,string password,unsigned long long& hashPassword,string rePassword,
    string accountNumber,Address& address,Type& type,int wish){
    
        clear();
        char t[100]; 
        EnterNewUserName : 
        // char username[100];

        clear();
        char in[] = "Enter your User Name(without space) : ";
        displayWindow(in,t);
        username = string(t); 
       
        // getch();

        if(!(UserManager :: checkUserNameAvailable(username))){
            clear();
            mvprintw(1,1,"This User Name already exists\n");
            goto EnterNewUserName;
        }
        clear();
        do{
            do{
                char in1[] ="Enter your Password(should contain  at least 6 characters,atleast 1 Upper Case,Lower Case and Digit character";   
                char in10[] = "and should not contain spaces) : ";
                displayWindow(in10,t,in1);
                password = string(t);


                if(Password :: checkStrength(password))
                    break;

                clear();
                mvprintw(10,5,"Password is not strong enough\n");
                refresh();
            
                }while(true);

                char in2[] = "Re-Enter your Password : ";
                displayWindow(in2,t);
                rePassword = string(t);
            
                if(password == rePassword)
                    break;
                
                clear();
                mvprintw(10,5,"Your Password didn't match\n");
                refresh();
        
        }while(true);

        char in3[] = "Enter your Account Number : ";
        displayWindow(in3,t);
        accountNumber = string(t);
        

        address.storeAddress();
        hashPassword = Password :: hashValue(password);
        if(wish == '1'){
            type = CUSTOMER;
        }else{
             type = VENDOR;
        }
        
}

void displayUsername(WINDOW* window){
    int xMax,yMax;
    getmaxyx(window,yMax,xMax);
    mvwprintw(window,xMax-(Database :: currentUser -> getUsername()).length(),0,(Database :: currentUser -> getUsername()).c_str());
    // cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<Database :: currentUser -> getUsername()<<endl;
}

int printAdminChoices(){
    string s[] = {"1: Set delivery charges","2: Set discount percentage","3: Logout"};
    return displayBox(s,3);
}


void setDeliveryCharges(){
    char charge[100];
    char in[]="Enter delivery charges : ";
    displayWindow(in,charge);
    Database :: deliveryCharge = stod(charge);
}

void setDiscountPercentage(){
    char percentage[100];
    char in[]="Enter the percentage : ";
    displayWindow(in,percentage);
    Database :: discount = stod(percentage);
}

void getUserDetails(string &username,string &password,unsigned long long &value){
    
    char user[100],pass[100];
    
    clear();
    char in[]="Enter your username(without spaces) :";
    displayWindow(in,user);
    username=string(user);
    
    clear();
    char in2[]="Enter your password :";
    displayWindow(in2,pass);
    password=string(pass);

    value = Password :: hashValue(password);

}

void showTopSearch(vector<Product*> v){
    move(5,5);
    for(int i=0;i<v.size();i++){
        printw("Buy Product: %d\n",i);
        v[i]->displayProduct();
    }

}

int showFuntionality(int n){
    string str[10];
    for(int i=0;i<n;i++){
        str[i] = "Product "+to_string(i+1);
    }
    str[n+1] = ":Search products";
    str[n+2] = ":Show cart";
    str[n+3] = ":Show wallet balance";
    str[n+4] = ":Show ordered products";
    str[n+5] = ":Logout";
    return displayBox(str,n+5);

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

int displayVendorChoices(){
    string in[6];
    in[0]="1:Add product to our shop";
    in[1]="2:Show Pending orders";
    in[2]="3:Show wallet balance";
    in[3]="4:See reviews and ratings";
    in[4]="5:Add money from wallet to Bank Account";
    in[5]="6:Logout";
    displayBox(in,6);
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
    if(check == 'Y'){
        cout<<"Enter description in one line :";
        getline(cin,description);
    }

}

void displayProductAcceptance(){
    
    string a[]={"1:Add to Cart","2:Buy Product","3:Go to Customer Choices"};
    displayBox(a,3);
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

void greenColor(){
attron(COLOR_PAIR(1));
}
void endGreenColor(){
attroff(COLOR_PAIR(1));
}
int main(){
    Database :: readFromDatabase();
    
    initscr();
        
    SignIn:
    
    int wish;
    wish = printLoginChoice();
    
    if(wish == 1) {
        
        Registration:
        char userWish = printUserChoice();
        
        if(userWish == 3)
            goto SignIn;

        string username,password,accountNumber,rePassword;
        unsigned long long hashPassword;
        Address address;
        Type type;

        if(userWish ==  1|| userWish == 2){
            getDetails(username,password,hashPassword,rePassword,accountNumber,address,type,userWish);
        }

        if(UserManager :: registerUser(username, hashPassword, accountNumber, address, type)){
            clear();
            mvprintw(5,5,"You have successfully created new account (:");
            if(type == CUSTOMER)
                mvprintw(6,5,"Please login into your account to purchase our products");
            else
                mvprintw(6,5,"Please login into your account to do business with us");
            goto SignIn;
        }
        
    }else if(wish == 2) {
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
            goto AdminRun;
        }
        goto AdminRun;
        
    }
    else if(wish == 3){
       
        string username,password;
        unsigned long long hashValue;
        getUserDetails(username,password,hashValue);

        
        if(!UserManager::loginUser(username,hashValue)){
            clear();
            mvprintw(5,5,"You have entered wrong username or password");
            goto SignIn;
        }
        if((Database :: currentUser)->getType() != CUSTOMER){
            clear();
            mvprintw(5,5,"Oops you are not CUSTOMER");
            mvprintw(6,5,"Please select proper category");
            goto SignIn;
        }


        mvprintw(10,5,"You are Logged In successsfully (:");

        vector<Product*> topSearch = ProductManager :: getTopProducts(3);
        
        
        CustomerChoices:

        showTopSearch(topSearch);
        int customerWish = showFuntionality(topSearch.size());
        
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
        }
        else if(customerWish == (topSearch.size()+4)){
            
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
    else if (wish == 4) {
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
        
        // displayUsername();
        char vendorWish;
        displayVendorChoices();
        cin>>vendorWish;
        
        if(vendorWish == '1'){
            string name,type,description;
            int quantity;
            double price;

            getProductDetails(name,type,quantity,price,description);

            if(!(ProductManager :: addProduct(name,type,quantity,price,type))){
                cout<<"Sorry something went wrong"<<endl;
                cout<<"Try after Sometime to add product"<<endl;
                goto VendorChoices;
            }
            cout<<"Your product have been added succesfully (:"<<endl;
            goto VendorChoices;

        }else if (vendorWish == '2'){



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
    else if (wish != 5){
        cout<<"You have entered wrong choice"<<endl;
        goto SignIn;
    }
    endwin();
    Database::writeToDatabase();

    // Database :: writeToDatabase<User>(Database::vendors,"user.txt");
    
}