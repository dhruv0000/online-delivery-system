#include <bits/stdc++.h>
using namespace std;


class UserManager{
public:


};



void printFlow(){
  cout<<"Enter the number corresponding to funtion you wish to perform"<<endl;
}

class Password{
public:
    static bool checkStrength(string passwd){
        int length = passwd;
        int countUpper = 0,countLower = 0,countDigit = 0;
        for(int i=0;i<len;i++){
            if(passwd[i] >= 65 && passwd[i] <= 90)
                countUpper++;
            if(passwd[i] >= 97 && passwd[i] <= 122)
                countLower++;
            if(passwd[i] >= 48 && passwd[i] <= 57)
                countDigit++;
        }
        if(countUpper && countLower && countDigit)
            return false;

        return true;
    }
    static unsigned long hashValue(string passwd){
        hash<string> h;
        return h(passwd);
    }

};

class Address{
private:
    string bulding,street,city,state;

public:
    void storeAddress(){
        cout<<"Enter each details in one line each "<<endl;
        cout<<"Enter your building or appartment : ";
        getline(str,building);
        cout<<"Enter your street : ";
        getline(str,street);
        cout<<"Enter your city : ";
        getline(str,city);
        cout<<"Enter your state : ";
        getline(str,state);
    }

    void display(){
        cout<<"Building/Appartment : "<<bulding<<endl;
        cout<<"Street : "<<street<<endl;
        cout<<"City : "<<city<<endl;
        cout<<"State : "<<state<<endl;
    }
};

int main(){
  int wish;
  cout<<"Welcome to our Online Store"<<endl;
  signIn:
  printFlow();
  cout<<"1 : New User"<<endl;
  cout<<"2 : Login as Admin"<<endl;
  cout<<"3 : Login as Customer"<<endl;
  cout<<"4 : Login as Vendor"<<endl;
  cin>>wish;

//   string username;
//   string password;
  
  switch(wish){
    case 1:
        registration:
        printFlow();
        cout<<"1: Register as Customer"<<endl;
        cout<<"2: Register as Vendor"<<endl;
        cin>>wish;
        string name,password,accountNumberrePassword;
        Address address;

        if(wish == 1){
            cout<<"Enter the following details"<<endl;
            cout<<"Enter your name(without space) : ";
            cin>>name;
        
            do{
                do{
                    cout<<"Enter your password(should contain 6-10 characters,atleast 1 Upper Case,Lower Case and Digit character) : ";
                    cin>>password;

                    if(Password :: checkStrength(password))
                        break;

                    cout<<"Password is not strong enough "<<endl;
        
                }while(true);

                cout<<"Re-Enter your password : ";
                cin>>rePassword;
        
                if(password == rePassword)
                    break;
        
                cout<<"Your password didn't match"<<endl;
        
            }while(true);

            cout<<"Enter your Account number : ";
            cin>>accountNumber;
            address.storeAddress();
            unsigned long hashPassword = Password :: hashValue(string);

        
        }else if(wish == 2){

        }else{
            cout<<"You have entered wrong wish"<<endl;
            goto registration;
        }

    case 2:
        cout<<"Enter your username (without spaces):";
        cin>>username;
        cout<<"Enter your password:";
        cin>>password;
        if(username == Database :: admin->username && Database :: password == admin->password){
        
        }else{
            cout<<"You have entered wrong wish"<<endl;
        }
    
    case 3:
    
    case 4:
    
    default:
        cout<<"You have entered wrong choice"<<endl;
        goto signIn;
  }
}
