#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <vector>
#include <string>
using namespace std;

//Class header file stuff
class Items{
    public: 
        Items(string itemName);
        void GiveItemName(string itemName);
        void DescribeItem();
        string GetItemName();
        
    private:
        
        string itemName;
};

Items::Items(string itemName){
    this->itemName = itemName;
}

void Items::GiveItemName(string itemName){
    this->itemName = itemName;
}



void Items::DescribeItem() {
    cout << "\nThere is [" << itemName << "] in here.\n" << endl;
}

string Items::GetItemName(){
    return itemName;
}
#endif