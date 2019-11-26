#include <bits/stdc++.h>
using namespace std;

bool compareCharIgnoreCase(char & c1, char & c2)
{
  if (c1 == c2||c1 == std::toupper(c2)||std::toupper(c1)==c2||std::toupper(c1) == std::toupper(c2))
    return true;
  return false;
}
 
bool compareStringIgnoreCase(std::string & str1, std::string &str2)
{
  return ( (str1.size() == str2.size() ) &&
       std::equal(str1.begin(), str1.end(), str2.begin(), &compareCharIgnoreCase) );
}

int main() {
    string a;
string b;
cin>>a;
cin>>b;
cout<<compareStringIgnoreCase(a,b);
}