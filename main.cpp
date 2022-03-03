#include <iostream>
#include <iomanip> //setprecision, setw
#include <stack>
#include <queue>
#include <vector>
#include <climits>//INT_MAX
#include <string>//stoi, stof
#include <algorithm> //sort
#include <fstream> //file handling
//#include <limits.h> //exception handling
#include <stdlib.h> //system pause
#include "item.hpp"
#include "date.h"

using namespace std;

vector<Item> item_record;
vector<Item> deleted_item;
Item t;

int num, day, month, year;
float floatnum;
string name;
char ch;
int index;//for delete and edit

/*------implementation--------*/
//function for all
bool check_product_num(int num);//find index to del or edit

//1. add
void addItem();
//2. delete
void delItem();
//3. sort
void sortMenu();
void sortbyName();
void sortbyQuantity();
void sortbyCost();
void sortbyPrice();
void sortbyMargin();
void displaySort(queue<Item> q);
//4. display
void displayMenu();
void displayCurrent();
void displayDeleted();
//5. search
void searchMenu();
void searchbyPnum(int num);
void binarySearch(vector <Item> a, unsigned l, unsigned r, int num, bool& found, unsigned& i);
void searchbyName(string name);
void searchbyAlpha(char ch);
void displaySearch(stack<Item> s);
//6. edit
void edit();
void editMenu();
void displayEdit();

void writeFile(){
    ofstream fileOut;
    fileOut.open("item_record.csv");
    fileOut<<"Product Num, Product Name, Quantity, Manufacture date, Expiring Date, Cost, Price, Margin" <<endl;
    for(unsigned i=0; i<item_record.size(); i++)
    fileOut<<item_record[i].getProduct_num()<<","
            <<item_record[i].getProduct_name()<<","
            <<item_record[i].getQuantity()<<","
            <<item_record[i].getMDay()<<"/"<<item_record[i].getMMonth()<<"/"<<item_record[i].getMYear()<<","
            <<item_record[i].getEDay()<<"/"<<item_record[i].getEMonth()<<"/"<<item_record[i].getEYear()<<","
            <<item_record[i].getCost()<<","
            <<item_record[i].getPrice()<<","
            <<item_record[i].getMargin()<<endl;
    fileOut.close();

    fileOut.open("deleted_item.csv");
    fileOut<<"Product Num, Product Name, Quantity, Manufacture Date, Expiring Date, Cost, Price, Margin" <<endl;
    for(unsigned i=0; i<deleted_item.size(); i++)
    fileOut<<deleted_item[i].getProduct_num()<<","
            <<deleted_item[i].getProduct_name()<<","
            <<deleted_item[i].getQuantity()<<","
            <<deleted_item[i].getMDay()<<"/"<<deleted_item[i].getMMonth()<<"/"<<deleted_item[i].getMYear()<<","
            <<deleted_item[i].getEDay()<<"/"<<deleted_item[i].getEMonth()<<"/"<<deleted_item[i].getEYear()<<","
            <<deleted_item[i].getCost()<<","
            <<deleted_item[i].getPrice()<<","
            <<deleted_item[i].getMargin()<<endl;
    fileOut.close();
}

