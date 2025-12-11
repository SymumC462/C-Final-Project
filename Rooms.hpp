#ifndef ROOMS_HPP
#define ROOMS_HPP

#include <iostream> 
#include <string>
#include "items.hpp"
using namespace std;

//gives names to the number values representing the 4 cardinal directions
enum Direction {NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3};

//struct allows for different datatypes; basically an array that can sort ints, strings, bools, etc, in the same list
struct Rooms{   
    //default constructor that calls Setup()
    Rooms();
    //calls the setup function to give it a name and description
    Rooms(string roomName, string roomDescription, Items* item);
    //sets up what the neighbors of the current room will be
    void SetNeighbors(Rooms* ptrNorth, Rooms* ptrSouth, Rooms* ptrEast, Rooms* ptrWest);

    //sets up the default names of the room and default ptrs to its neighbors
    void Setup(string roomName, string roomDescription, Items* item);
    void OutputRoomInfo();
    //outputs the current rooms neighbors
    void OutputNeigbors();
    //sees which directions you can go from your current room
    bool CanGo(Direction direction);
    void AddItemtoInventory(vector<string>& inventory, vector<int>& itemCounts);

    //variables for the rooms
    string roomName;
    string roomDescription;
    //pointers for the rooms next to a room [roomx is north of roomy, roomz is south of roomy, etc]
    Rooms* ptrNeighborNorth;
    Rooms* ptrNeighborSouth;
    Rooms* ptrNeighborEast;
    Rooms* ptrNeighborWest;
    //item that the room has
    Items* roomItem;
};
//default constructor that calls Setup()
Rooms::Rooms(){
    Setup(roomName, roomDescription, roomItem);
}
//calls the setup function to give it a name and description
Rooms::Rooms(string roomName, string roomDescription, Items* item){
    Setup(roomName, roomDescription, item);
}
//sets up what the neighbors of the current room will be
void Rooms::SetNeighbors(Rooms* ptrNorth, Rooms* ptrSouth, Rooms* ptrEast, Rooms* ptrWest){
    ptrNeighborNorth = ptrNorth;
    ptrNeighborSouth = ptrSouth;
    ptrNeighborEast = ptrEast;
    ptrNeighborWest = ptrWest;
}

//sets up the default names and item of the room and default ptrs to its neighbors
void Rooms::Setup(string roomName, string roomDescription, Items* item){
    this->roomName = roomName;
    this->roomDescription = roomDescription;
    ptrNeighborNorth = nullptr;
    ptrNeighborSouth = nullptr;
    ptrNeighborEast = nullptr;
    ptrNeighborWest = nullptr;
    roomItem = item;
}
void Rooms::OutputRoomInfo(){
    cout << roomName << endl << roomDescription << endl;
    roomItem->DescribeItem();
    OutputNeigbors();
}
//outputs the current rooms neighbors
void Rooms::OutputNeigbors(){
    cout << "Head to..." << endl;
    if(ptrNeighborNorth != nullptr){cout << "North " << endl;}
    if(ptrNeighborSouth != nullptr){cout << "South " << endl;}
    if(ptrNeighborEast != nullptr){cout << "East " << endl;}
    if(ptrNeighborWest != nullptr){cout << "West " << endl;}
}
//sees which directions you can go from your current room
bool Rooms::CanGo(Direction direction){
    if(direction == NORTH && ptrNeighborNorth != nullptr){
        return true;
    }
    if(direction == SOUTH && ptrNeighborSouth != nullptr){
        return true;
    }
    if(direction == EAST && ptrNeighborEast != nullptr){
        return true;
    }
    if(direction == WEST && ptrNeighborWest != nullptr){
        return true;
    }
    return false;
}  

void Rooms::AddItemtoInventory(vector<string>& inventory, vector<int>& itemCounts){
    string itemToCheck = roomItem->GetItemName(); 
    bool itemIsInInventory = false;
    bool itemIsNothing = false;
    Items* nowNothing = new Items("nothing");
    if (itemToCheck == "nothing")
    {
        itemIsNothing = true;
    }
    // checks to see if the item we're adding is the same as an item currently in the inventory, and only does so when the item isn't nothing
    if (!(itemIsNothing))
    {
        for (unsigned long int i = 0; i < inventory.size(); i++) // iterates through the current inventory to check for an item already existing
        {
            if (inventory.at(i) == itemToCheck)
            {
                itemCounts.at(i)++;
                itemIsInInventory = true;
            }
        }
        if (!(itemIsInInventory))
        {
            inventory.push_back(roomItem->GetItemName());
            itemCounts.push_back(1);
        }
        cout << "You put " << roomItem->GetItemName() << " into your inventory." << endl;
        roomItem = nowNothing;
    }

}
#endif