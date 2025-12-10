#ifndef ROOMS_HPP
#define ROOMS_HPP

#include <iostream> 
#include <string>
using namespace std;
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


    //default constructor that calls Setup()
    Rooms(){
        Setup(roomName, roomDescription);
    }
    //calls the setup function to give it a name and description
    Rooms(string roomName, string roomDescription){
        Setup(roomName, roomDescription);
    }
    //sets up what the neighbors of the current room will be
    void SetNeighbors(Rooms* ptrNorth, Rooms* ptrSouth, Rooms* ptrEast, Rooms* ptrWest){
        ptrNeighborNorth = ptrNorth;
        ptrNeighborSouth = ptrSouth;
        ptrNeighborEast = ptrEast;
        ptrNeighborWest = ptrWest;
    }

    //sets up the default names of the room and default ptrs to its neighbors
    void Setup(string roomName, string roomDescription){
        this->roomName = roomName;
        this->roomDescription = roomDescription;
        ptrNeighborNorth = nullptr;
        ptrNeighborSouth = nullptr;
        ptrNeighborEast = nullptr;
        ptrNeighborWest = nullptr;
    }
    void OutputRoomInfo(){
        cout << roomName << endl << roomDescription << endl;
        OutputNeigbors();
    }
    //outputs the current rooms neighbors
    void OutputNeigbors(){
        cout << "Head to..." << endl;
        if(ptrNeighborNorth != nullptr){cout << "(N)orth " << endl;}
        if(ptrNeighborSouth != nullptr){cout << "(S)outh " << endl;}
        if(ptrNeighborEast != nullptr){cout << "(E)ast " << endl;}
        if(ptrNeighborWest != nullptr){cout << "(W)est " << endl;}
    }

};  
#endif