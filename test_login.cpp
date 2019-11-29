#include "header/managers.hpp"
// #include <conio.h>

using namespace std;





void printFlow(){
    
}

// void getPassword(string *password) {
//     char ch;
//     ch = );
//     cout<<"\b ";

//     while (ch!='\n')
//     {
//         password->push_back(ch);
//         cout<<"\b ";
//         ch = );
//     }
    
// }

int printLoginChoice(){ 

    string s[] = {"1 : New User","2 : Login as Admin","3 : Login as Customer","4 : Login as Vendor","5 : Exit Store"};
    return displayBox(s,5);

}

int printUserChoice(){
    string s[] = {"1: Register as Customer","2: Register as Vendor","3: Go to start menu"};
    return displayBox(s,3);
}


void getDetails(string &username,string &password,unsigned long long& hashPassword,string &rePassword,
    string &accountNumber,Address &address,Type& type,int wish){
    
        clear();
        char t[100]; 
        EnterNewUserName : 
        // char username[100];

        clear();
        char in[] = "Enter your User Name(without space) : ";
        displayWindow(in,t);
        username = string(t); 
       
        // 

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
        if(wish == 1){
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
    printw("Top Search Products:\n");
    for(int i=0;i<v.size();i++){
        printw("     Product: %d\n",i);
        v[i]->displayProduct();
    }

}

int showFuntionality(int n){
    string str[10];
    for(int i=0;i<n;i++){
        str[i] = to_string(i+1)+":Order Product "+to_string(i+1);
    }
    str[n] = to_string(n+1)+":Search products";
    str[n+1] = to_string(n+2)+":Show cart";
    str[n+2] = to_string(n+3)+":Show wallet balance";
    str[n+3] = to_string(n+4)+":Show ordered products";
    str[n+4] = to_string(n+5)+":Logout";
    return displayBox(str,n+5);

}

void displaySearchProduct(vector<Product*> searchedProduct){
    
    clear();
    mvprintw(5,5,"Select the product of your choice");
    
    int i=1;
    for(auto presentProduct : searchedProduct){
        printw("   Product: %d\n",i);
        presentProduct->displayProduct();
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
    return displayBox(in,6);
}

void getProductDetails(string &name,string &type,int &quantity,double &price,string &description){

    char temp[100];

    clear();
    char in[]="Name your product name:";
    displayWindow(in,temp);
    name = string(temp);

    clear();
    char in1[]="Enter your product type:";
    displayWindow(in1,temp);
    type = string(temp);

    clear();
    char in2[]="Enter quantity(must be an integer value):";
    displayWindow(in2,temp);
    quantity = stod(temp);

    clear();
    char in3[]="Enter price(must be decimal value):";
    displayWindow(in3,temp);
    price = stod(temp);

    char check;
    clear();
    char in4[]="Would you liketo add description of your product?Y/N";
    displayWindow(in4,temp);
    check = (temp[0]);

    
    if(check == 'Y' || check == 'y'){
        clear();
        char in7[]="Enter your product one line description :";
        displayWindow(in7,temp);
        description = string(temp);
    }

}

int displayProductAcceptance(){
    
    string a[]={"1:Add to Cart","2:Buy Product","3:Go to Customer Choices"};
    return displayBox(a,3);
}

void getOrderInformation(string &slot,PaymentStatus &status){
    string in[4]; 
    char header[]="Enter the timimgs when you are available to take delivery ";
    in[0]="1:Morning";
    in[1]="2:Afternoon";
    in[2]="3:Evening";
    in[3]="4:Night";
    int time = displayBoxHeader(in,4,header);
    if(time==1)slot = "Morning";
    else if(time==2)slot = "Afternoon";
    else if(time == 3)slot = "Evening";
    else slot = "Night";

    char header2[]="Enter the payment mode";
    string in2[2];
    in2[0]="1:Cash On Delivery";
    in2[1]="2:Wallet Money";
    // status=WALLET;
    int t = displayBoxHeader(in2,2,header2);
    if(t==1)
        status = CASH_ON_DELIVERY;
    else 
        status = WALLET;
}

int cartChoices(){
    string s[2];
    s[0]="1:Order the cart items";
    s[1]="2:Remove from cart";
    return displayBox(s,2);
    // end();
    // end();
}

int displayProductChoice(int n){
    string s[n];
    for(int i=0;i<n;i++){
        s[i] = to_string(i+1)+": Order Product "+to_string(i+1);
    }
    return displayBox(s,n);
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
        
        clear();
        CustomerChoices:

        showTopSearch(topSearch);
        int customerWish = showFuntionality(topSearch.size());
        
        if(customerWish>=1 && customerWish <=(int)(topSearch.size())){
            
            // ProductManager :: searchAndDisplayVendor(topSearch[--customerWish]);
            // int vendorSelection;
            // cin>>vendorSelection;
            // vendorSelection--;
            // Stock* stock = ProductManager :: getStockPointer(topSearch[customerWish],vendorSelection);

            // TopProductAcceptance:

            // int productAcceptance;
            // displayProductAcceptance();
            // cin>>productAcceptance;
                
            // if(productAcceptance == 1){
            //     int quantity;
            //     cout<<"Number of quantity you want to purchase :";
            //     cin>>quantity;
            //     OrderManager :: addToCart(topSearch[customerWish],stock,quantity);
            //     cout<<"Your Product has bee added into cart (:"<<endl;
            //     goto CustomerChoices;
                
            // }else if(productAcceptance == 2){
            //     int quantity;
            //     cout<<"Number of quantity you want to purchase :";
            //     cin>>quantity;    
            //     string deliverySlot;
            //     PaymentStatus paymentStatus;
            //     getOrderInformation(deliverySlot,paymentStatus);
            //     OrderManager :: placeOrder(topSearch[customerWish],stock,quantity,deliverySlot,paymentStatus);
            //     goto CustomerChoices;

            // }else if(productAcceptance == 3){
            //     goto CustomerChoices;
            // }else{
            //     cout<<"You have Entered wrong choice"<<endl;
            //         goto TopProductAcceptance;
            // }
            
                clear();
                ProductManager :: searchAndDisplayVendor(topSearch[--customerWish]);
                // displayVendorList(availableVendors);
                int vendorSelection;
                char c[] = "Enter the Vendor Number:";
                char ven[10];
                displayWindow(c,ven);
                vendorSelection = stod(ven)-1; 

                Stock* stock = ProductManager :: getStockPointer(topSearch[vendorSelection],vendorSelection);
                // cout<<stock->price<<endl;
                ProductAcceptance:

                int productAcceptance = displayProductAcceptance();
                
                
                if(productAcceptance == 1){
                    
                    int quantity;
                    clear();
                    char c[] = "Number of quantity you want to purchase :";
                    char qin[10];
                    displayWindow(c,qin);
                    quantity = stod(qin); 

                    OrderManager :: addToCart(topSearch[vendorSelection],stock,quantity);
                    clear();
                    mvprintw(3,5,"Your Product has bee added into cart");
                    goto CustomerChoices;
                
                }else if(productAcceptance == 2){
                    
                    int quantity;
                    clear();
                    char c[] = "Number of quantity you want to purchase :";
                    char qin[10];
                    displayWindow(c,qin);
                    quantity = stod(qin); 

                    string deliverySlot;
                    PaymentStatus paymentStatus;
                    
                    getOrderInformation(deliverySlot,paymentStatus);

                    // cout<<stock->price<<endl;
                    // cout<<searchProduct[0]->getProductName()<<endl;
                    
                    
                    OrderManager :: placeOrder(topSearch[0],stock,quantity,deliverySlot,paymentStatus);
                    clear();
                    mvprintw(3,5,"Your Product has successfully ordered (:");
                    goto CustomerChoices;
                    
                }else if(productAcceptance == 3){
                    goto CustomerChoices;

                }
             
        }
        else if(customerWish  == (int)(topSearch.size())+1){
            string searchString;
            
            clear();
            char search[100] ;
            char show[] = "Enter about product which you wish to search :";
            displayWindow(show,search);
            searchString = string(search);

            vector<Product*>  searchProduct= ProductManager :: searchProducts(searchString);
            if(searchProduct.size() == 0){
                clear();
                mvprintw(5,5,"Sorry, Presently we don't have the required product.You can search for it afterwards at our store");
                goto CustomerChoices; 
            }
            
            displaySearchProduct(searchProduct);

            
            int productWish = displayProductChoice(searchProduct.size());
                        
            if(productWish >= 1 && productWish <= (int)(searchProduct.size())){
                productWish--;
                
                clear();
                ProductManager :: searchAndDisplayVendor(searchProduct[productWish]);
                // displayVendorList(availableVendors);
                int vendorSelection;
                char c[] = "Enter the Vendoe Number:";
                char ven[10];
                displayWindow(c,ven);
                vendorSelection = stod(ven)-1; 

                Stock* stock = ProductManager :: getStockPointer(searchProduct[productWish],vendorSelection);
                // cout<<stock->price<<endl;
                ProductAcceptance:

                int productAcceptance = displayProductAcceptance();
                
                
                if(productAcceptance == 1){
                    
                    int quantity;
                    clear();
                    char c[] = "Number of quantity you want to purchase :";
                    char qin[10];
                    displayWindow(c,qin);
                    quantity = stod(qin); 

                    OrderManager :: addToCart(searchProduct[productWish],stock,quantity);
                    clear();
                    mvprintw(3,5,"Your Product has bee added into cart");
                    goto CustomerChoices;
                
                }else if(productAcceptance == 2){
                    
                    int quantity;
                    clear();
                    char c[] = "Number of quantity you want to purchase :";
                    char qin[10];
                    displayWindow(c,qin);
                    quantity = stod(qin); 

                    string deliverySlot;
                    PaymentStatus paymentStatus;
                    
                    getOrderInformation(deliverySlot,paymentStatus);

                    // cout<<stock->price<<endl;
                    // cout<<searchProduct[0]->getProductName()<<endl;
                    
                    
                    OrderManager :: placeOrder(searchProduct[0],stock,quantity,deliverySlot,paymentStatus);
                    clear();
                    mvprintw(3,5,"Your Product has successfully ordered (:");
                    goto CustomerChoices;
                    
                }else if(productAcceptance == 3){
                    goto CustomerChoices;

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
            int operation;
            clear();
            mvprintw(1,5,"Your Wallet has %.2lf rupees.",UserManager :: getWalletBalance());
            // cout<<"Your Wallet has "<<UserManager :: getWalletBalance()<<"rupees"<<endl;
            string option[]= {"1:Add Money","2:Extract Money","3:Exit"};
            operation=displayBox(option,3);
            if(operation == 1){
                double amt;
                char c[] = "Enter the amount you want to add: ";
                    char qin[50];
                    displayWindow(c,qin);
                    amt = stod(qin);
                UserManager :: addMoneyFromAccount(amt);
            }
            if(operation == 2){
                double amt;
                char c[] = "Enter the amount you want to extract: ";
                    char qin[50];
                    displayWindow(c,qin);
                    amt = stod(qin);
                UserManager :: addMoneyToAccount(amt);
            }
            clear();
            mvprintw(1,5,"Your Wallet has %.2lf rupees.",UserManager :: getWalletBalance());
            goto CustomerChoices;
        }
        else if(customerWish == (topSearch.size()+4)){
            
            OrderManager :: showCustomerOrder();
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

        int vendorWish = displayVendorChoices();
        
        if(vendorWish == 1){
            string name,type,description;
            int quantity;
            double price;

            getProductDetails(name,type,quantity,price,description);
            ProductManager :: addProduct(name,type,quantity,price,type);
            // if(!(ProductManager :: addProduct(name,type,quantity,price,type))){
            //     cout<<"Sorry something went wrong"<<endl;
            //     cout<<"Try after Sometime to add product"<<endl;
            //     goto VendorChoices;
            // }
            clear();
            mvprintw(5,5,"Your product have been added succesfully (:");
            goto VendorChoices;

        }else if (vendorWish == 2){

            OrderManager :: showVendorOrder();
            goto VendorChoices;

        }
        else if(vendorWish == 3){
            clear();
            mvprintw(5,5,"Your wallet has %d", UserManager :: getWalletBalance());
            goto VendorChoices;

        }else if(vendorWish == 4){

            clear();
            ((Vendor*)(Database :: currentUser))->displayVendorRatings();
            goto VendorChoices;
        
        }
        else if(vendorWish == 5){
           
            clear();
            mvprintw(5,5,"Your wallet has %lf",UserManager :: getWalletBalance());
            
            char temp[100];
            char in[] = "Enter the amount you wish to add to your bank account";
            displayWindow(in,temp);
            double amount = stod(temp);


            if(amount > UserManager :: getWalletBalance()){
                clear();
                mvprintw(5,5,"Sorry you don't have enough balance");
                goto VendorChoices;
            }

            UserManager :: addMoneyToAccount(amount);
            //Last mai dekhege...
            // if((Database :: currentUser)->getWalletBalance()<0){
            //     mvprintw("You don't have enough money in account"
            // }
            clear();
            mvprintw(5,5,"Your wallet has %lf",UserManager :: getWalletBalance());
            goto VendorChoices;

        }
        else if(vendorWish == 6){
            clear();
            goto SignIn;
        
        }

    }
    endwin();
    Database::writeToDatabase();

    // Database :: writeToDatabase<User>(Database::vendors,"user.txt");
    
}