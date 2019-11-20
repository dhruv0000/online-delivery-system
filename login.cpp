#include <bits/stdc++.h>

using namespace std;

void printFlow(){
  cout<<"Enter the number corresponding to funtion you wish to perform"<<endl;
}

int main(){
  int wish;
  cout<<"Welcome to our Online Store"<<endl;
  error:
  printFlow();
  cout<<"1 : New User"<<endl;
  cout<<"2 : Login as Admin"<<endl;
  cout<<"3 : Login as Customer"<<endl;
  cout<<"4 : Login as Vendor"<<endl;
  cin>>wish;

  string username;
  string password;
  
  switch(wish){
    case 1:
      
    
    case 2:
      cout<<"Enter your username (without spaces):";
      cin>>username;
      cout<<"Enter your password:";
      cin>>password;
      if(username == Database :: admin->username && Database :: password == admin->password){
        
      }else{
        cout<<"You have entered wrong password"<<endl;
        
      }
    
    case 3:
    
    case 4:
    
    default:
      cout<<"You have entered wrong choice"<<endl;
      goto error;
  }
}