void readFile(){
    ifstream fileIn;
    fileIn.open("item_record.csv");

    if (fileIn.is_open()){
        fileIn.ignore(INT_MAX,'\n');

        string s,d,m,y;
        while(fileIn.peek()!=EOF){

            getline(fileIn, s, ',');
            t.setProduct_num(stoi(s));

            getline(fileIn,name,',');
            t.setProduct_name(name);

            getline(fileIn, s, ',');
            t.setQuantity(stoi(s));

            getline(fileIn, d, '/');
            getline(fileIn, m, '/');
            getline(fileIn, y, ',');
            t.setmDate(stoi(d),stoi(m),stoi(y));

            getline(fileIn, d, '/');
            getline(fileIn, m, '/');
            getline(fileIn, y, ',');
            t.seteDate(stoi(d),stoi(m),stoi(y));

            getline(fileIn, s, ',');
            t.setCost(stof(s));

            getline(fileIn, s, ',');
            t.setPrice(stof(s));

            getline(fileIn, s, '\n');
            t.setMargin(stof(s));

            item_record.push_back(t);
            Item::counter++;
            }

        fileIn.close();
    }

    fileIn.open("deleted_item.csv");

    if (fileIn.is_open()){
        fileIn.ignore(INT_MAX,'\n');

        string s,d,m,y;
        while(fileIn.peek()!=EOF){

            getline(fileIn, s, ',');
            t.setProduct_num(stoi(s));

            getline(fileIn,name,',');
            t.setProduct_name(name);

            getline(fileIn, s, ',');
            t.setQuantity(stoi(s));

            getline(fileIn, d, '/');
            getline(fileIn, m, '/');
            getline(fileIn, y, ',');
            t.setmDate(stoi(d),stoi(m),stoi(y));

            getline(fileIn, d, '/');
            getline(fileIn, m, '/');
            getline(fileIn, y, ',');
            t.seteDate(stoi(d),stoi(m),stoi(y));

            getline(fileIn, s, ',');
            t.setCost(stof(s));

            getline(fileIn, s, ',');
            t.setPrice(stof(s));

            getline(fileIn, s, '\n');
            t.setMargin(stof(s));

            deleted_item.push_back(t);
            Item::counter++;
            }

        fileIn.close();
    }
}

/*--------definition--------*/
bool check_product_num(int num){//to find index of product to del or edit
    for(unsigned i = 0; i < item_record.size(); i++)
    {
        if(num == item_record[i].getProduct_num())
        {
            index = i;
            return true;
        }
    }
    return false;
}

//1.add
void addItem(){
    system("cls");
    cout<<"Please enter the information of the new product"<<endl;
    //name
    cout<<"Name                         : ";
    cin.ignore();
    getline(cin,name);
    t.setProduct_name(name);
    //quantity
    cout<<"Quantity                     : ";
    cin>>num;
    while(cin.fail())
    {
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>num;
    }
    t.setQuantity(num);
    //manufacture date
    cout<<"Manufacture date (DD MM YYYY): ";
    cin>>day>>month>>year;
    while(cin.fail()||!validDate(day,month,year)||!check_manufacture_date(day, month, year))
    {
        if(cin.fail()){
            cout<<"Only number is allowed"<<endl;
            cout<<"->";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else if(!validDate(day,month,year)){
            cout<<"Invalid date! Please reenter."<<endl;
            cout<<"->";
            cin.clear();
        }
        else{
            cout<<"Manufacture date cannot be at the future"<<endl;
            cout<<"->";
            cin.clear();
        }
        cin>>day>>month>>year;
    }
    t.setmDate(day,month,year);
    //expired date
    cout<<"Expired date (DD MM YYYY)    : ";
    cin>>day>>month>>year;
    while(cin.fail()||!validDate(day,month,year)||!check_expired_date(day, month, year))
    {
        if(cin.fail()){
            cout<<"Only number is allowed"<<endl;
            cout<<"->";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else if(!validDate(day,month,year)){
            cout<<"Invalid date! Please reenter."<<endl;
            cout<<"->";
            cin.clear();
        }
        else{
            cout<<"Manufacture date cannot be at the past"<<endl;
            cout<<"->";
            cin.clear();
        }
        cin>>day>>month>>year;
    }
    t.seteDate(day,month,year);
    //cost
    cout<<"Cost (per unit)              : RM ";
    cin>>floatnum;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>floatnum;
    }
    t.setCost(floatnum);
    //margin
    cout<<"Margin (%)                   : ";
    cin>>floatnum;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>floatnum;
    }
    t.setMargin(floatnum);
    //confirmation
    cout<<endl<<"Are you confirm the informations are correct? (y/n) : ";
    cin>>ch;
    if(ch=='y'|| ch=='Y'){
        t.setProduct_num();
        t.setPrice();
        item_record.push_back(t);
        Item::counter++;
        cout<<"New product '"<<t.getProduct_name()<<"' added."<<endl;
    }else{
        cout<<"No new product added."<<endl;

    }
    cout<<endl;
    cout<<"< Enter anykey to continue adding >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        addItem();
    }
}

