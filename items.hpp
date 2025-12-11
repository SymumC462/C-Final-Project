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
        void AddItemtoInventory(vector<string> inventory);
        void DescribeItem();
        
    private:
        string GetItemName();
        string itemName;
};

Items::Items(string itemName){
    this->itemName = itemName;
}

void Items::GiveItemName(string itemName){
    this->itemName = itemName;
}

void Items::AddItemtoInventory(vector<string> inventory){
    inventory.push_back(this->itemName);
}

void Items::DescribeItem() {
    cout << "There is " << itemName << " in here." << endl;
}

string Items::GetItemName(){
    return itemName;
}
#endif