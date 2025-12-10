#ifndef GAME_HPP
#define GAME_HPP
#include "Rooms.hpp"
#include "items.hpp"

#include <cctype>
#include <string>
#include <vector>
#include <limits>

using namespace std;

//the game system class
class Game{
    public:
        //default constructor for game class
        Game(){
            Rooms* ptrCurrentRoom = nullptr;
            SetupRooms();
            isdone = false;   
        }
        //function that runs the game
        void RunGame(){
            
            string status = "";
             while(!isdone){
                ptrCurrentRoom->OutputRoomInfo();

                status = HandleUserInput();

                cout << status << endl;
                Pause();
            }
        }
        
    private:
        // pushes the rooms into the roomsVctr vector
        int CreateRoom(string name, string description){
            Rooms* rooms = new Rooms();

            rooms->Setup(name, description);
            roomsVctr.push_back(rooms);

            return roomsVctr.size() -1;
        }

        // sets up the rooms starting with the first room and its neighboring rooms  
        void SetupRooms(){
            int startingRoom = CreateRoom("Dungeon Entrance", "You have reached the entrance.");
            int OutsideEntrance = CreateRoom("Outside Entrance", "This is the outside near a forest.");
            int dungeonExit = CreateRoom("Dungeon Exit", " You are at the last room of the dungeon.");

        /*  rooms[1].Setup("Room1", "description text here");
            rooms[2].Setup("Room2", "description text here");
            rooms[3].Setup("Room3", "description text here");
            rooms[4].Setup("Room4", "description text here");
            rooms[5].Setup("Room5", "description text here");
            rooms[6].Setup("Room6", "description text here");
            rooms[7].Setup("Room7", "description text here");
            rooms[8].Setup("Room8", "description text here");
            rooms[9].Setup("Room9", "description text here");
            rooms[10].Setup("Room10", "description text here");
            rooms[11].Setup("Room11", "description text here");
            rooms[12].Setup("Room12", "description text here");
            rooms[13].Setup("Room13", "description text here");
            rooms[14].Setup("Room14", "description text here");
            rooms[15].Setup("Room15", "description text here");
            rooms[16].Setup("Room16", "description text here");
            rooms[17].Setup("Room17", "description text here");
            //the rooms connected to each room(where can u go after this room)
            rooms[0].SetNeighbors(nullptr,nullptr,nullptr, rooms[1]); */

            roomsVctr[startingRoom]->SetNeighbors(nullptr, nullptr, roomsVctr[dungeonExit], roomsVctr[OutsideEntrance]);

            ptrCurrentRoom = roomsVctr[startingRoom]; 
        }

        //function to convert strings to lowercase
        string ToLowerString(string str){
            for(char &c : str){
                c = tolower(c);
            }
            return str;
        }

        //Handles the user input, checks if the direction player wants to go is available, then changes the currentroom to that new room
        string HandleUserInput(){
            string status = "";
            string userInput ;
            cout <<"What will you do? " << endl;
            getline(cin, userInput);

            string lowerInput = ToLowerString(userInput);
            if(lowerInput ==  "north"){
                //changes current room to room in that direction, or tells the player they cant go in that direction
                if(ptrCurrentRoom->CanGo(NORTH)){
                    status = "You went NORTH."; 
                    ptrCurrentRoom = ptrCurrentRoom->ptrNeighborNorth;                    
                }
                else{
                    status = "You cant go NORTH here."; 
                }
                     
            }
            else if(lowerInput ==  "south"){
                //changes current room to room in that direction, or tells the player they cant go in that direction
                if(ptrCurrentRoom->CanGo(SOUTH)){
                    status = "You went SOUTH."; 
                    ptrCurrentRoom = ptrCurrentRoom->ptrNeighborSouth;                    
                }
                else{
                    status = "You cant go SOUTH here."; 
                }
                     
            }
            else if(lowerInput ==  "east"){
                //changes current room to room in that direction, or tells the player they cant go in that direction
                if(ptrCurrentRoom->CanGo(EAST)){
                    status = "You went EAST."; 
                    ptrCurrentRoom = ptrCurrentRoom->ptrNeighborEast;                    
                }
                else{
                    status = "You cant go EAST here."; 
                }
                     
            }
            else if(lowerInput ==  "west"){
                //changes current room to room in that direction, or tells the player they cant go in that direction
                if(ptrCurrentRoom->CanGo(WEST)){
                    status = "You went WEST."; 
                    ptrCurrentRoom = ptrCurrentRoom->ptrNeighborWest;                    
                }
                else{
                    status = "You cant go WEST here."; 
                }
                     
            }            
            return status;
        }

        //gives a pause after each action the player does
        void Pause(){
            system("pause");
            cout << endl << "Press Enter to continue..." << endl;
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
        }

        Rooms* ptrCurrentRoom;
        //vector that stores the rooms
        vector<Rooms*> roomsVctr;
        bool isdone;
};

#endif