//2. delete
void delItem(){
    system("cls");
    displayCurrent();
    cout<<"Enter product number to delete : ";
    cin>>num;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>num;
    }
    if(!check_product_num(num)){
        cout<<"No product with product number "<<num<<" found."<<endl;
    }else{
        cout<<"Product with product number "<<num<<" chosen."<<endl;
        cout<<"Are you sure to delete? (y/n) :";
        cin>>ch;
        if(ch=='y'||ch=='Y'){
            deleted_item.push_back(item_record[index]);
            item_record.erase(item_record.begin()+index);
            cout<<"Product with product number "<<num<<" deleted."<<endl;;
        }
    }

    cout<<endl;
    cout<<"< Enter anykey to continue deleting >"<<endl;
    cout<<"< Enter '0' go back to Main Menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        delItem();
    }
}

//3. sort
void sortMenu(){
    system("cls");
    int sort_choice;
    cout<<"_____SORT MENU_____"<<endl;
    cout<<"1. sort by product number"<<endl;
    cout<<"2. sort by name"<<endl;
    cout<<"3. sort by quantity"<<endl;
    cout<<"4. sort by cost"<<endl;
    cout<<"5. sort by price"<<endl;
    cout<<"6. sort by margin"<<endl;
    cout<<"->";
    cin>>sort_choice;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>sort_choice;
    }
    switch (sort_choice)
    {
    case 1:
        displayCurrent();
        break;
    case 2:
        sortbyName();
        break;
    case 3:
        sortbyQuantity();
        break;
    case 4:
        sortbyCost();
        break;
    case 5:
        sortbyPrice();
        break;
    case 6:
        sortbyMargin();
        break;
    default:
        cout<<"Wrong input"<<endl;
        break;
    }

    cout<<endl;
    cout<<"< Enter anykey to continue searching >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        sortMenu();
    }

}

