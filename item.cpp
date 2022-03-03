#include "item.hpp"
const int tax=0.6;

Item::Item(){}

Item::Item(string product_name, int quantity,
             int mDay, int mMonth, int mYear,
             int eDay, int eMonth, int eYear,
             float cost, int margin)
             //initialization list
    : product_name(product_name), quantity(quantity),
        mDay(mDay), mMonth(mMonth), mYear(mYear),
        eDay(eDay), eMonth(eMonth), eYear(eYear),
        margin(margin),  cost(cost)
    { };

int Item::counter = 0;

void Item::setProduct_num(){
    product_num = 1001 + counter; //initial num 1001
}

void Item::setProduct_num(int product_num){
    this->product_num=product_num;
}

void Item::setProduct_name(string product_name){
    for(unsigned i = 0; i < product_name.length(); i++)
    {
        product_name[i] = toupper(product_name[i]);
    }

    this->product_name = product_name;
}

void Item::setQuantity(int quantity){
    this->quantity = quantity;
}

void Item::setmDate(int mDay, int mMonth, int mYear){
    this->mDay = mDay;
    this->mMonth = mMonth;
    this->mYear = mYear;
}

void Item::seteDate(int eDay, int eMonth, int eYear){
    this->eDay = eDay;
    this->eMonth = eMonth;
    this->eYear = eYear;
}

void Item::setCost(float cost){
    this->cost = cost;
}

void Item::setMargin(float margin){
    this->margin = margin;
}

void Item::setPrice(){
    price = (cost/(1-margin/100))*(1+tax);
}

void Item::setPrice(float price){
    this->price=price;
}

int     Item::getProduct_num()const{return product_num;}
string  Item::getProduct_name()const{return product_name;}
int     Item::getQuantity()const{return quantity;}
float   Item::getCost()const{return cost;}
float   Item::getPrice()const{return price;}
float   Item::getMargin()const{return margin;}
int     Item::getMDay()const{return mDay;}
int     Item::getMMonth()const{return mMonth;}
int     Item::getMYear()const{return mYear;}
int     Item::getEDay()const{return eDay;}
int     Item::getEMonth()const{return eMonth;}
int     Item::getEYear()const{return eYear;}
