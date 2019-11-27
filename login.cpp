#include "header/managers.hpp"
// #include <conio.h>

using namespace std;

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
    cout<<"1 : New User"<<endl;
    cout<<"2 : Login as Admin"<<endl;
    cout<<"3 : Login as Customer"<<endl;
    cout<<"4 : Login as Vendor"<<endl;
    cout<<"5 : Exit Store"<<endl;
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
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<Database :: currentUser -> getUsername()<<endl;
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
        cout<<"Product "<<i+1<<endl;
        v[i]->displayProduct();
    }
}

void showFuntionality(int i){
    cout<<i+1<<":Search products"<<endl;
    cout<<i+2<<":Show cart"<<endl;
    cout<<i+3<<":Show wallet balance"<<endl;
    cout<<i+4<<":Logout"<<endl;
}

void displaySearchProduct(vector<Product*> searchedProduct){
    cout<<"Enter the number of the product which you are liking"<<endl;
    int i=0;
    for(auto presentProduct : searchedProduct){
        cout<<i<<endl;
        presentProduct->displayProduct();
        i++;
    }
}

void displayVendorChoices(){
    printFlow();
    cout<<"1:Add Product to our Shop"<<endl;
    cout<<"2:Show Pending Orders"<<endl;
    cout<<"3:Show Wallet Balance"<<endl;
    cout<<"4:See Reviews and Ratings"<<endl;
    cout<<"5:Logout"<<endl;
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
    printFlow();
    cout<<"1:Add to Cart"<<endl;
    cout<<"2:Buy Product"<<endl;
}

int main(){
   
    char wish;
    cout<<"Welcome to our Online Store"<<endl;
    
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
            cout<<endl;
            cout<<"You have successfully created new account (:"<<endl;
            if(type == CUSTOMER)
                cout<<"Please login into your account to purchase our products"<<endl;
            else
                cout<<"Please login into your account to do business with us"<<endl;
            cout<<endl;
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
            else if(adminWish == '3')UserManager :: logoutUser();
            else{
                 cout<<"Admin Please enter correct choice"<<endl;
                 goto AdminRun;
            }

        }else{
            cout<<"You have entered wrong password"<<endl;
            goto SignIn;
        }
        
    }
    else if(wish == '3'){
       
        string username,password;
        unsigned long long hashValue;

        getUserDetails(username,password,hashValue);

        if(!UserManager::loginUser(username,hashValue)){
            cout<<"\nYou have entered wrong username or password\n\n";
            goto SignIn;
        }
        
        if((Database :: currentUser)->getType() != CUSTOMER){
            cout<<"\nOops you are not CUSTOMER\n";
            cout<<"Please select proper category\n"<<endl;
            goto SignIn;
        }

        cout<<"You are Logged In successsfully (:"<<endl;
        displayUsername();
        int count;
        cout<<"Enter the number of top purchased product you want to see"<<endl;
        std :: cin>>count;
            
        vector<Product*> topSearch = ProductManager :: getTopProducts(count);
        char customerWish;

        CustomerChoices:

        printFlow();
        showTopSearch(topSearch);
        showFuntionality(topSearch.size());
        std :: cin>>customerWish;

        if((customerWish - '0') == topSearch.size()+1){
            string searchString;
            cout<<"Enter about product which you wish to search :";
            cin>>searchString;
            vector<Product*>  searchProduct= ProductManager :: searchProducts(searchString);

            if(searchProduct.size() == 0){
                cout<<"\nSorry, Presently we don't have the required product.You can search for it afterwards at our store\n\n";
                goto CustomerChoices; 
            }

            char productWish;
            SearchProductDisplay:
            displaySearchProduct(searchProduct);
            cin>>productWish;
            
            //For user not to enter random numbers , isko lite lo 
            //if(productWish<1 ||productWish>searchProduct.size()){
            //     cout<<"\nMatch not found\n\n";
            //     goto SearchProductDisplay;
            // }
            if(productWish >= '1' && productWish <= (char)(searchProduct.size()+(int)'0')){
                int productNumber;
                displayProductAcceptance();
                cin>>productNumber;
            }


        }


        
        else{
            
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

            if(!(ProductManager :: addProduct(name,type,quantity,price,type))){
                cout<<"Sorry something went wrong"<<endl;
                cout<<"Try after Sometime to add product"<<endl;
                goto VendorChoices;
            }
            cout<<"Your product have been added succesfully (:"<<endl;
            goto VendorChoices;

        }else if(vendorWish == '5')
            goto SignIn;

    }
    else if (wish != '5'){
        cout<<"You have entered wrong choice"<<endl;
        goto SignIn;
    }

    Database :: writeToDatabase<Product>(Database::products,"products.txt");
    Database :: writeToDatabase<User>(Database::users,"users.txt");
    // Database :: writeToDatabase<User>(Database::vendors,"user.txt");
    
}