void swap(Item& x, Item& y){
   Item temp = x;
   x = y;
   y = temp;
}
void sortbyName(){
    // bubble sort
    Item arr[item_record.size()];
    for(unsigned i=0; i<item_record.size();i++){
        arr[i]=item_record[i];
    }
    int n=item_record.size();

    while(n>1){
        bool swapped = false;

        for(int i=0; i<n-1; i++){
            if(arr[i].getProduct_name()>arr[i+1].getProduct_name()){
                swap(arr[i], arr[i+1]);
                swapped = true;
                cout<<endl;
            }
        }
        if (!swapped)
            n=0;
        n--;
    }

    //temporary display
    queue<Item> result;
    for (unsigned i = 0; i < item_record.size(); ++i)//copy vector into queue
	{
		result.push(arr[i]);
	}

    displaySort(result);
}
void sortbyQuantity(){
    vector<Item> temp;
    for (unsigned i = 0; i < item_record.size(); ++i)//copy vector into vector temp
	{
		temp.push_back(item_record[i]);
	}

	sort(temp.begin(), temp.end(),
		[](const Item& lhs, const Item& rhs)
		{ return lhs.getQuantity() < rhs.getQuantity(); }
	);

    queue<Item> result;
    for (unsigned i = 0; i < temp.size(); ++i)//copy vector into queue
	{
		result.push(temp[i]);
	}
    displaySort(result);
}
void sortbyCost(){
    vector<Item> temp;
    for (unsigned i = 0; i < item_record.size(); ++i)//copy vector into vector temp
	{
		temp.push_back(item_record[i]);
	}

	sort(temp.begin(), temp.end(),
		[](const Item& lhs, const Item& rhs)
		{ return lhs.getCost() < rhs.getCost(); }
	);

    queue<Item> result;
    for (unsigned i = 0; i < temp.size(); ++i)//copy vector into queue
	{
		result.push(temp[i]);
	}
    displaySort(result);
}
void sortbyPrice(){
    vector<Item> temp;
    for (unsigned i = 0; i < item_record.size(); ++i)//copy vector into vector temp
	{
		temp.push_back(item_record[i]);
	}

	sort(temp.begin(), temp.end(),
		[](const Item& lhs, const Item& rhs)
		{ return lhs.getPrice() < rhs.getPrice(); }
	);

    queue<Item> result;
    for (unsigned i = 0; i < temp.size(); ++i)//copy vector into queue
	{
		result.push(temp[i]);
	}
    displaySort(result);
}
void sortbyMargin(){
    vector<Item> temp;
    for (unsigned i = 0; i < item_record.size(); ++i)//copy vector into vector temp
	{
		temp.push_back(item_record[i]);
	}

	sort(temp.begin(), temp.end(),
		[](const Item& lhs, const Item& rhs)
		{ return lhs.getMargin() < rhs.getMargin(); }
	);

    queue<Item> result;
    for (unsigned i = 0; i < temp.size(); ++i)//copy vector into queue
	{
		result.push(temp[i]);
	}
    displaySort(result);
}
void displaySort(queue<Item> q){
    system("cls");
    cout<<"Products sorted"<<endl<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | Product  | Name                   | Quantity | Manufacture  | Expiring     | Cost       | Price      | Margin    |"<<endl;
    cout<<" | number   |                        |          | date         | date         | (RM)       | (RM)       |           |"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    while(!q.empty()){
    cout<<" | "<<setw(8)<<left<<q.front().getProduct_num()
        <<" | "<<setw(22)<<left<<q.front().getProduct_name()
        <<" | "<<setw(8)<<left<<q.front().getQuantity()
        <<" | "<<setw(3)<<internal<<q.front().getMDay()<<"/"<<q.front().getMMonth()<<"/"<<q.front().getMYear()
        <<"  | "<<setw(3)<<internal<<q.front().getEDay()<<"/"<<q.front().getEMonth()<<"/"<<q.front().getEYear()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<q.front().getCost()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<q.front().getPrice()
        <<"  | "<<setw(6)<<right<<fixed<<setprecision(1)<<q.front().getMargin()<<" %"<<"  | "<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    q.pop();
    }
    cout<<endl;
}

//4.display
void displayMenu(){
    system("cls");
    int display_choice;
    cout<<"_____DISPLAY MENU_____"<<endl;
    cout<<"1. display current"<<endl;
    cout<<"2. display deleted item"<<endl;
    cout<<"->";
    cin>>display_choice;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>display_choice;
    }
    switch (display_choice)
    {
    case 1:
        displayCurrent();
        break;
    case 2:
        displayDeleted();
        break;
    default:
        cout<<"Wrong input"<<endl;
        break;
    }

    cout<<endl;
    cout<<"< Enter anykey to continue display >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        displayMenu();
    }
}
void displayCurrent(){
    system("cls");
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | Product  | Name                   | Quantity | Manufacture  | Expiring     | Cost       | Price      | Margin    |"<<endl;
    cout<<" | number   |                        |          | date         | date         | (RM)       | (RM)       |           |"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    for (unsigned i=0; i<item_record.size(); ++i){
    cout<<" | "<<setw(8)<<left<<item_record[i].getProduct_num()
        <<" | "<<setw(22)<<left<<item_record[i].getProduct_name()
        <<" | "<<setw(8)<<left<<item_record[i].getQuantity()
        <<" | "<<setw(3)<<internal<<item_record[i].getMDay()
                <<"/"<<setw(2)<<item_record[i].getMMonth()
                <<"/"<<setw(4)<<item_record[i].getMYear()
        <<"  | "<<setw(3)<<internal<<item_record[i].getEDay()
                <<"/"<<setw(2)<<item_record[i].getEMonth()
                <<"/"<<setw(4)<<item_record[i].getEYear()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<item_record[i].getCost()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<item_record[i].getPrice()
        <<"  | "<<setw(6)<<right<<fixed<<setprecision(1)<<item_record[i].getMargin()<<" %"<<"  | "<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    }
    cout<<endl;
}
void displayDeleted(){
    system("cls");
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | Product  | Name                   | Quantity | Manufacture  | Expiring     | Cost       | Price      | Margin    |"<<endl;
    cout<<" | number   |                        |          | date         | date         | (RM)       | (RM)       |           |"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    for (unsigned i=0; i<deleted_item.size(); ++i){
    cout<<" | "<<setw(8)<<left<<deleted_item[i].getProduct_num()
        <<" | "<<setw(22)<<left<<deleted_item[i].getProduct_name()
        <<" | "<<setw(8)<<left<<deleted_item[i].getQuantity()
        <<" | "<<setw(3)<<internal<<deleted_item[i].getMDay()
                <<"/"<<setw(2)<<deleted_item[i].getMMonth()
                <<"/"<<setw(4)<<deleted_item[i].getMYear()
        <<"  | "<<setw(3)<<internal<<deleted_item[i].getEDay()
                <<"/"<<setw(2)<<deleted_item[i].getEMonth()
                <<"/"<<setw(4)<<deleted_item[i].getEYear()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<deleted_item[i].getCost()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<deleted_item[i].getPrice()
        <<"  | "<<setw(6)<<right<<fixed<<setprecision(1)<<deleted_item[i].getMargin()<<" %"<<"  | "<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    }
    cout<<endl;
}

