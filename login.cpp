#include <bits/stdc++.h>
#include "managers.hpp"

using namespace std;

void printFlow(){
  cout<<"Enter the number corresponding to funtion you wish to perform"<<endl;
}

void printLoginChoice(){
    printFlow();
    cout<<"1 : New User"<<endl;
    cout<<"2 : Login as Admin"<<endl;
    cout<<"3 : Login as Customer"<<endl;
    cout<<"4 : Login as Vendor"<<endl;
    // cout<<"5 : Exit Store"<<endl;
}
void printUserChoice(){
    printFlow();
    cout<<"1: Register as Customer"<<endl;
    cout<<"2: Register as Vendor"<<endl;
}

void getDetails(string& username,string& password,unsigned long long& hashPassword,string& rePassword,
    string& accountNumber,Address& address,Type& type,int wish){
    EnterNewUserName : 
            
        cout<<"Enter the following details"<<endl;
        cout<<"Enter your User Name(without space) : ";
        std :: cin>>username;
                
        if(!(UserManager :: checkUserNameAvailable(username))){
            cout<<"This User Name already exists"<<endl;
            goto EnterNewUserName;
        }

        do{
            do{
                cout<<"Enter your Password(should contain 6-10 characters,atleast 1 Upper Case,Lower Case and Digit character) : ";
                std :: cin>>password;

                if(Password :: checkStrength(password))
                    break;

                cout<<"Password is not strong enough "<<endl;
            
                }while(true);

                cout<<"Re-Enter your Password : ";
                std :: cin>>rePassword;
            
                if(password == rePassword)
                    break;
            
                cout<<"Your Password didn't match"<<endl;
            
        }while(true);

        cout<<"Enter your Account Number : ";
        std :: cin>>accountNumber;
        address.storeAddress();
        hashPassword = Password :: hashValue(password);
        if(wish == 1){
            type = CUSTOMER;
        }else{
             type = VENDOR;
        }
        
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
    for(int i=0;i<v.size();i++){
        cout<<i+1<<endl;
        v[i]->displayProduct();
    }
}

void showFuntionality(int i){
    cout<<i+1<<":Search products"<<endl;
    cout<<i+2<<":Show cart"<<endl;
    cout<<i+3<<":Logout"<<endl;
}

int main(){
   
    int wish;
    cout<<"Welcome to our Online Store"<<endl;
    
    SignIn: 
    printLoginChoice();
    std :: cin>>wish;


    if(wish == 1) {
        
        Registration:
        printUserChoice();
        std :: cin>>wish;
        
        string username,password,accountNumber,rePassword;
        unsigned long long hashPassword;
        Address address;
        Type type;

        if(wish == 1 || wish == 2){
            getDetails(username,password,hashPassword,rePassword,accountNumber,address,type,wish);
        }else{
            cout<<"You have entered wrong wish"<<endl;
            goto Registration;
        }

        if(UserManager :: registerUser(username, hashPassword, accountNumber, address, type)){
            cout<<"You have successfully created new account"<<endl;
            cout<<"Please login into Account "<<endl;
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
            int adminWish;
            std :: cin>>adminWish;
            if(adminWish == 1)setDeliveryCharges();
            else if(adminWish == 2)setDiscountPercentage();
            else if(adminWish == 3)UserManager :: logoutUser();
            else{
                 cout<<"Admin Please enter correct choice"<<endl;
                 goto AdminRun;
            }

        }else{
            cout<<"You have entered wrong password"<<endl;
            goto SignIn;
        }
        
    }

    else if(wish == 3){
       
        string username,password;
        unsigned long long hashValue;

        getUserDetails(username,password,hashValue);

        if(!UserManager::loginUser(username,hashValue)){
            cout<<"You have entered wrong username or password"<<endl;
            goto SignIn;
        }

        cout<<"You are Logged In successsfully (:"<<endl;

        if((Database :: currentUser)->getType() == CUSTOMER){
            int count;
            cout<<"Enter the number of top purchased product you we to see"<<endl;
            std :: cin>>count;
            vector<Product*> topSearch = ProductManager :: getTopProducts(count);
                //Show Top Product has some Issues of how to get the top product address???
            int customerWish;

            UserChoices:

            printFlow();
            showFuntionality(topSearch.size());
            showTopSearch(topSearch);
            std :: cin>>customerWish;

            if(customerWish<1 || customerWish>(topSearch.size()+3)){
                cout<<"User please enter correct";
            }


        }
        else{
            
        }

       

    }
    // else if (wish == 4) {
    // }

    // else {
    //     cout<<"You have entered wrong choice"<<endl;
    //     goto SignIn;
    // }
}
