#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
using namespace std;

//Class header file stuff
class Items{
    public: 
        Items(string itemName);
        void GiveItemName(string itemName);
        void AddItemtoInventory();
        
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

void Items::AddItemtoInventory(){

}


string Items::GetItemName(){
    return itemName;
}
#endif