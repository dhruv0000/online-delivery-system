#include <iostream>
#include <string>

#include <boost/asio.hpp>
int main()
{
    // boost::asio::ip::tcp::iostream s("raw.githubusercontent.com", "https");
    // if(!s)
    //     std::cout << "Could not connect to www.a.com\n";
    // s  << "GET /dhruv0000/online-delivery-system/master/products.txt HTTPS/1.0\r\n"
    //    << "Host: raw.githubusercontent.com\r\n"
    //    << "Accept: */*\r\n"
    //    << "Connection: close\r\n\r\n" ;
    // for(std::string line; getline(s, line); )
    //      std::cout << line << '\n';
    system("curl https://raw.githubusercontent.com/dhruv0000/online-delivery-system/master/products.txt --output my.file");
}