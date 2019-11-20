
enum OrderStatus {ORDERED, DISPATCHED, DELIVERED, CANCELLED};
enum PaymentStatus {CASH_ON_DELIVERY,WALLET};
enum Type {ADMIN,VENDOR,CUSTOMER};

class CartProduct{
  Product *product;
  Stock *stock;
  int quantity;
};

class Product{
  string name;
  string type;
  vector<Stock*> stocks;
  string description;
};

class Stock{
  Vendor* vendor;
  int quantity;
  double price;
};

class Cart{
  vector<CartProduct> cartProducts;
};

class Order{
  OrderStatus status;
  vector<CartProduct> cartProducts;
  string expectedDeliveryDate;
  double cost;
  string deliverySlot;
  PaymentStatus paymentStatus;
};

class Vendor{
  double rating;
  int numberOfRatings;
  string reviews;
};

class Customer : public User{
  Cart cart;
};

class User{
  string username;
  string password;
  Wallet wallet;
  vector<Order*> orders;
  string account;
  string address;
  Type type;
};

class Wallet{
  double balance;
};
