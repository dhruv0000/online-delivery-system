#include"utilities.hpp"

namespace Database {
    vector<Order*> orders;
    vector<Product*> products;
    vector<User*> users;
    User* currentUser;
    User* admin;
    double discount;
    double deliveryCharge;

    template<typename T>
    void writeToDatabase(vector<T*> data, string fname) {
        ofstream fout;
        fout.open(fname);
        for(auto item : data) {
            fout<<item->getDatabaseString();
        }
    }
};
