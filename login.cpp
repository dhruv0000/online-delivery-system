#include <bits/stdc++.h>
#include "header/managers.hpp"

using namespace std;

void printFlow(){
  cout<<"Enter the number corresponding to funtion you wish to perform"<<endl;
}

int main(){
    int wish;
    cout<<"Welcome to our Online Store"<<endl;
    SignIn:
    printFlow();
    cout<<"1 : New User"<<endl;
    cout<<"2 : Login as Admin"<<endl;
    cout<<"3 : Login as Customer"<<endl;
    cout<<"4 : Login as Vendor"<<endl;
    cin>>wish;

  
    if(wish == 1) {
        
        Registration:
        
        printFlow();
        cout<<"1: Register as Customer"<<endl;
        cout<<"2: Register as Vendor"<<endl;
        cin>>wish;
        
        string username,password,accountNumber,rePassword;
        unsigned long long hashPassword;
        Address address;
        Type type;

        if(wish == 1 || wish == 2){
            EnterNewUserName : 
            
            cout<<"Enter the following details"<<endl;
            cout<<"Enter your User Name(without space) : ";
            cin>>username;
            
            if(!(UserManager :: checkUserNameAvailable(username))){
                cout<<"This User Name already exists"<<endl;
                goto EnterNewUserName;
            }

            do{
                do{
                    cout<<"Enter your Password(should contain 6-10 characters,atleast 1 Upper Case,Lower Case and Digit character) : ";
                    cin>>password;

                    if(Password :: checkStrength(password))
                        break;

                    cout<<"Password is not strong enough "<<endl;
        
                }while(true);

                cout<<"Re-Enter your Password : ";
                cin>>rePassword;
        
                if(password == rePassword)
                    break;
        
                cout<<"Your Password didn't match"<<endl;
        
            }while(true);

            cout<<"Enter your Account Number : ";
            cin>>accountNumber;
            address.storeAddress();
            hashPassword = Password :: hashValue(password);
            if(wish == 1){
                type = CUSTOMER;
            }else{
                type = VENDOR;
            }
        
        }else{
            cout<<"You have entered wrong wish"<<endl;
            goto Registration;
        }

        if(UserManager :: registerUser(username, hashPassword, accountNumber, address, type)){
            cout<<"You have successfully created new account"<<endl;
            cout<<"Please login into Account "<<endl;
            goto SignIn;
        }
        
    } else if(wish == 2) {
        string username,password;
        IncorrectPassword :

        cout<<"Enter your username (without spaces):";
        cin>>username;
        cout<<"Enter your password:";
        cin>>password;
        unsigned long long hashValue = (Password :: hashValue(password));
        // if((username == Database :: admin->getUsername()) &&  hashValue == (Database :: admin->password)){
                
        // }else{
            if(!UserManager::loginUser(username,hashValue)){
                cout<<"You have entered wrong user name or password : "<<endl;
                goto IncorrectPassword;
            }
            cout<<"You are Logged In successsfully (:"<<endl;
            if((Database :: currentUser)->getType() == 1){

            }
            else{
                int count;
                cout<<"Enter the number of top purchased product you we to see"<<endl;
                cin>>count;
                ProductManager :: showTopProducts(count);
                //Show Top Product has some Issues of how to get the top product address???
                
                printFlow();
                cout<<"1 :";

            }

        // }
        
    }

    // else if(wish == 3) {
    // }
    // else if (wish == 4) {
    // }

    // else {
    //     cout<<"You have entered wrong choice"<<endl;
    //     goto SignIn;
    // }
}

