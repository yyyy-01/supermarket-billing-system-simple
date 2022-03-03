#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
#include <vector>
#include <iostream>
using namespace std;

class Item
{
    private:
        int product_num, quantity, mDay, mMonth, mYear, eDay, eMonth, eYear;
        string product_name;
        float cost, margin, price;

    public:
        Item();
        Item(string product_name, int quantity,
             int mDay, int mMonth, int mYear,
             int eDay, int eMonth, int eYear,
             float cost, int margin);

        static int counter;

    void setProduct_num();
    void setProduct_num(int product_num);
    void setProduct_name(string name);
    void setQuantity(int num);
    void setmDate(int mDay, int mMonth, int mYear);
    void seteDate(int eDay, int eMonth, int eYear);
    void setCost(float cost);
    void setPrice();
    void setPrice(float price);
    void setMargin(float margin);

    int getProduct_num()const;
    string getProduct_name()const;
    float getMargin()const;
    int getQuantity() const;
    float getCost()const;
    float getPrice()const;
    int getMDay()const;
    int getMMonth()const;
    int getMYear()const;
    int getEDay()const;
    int getEMonth()const;
    int getEYear()const;

};

#endif // ITEM_H_INCLUDED
