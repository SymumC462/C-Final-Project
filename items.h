#ifndef ITEMS_H
#define ITEMS_H

#include <string>
using namespace std;

//Class header file stuff
class Items{
    public: 
        void GiveItemName();
        void AddItemtoInventory();
    private:
        string itemName;
};

#endif