//5.search
void searchMenu(){
    system("cls");
    int search_choice;
    cout<<"_____SEARCH MENU_____"<<endl;
    cout<<"1. Search by product number"<<endl;
    cout<<"2. Search by name"<<endl;
    cout<<"3. Search by starting alphabet"<<endl;
    cout<<"->";
    cin>>search_choice;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>search_choice;
    }
    switch (search_choice)
    {
    case 1:
        cout<<"Enter product number : ";
        cin>>num;
        searchbyPnum(num);
        break;
    case 2:
        cout<<"Enter product name : ";
        cin>>name;
        searchbyName(name);
        break;
    case 3:
        cout<<"Enter product name : ";
        cin>>ch;
        searchbyAlpha(ch);
        break;
    default:
        cout<<"Wrong input"<<endl;
        break;
    }

    cout<<endl;
    cout<<"< Enter anykey to continue searching >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        searchMenu();
    }
}
void searchbyPnum(int num){
    //binary search
    bool found=false;
    unsigned l=0;
    unsigned r = item_record.size() - 1;
    unsigned i;

    binarySearch(item_record, l, r, num, found, i);

    if(!found){
        cout<<"Not found"<<endl;
    }else{
        stack <Item> result;
        result.push(item_record[i]);
        displaySearch(result);
    }
}
void binarySearch(vector <Item> arr, unsigned l, unsigned r, int num, bool& found, unsigned& i){
    if (num<arr[l].getProduct_num()){
        return;
    }
    if (r >= l) {
        unsigned mid = l + (r - l) / 2;

        if (arr[mid].getProduct_num() == num){
            found=true;
            i = mid;
        }else if (arr[mid].getProduct_num() > num){
            binarySearch(arr, l, mid - 1, num, found, i);
        }else if (arr[mid].getProduct_num() < num){
            binarySearch(arr, mid + 1, r, num, found, i);
        }
    }else{
        found=false;
    }
    return;
}
void searchbyName(string name){
    for(unsigned i = 0; i < name.length(); i++)
    {
        name[i] = toupper(name[i]);
    };

	stack <Item> result;

    for (unsigned i = 0; i < item_record.size(); ++i)
	{

//commented is search by exact name
//		if (item_record[i].getProduct_name() == name) {
//			result.push(item_record[i]);
//		}

        size_t found = item_record[i].getProduct_name().find(name);
        if (found != string::npos)
            result.push(item_record[i]);
	}

	if (result.empty()){
        cout<<"Product not found! "<<endl;
	}else{
        displaySearch(result);
	}
}
void searchbyAlpha(char ch){
    ch = toupper(ch);
    stack <Item> result;

    for (unsigned i = 0; i < item_record.size(); ++i)
	{
		if (item_record[i].getProduct_name()[0] == ch) {
			result.push(item_record[i]);
		}
	}

	if (result.empty()){
        cout<<"Product not found! "<<endl;
	}else{
        displaySearch(result);
	}
}
void displaySearch(stack<Item> s){
    system("cls");
    cout<<s.size()<<" result(s) found."<<endl<<endl;

    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | Product  | Name                   | Quantity | Manufacture  | Expiring     | Cost       | Price      | Margin    |"<<endl;
    cout<<" | number   |                        |          | date         | date         | (RM)       | (RM)       |           |"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    while(!s.empty()){
    cout<<" | "<<setw(8)<<left<<s.top().getProduct_num()
        <<" | "<<setw(22)<<left<<s.top().getProduct_name()
        <<" | "<<setw(8)<<left<<s.top().getQuantity()
        <<" | "<<setw(3)<<internal<<s.top().getMDay()
                <<"/"<<setw(2)<<s.top().getMMonth()
                <<"/"<<setw(4)<<s.top().getMYear()
        <<"  | "<<setw(3)<<internal<<s.top().getEDay()
                <<"/"<<setw(2)<<s.top().getEMonth()
                <<"/"<<setw(4)<<s.top().getEYear()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<s.top().getCost()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<s.top().getPrice()
        <<"  | "<<setw(6)<<right<<fixed<<setprecision(1)<<s.top().getMargin()<<" %"<<"  | "<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    s.pop();
    }
    cout<<endl;
}

