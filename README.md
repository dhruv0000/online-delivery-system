# online-delivery-system
![System Requirement](https://img.shields.io/badge/g%2B%2B-7.4.0-orange)
![System Requirement](https://img.shields.io/badge/ubuntu-18.04.1-green)
![System Requirement](https://img.shields.io/badge/lib-ncurses-blue)
![System Requirement](https://img.shields.io/badge/language-c%2B%2B-yellow)

An object oriented C++ project, created for university course with _nCurses_ based CLI software to order, track and manage delivery of goods.

### Concepts and Tools Learnt
The project uses the concepts of _classes_, _templates_, _template specialization_, _virtual functions_, _namespaces_, _inheritance_, _file handling_, _password hashing_, _STL components_ ,_friend functions_ and _nCurses Library_.

### Features
- __Menu support in CLI__ (using nCurses)
- __Product Advertisement__
- __Premium Membership__
- __Order Cancellation__
- __Top Products Display__ 
- Search Products
- Cart
- Payment Modes
  * Cash on Delivery
  * Wallet
- Discount
- Database
- Multiple Vendors Support
- Trust Building among Vendors

### Problems Faced
- CLI was initially trivial, but menus and headings were later added to improve UI/UX using the __ncurses library__.
- We tried to host the database online, without success.
- The system was divided into three separate subsystems, visually _User Manager_, _Product Manager_ and _Order Manager_, to improve modularity and readability of the code.
- Exception handling was not implemented from starting which led to the program shutting down ungracefully.
- Tried to include Review and Rating System. were not able to integrate Backend with nCurser front-end.


 
## Running the Code
The code makes use of _ncurses_ library, which is only available in __Linux__ based system currently.

Clone the repository:
```bash
git clone https://github.com/dhruv0000/online-delivery-system
```

Navigate into repository:
``` bash
cd online-delivery-system
```

Run the makefile:
```
start
```


