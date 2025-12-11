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
     //variables for rooms
    string roomName;
    string roomDescription;
    //pointers for the rooms next to a room
    Rooms* ptrNeighborNorth;
    Rooms* ptrNeighborSouth;
    Rooms* ptrNeighborEast;
    Rooms* ptrNeighborWest;
    //item that the room has
    Items* roomItem;


    //default constructor that calls Setup()
    Rooms(){
        Setup(roomName, roomDescription, roomItem);
    }
    //calls the setup function to give it a name and description
    Rooms(string roomName, string roomDescription, Items* item){
        Setup(roomName, roomDescription, item);
    }
    //sets up what the neighbors of the current room will be
    void SetNeighbors(Rooms* ptrNorth, Rooms* ptrSouth, Rooms* ptrEast, Rooms* ptrWest){
        ptrNeighborNorth = ptrNorth;
        ptrNeighborSouth = ptrSouth;
        ptrNeighborEast = ptrEast;
        ptrNeighborWest = ptrWest;
    }

    //sets up the default names of the room and default ptrs to its neighbors
    void Setup(string roomName, string roomDescription, Items* item){
        this->roomName = roomName;
        this->roomDescription = roomDescription;
        ptrNeighborNorth = nullptr;
        ptrNeighborSouth = nullptr;
        ptrNeighborEast = nullptr;
        ptrNeighborWest = nullptr;
        roomItem = item;
    }
    void OutputRoomInfo(){
        cout << roomName << endl << roomDescription << endl;
        roomItem->DescribeItem();
        OutputNeigbors();
    }
    //outputs the current rooms neighbors
    void OutputNeigbors(){
        cout << "Head to..." << endl;
        if(ptrNeighborNorth != nullptr){cout << "North " << endl;}
        if(ptrNeighborSouth != nullptr){cout << "South " << endl;}
        if(ptrNeighborEast != nullptr){cout << "East " << endl;}
        if(ptrNeighborWest != nullptr){cout << "West " << endl;}
    }
    //sees which directions you can go from your current room
    bool CanGo(Direction direction){
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

};  
#endif