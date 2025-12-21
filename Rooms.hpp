#ifndef ROOMS_HPP
#define ROOMS_HPP

#include <iostream> 
#include <string>
#include "items.hpp"
using namespace std;

//This code was adapted by  the people at GeeksForGeeks
//https://www.geeksforgeeks.org/c/enumeration-enum-c/

//gives names to the number values representing the 4 cardinal directions
enum Direction {NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3};

//This code was adapted by  the people at GeeksForGeeks
//https://www.geeksforgeeks.org/cpp/structures-in-cpp/

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
    //called to game.hpp to reset the ancient coin in statue room
    void ResetCoin(Items* ancientCoinPtr);
    void OutputRoomInfo();
    //outputs the current rooms neighbors
    void OutputNeigbors();
    //sees which directions you can go from your current room
    bool CanGo(Direction direction);
    void AddItemtoInventory(vector<string>& inventory, vector<int>& itemCounts);

    //variables for the rooms
    string roomName;
    string roomDescription;
    // boolean to see if a coin is available, and a pointer to the original coin object
    bool ancientCoinAvailable;
    Items* ptrToAncientCoin;
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
    //checks if the roomName is statueRoom, then a coin is available
    ancientCoinAvailable = (roomName == "StatueRoom");
    if(ancientCoinAvailable){
        ptrToAncientCoin = item;
    }
    else{
        ptrToAncientCoin = nullptr;
    }

}
//when called in Game.hpp, sets boolean ancientCoinAvailable to true
void Rooms::ResetCoin(Items* ancientCoinPtr){
    if(roomName == "StatueRoom"){
        roomItem = ancientCoinPtr;
        ancientCoinAvailable = true;

    }
}
//outputs each rooms info
void Rooms::OutputRoomInfo(){
    cout << roomName << endl << roomDescription << endl;
    roomItem->DescribeItem();
    OutputNeigbors();
}
//outputs the current rooms neighbors
void Rooms::OutputNeigbors(){
    cout << "Head to..." << endl << endl;
    if(ptrNeighborNorth != nullptr){cout << "[North] " << endl;}
    if(ptrNeighborSouth != nullptr){cout << "[South] " << endl;}
    if(ptrNeighborEast != nullptr){cout << "[East] " << endl;}
    if(ptrNeighborWest != nullptr){cout << "[West] " << endl;}
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
//when you [get] an item, it puts it into the inventory vector and outputs it all, 
//along with the parallel vector itemCounts to show how many of one item you have in the inventory 
void Rooms::AddItemtoInventory(vector<string>& inventory, vector<int>& itemCounts){
    string itemToCheck = roomItem->GetItemName(); 
    bool itemIsInInventory = false;
    bool itemIsNothing = false;
    // as long as it reads the room's itemname as nothing, it assumes the room has nothing
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
        cout << "\nYou put " << roomItem->GetItemName() << " into your inventory." << endl;
        roomItem = nowNothing;
    }

}

#endif