//6. edit functions
void edit(){
    system("cls");
    displayCurrent();
    cout<<"Enter the product number to edit: ";
    cin>>num;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>num;
    }
    if(!check_product_num(num)){
        cout<<"No product with product number "<<num<<endl;
    }else{
        searchbyPnum(num);
        editMenu();
    }

    cout<<endl;
    cout<<"< Enter anykey to continue editing >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        edit();
    }
}
void editMenu(){
    int edit_choice;
    cout<<"_____EDIT MENU_____"<<endl;
    cout<<"1. Edit name"<<endl;
    cout<<"2. Edit quantity"<<endl;
    cout<<"3. Edit cost"<<endl;
    cout<<"4. Edit margin"<<endl;
    cout<<"5. Edit manufacture date"<<endl;
    cout<<"6. Edit expired date"<<endl;
    cout<<"->";
    cin>>edit_choice;
    while(cin.fail()){
        cout<<"Only number is allowed"<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>edit_choice;
    }
    switch (edit_choice)
    {
        case 1:
            cout<<"New name: ";
            cin>>name;
            item_record[index].setProduct_name(name);
            break;
        case 2:
            cout<<"New quantity: ";
            cin>>num;
            while(cin.fail()){
                cout<<"Only number is allowed"<<endl;
                cout<<"->";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cin>>num;
            }
            item_record[index].setQuantity(num);
            break;
        case 3:
            cout<<"New cost: RM ";
            cin>>floatnum;
            while(cin.fail()){
                cout<<"Only number is allowed"<<endl;
                cout<<"->";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cin>>floatnum;
            }
            item_record[index].setCost(floatnum);
            item_record[index].setPrice();
            break;
        case 4:
            cout<<"New margin (%): ";
            cin>>floatnum;
            while(cin.fail()){
                cout<<"Only number is allowed"<<endl;
                cout<<"->";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cin>>floatnum;
            }
            item_record[index].setMargin(floatnum);
            break;
        case 5:
            cout<<"New manufacture date (DD MM YYYY): ";
            cin>>day>>month>>year;
            while(cin.fail()||!validDate(day,month,year)||!check_manufacture_date(day, month, year))
            {
                if(cin.fail()){
                    cout<<"Only number is allowed"<<endl;
                    cout<<"->";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else if(!validDate(day,month,year)){
                    cout<<"Invalid date! Please reenter."<<endl;
                    cout<<"->";
                    cin.clear();
                }
                else{
                    cout<<"Manufacture date cannot be at the future"<<endl;
                    cout<<"->";
                    cin.clear();
                }
                cin>>day>>month>>year;
            }
            item_record[index].setmDate(day,month,year);
            break;
        case 6:
            cout<<"New expired date (DD MM YYYY): ";
            cin>>day>>month>>year;
            while(cin.fail()||!validDate(day,month,year)||!check_expired_date(day, month, year))
            {
                if(cin.fail()){
                    cout<<"Only number is allowed"<<endl;
                    cout<<"->";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else if(!validDate(day,month,year)){
                    cout<<"Invalid date! Please reenter."<<endl;
                    cout<<"->";
                    cin.clear();
                }
                else{
                    cout<<"Manufacture date cannot be at the past"<<endl;
                    cout<<"->";
                    cin.clear();
                }
                cin>>day>>month>>year;
            }
            item_record[index].seteDate(day,month,year);
            break;
        default:
            cout<<"Wrong input"<<endl;

            break;
    }

    if(edit_choice>=1 && edit_choice<=6){
        displayEdit();
    }

    cout<<endl;
    cout<<"< Enter anykey to continue editing >"<<endl;
    cout<<"< Enter '0' go back to main menu >"<<endl;
    cin>>ch;
    if(ch=='0'){
        return;
    }else{
        editMenu();
    }

}
void displayEdit(){
    system("cls");
    cout<<"Product edited"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | Product  | Name                   | Quantity | Manufacture  | Expiring     | Cost       | Price      | Margin    |"<<endl;
    cout<<" | number   |                        |          | date         | date         | (RM)       | (RM)       |           |"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<" | "<<setw(8)<<left<<item_record[index].getProduct_num()
        <<" | "<<setw(22)<<left<<item_record[index].getProduct_name()
        <<" | "<<setw(8)<<left<<item_record[index].getQuantity()
        <<" | "<<setw(3)<<internal<<item_record[index].getMDay()
                <<"/"<<setw(2)<<item_record[index].getMMonth()
                <<"/"<<setw(4)<<item_record[index].getMYear()
        <<"  | "<<setw(3)<<internal<<item_record[index].getEDay()
                <<"/"<<setw(2)<<item_record[index].getEMonth()
                <<"/"<<setw(4)<<item_record[index].getEYear()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<item_record[index].getCost()
        <<"  | "<<setw(9)<<right<<fixed<<setprecision(2)<<item_record[index].getPrice()
        <<"  | "<<setw(6)<<right<<fixed<<setprecision(1)<<item_record[index].getMargin()<<" %"<<"  | "<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------------------------"<<endl;

}

//main function
int main(){
    readFile();
    //main menu
    menu:
    system("cls");
    int main_choice;
    cout<<"_____MAIN MENU_____"<<endl;
    cout<<"1. add"<<endl;
    cout<<"2. delete"<<endl;
    cout<<"3. sort"<<endl;
    cout<<"4. display all item"<<endl;
    cout<<"5. search"<<endl;
    cout<<"6. edit"<<endl;
    cout<<"7. exit from program"<<endl;
    cout<<"->";
    cin>>main_choice;

    while(cin.fail())
    {
        cout<<"Please reenter "<<endl;
        cout<<"->";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>main_choice;
    }

    switch (main_choice)
    {
    case 1:
        addItem();
        break;
    case 2:
        delItem();
        break;
    case 3:
        sortMenu();
        break;
    case 4:
        displayMenu();
        break;
    case 5:
        searchMenu();
        break;
    case 6:
        edit();
        break;
    case 7:
        return 0;
        break;
    default:
        cout<<"Wrong input"<<endl;
        break;
    }
    writeFile();
    goto menu;

}
