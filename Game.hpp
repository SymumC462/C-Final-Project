#ifndef GAME_HPP
#define GAME_HPP
#include "Rooms.hpp"
#include "items.hpp"

#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

//the game system class
class Game{
    public:
        //default constructor for game class
        Game();
        //function that runs the game
        void RunGame();
        
    private:
    // pushes the rooms info AND item into the roomsVctr vector
    int CreateRoom(string name, string description, Items* item);
    // sets up the rooms starting with the first room and its neighboring rooms  
    void SetupRooms();
    //function to convert strings to lowercase
    string ToLowerString(string str);
    //Handles the user input, checks if the direction player wants to go is available, then changes the currentroom to that new room
    string HandleUserInput(); 
    // outputs the inventory as a vector of strings and ints, representing the item and its amount
    void OutputUserInventory();
    //skips 50 lines to make stuff more readable
    void ClearConsole();
    //gives a pause after each action the player does
    void Pause();
    //currently, checks if the player has entered the last room, and stops the program
    void EndCondition();
    
    Rooms* ptrDungeonExit;
    Rooms* ptrCurrentRoom;
    //vector that stores the rooms info AND item the room has
    vector<Rooms*> roomsVctr;
    vector<string> inventory; // parallel vectors that will store itemnames
    vector<int> itemCounts;   // and each item's count
    bool isdone;
};  

//the function definitions below

Game::Game(){
        
    this->ptrCurrentRoom = nullptr;
    SetupRooms();
    isdone = false;   
}

void Game::RunGame(){
        
    string status = "";
    while(!isdone){
        ptrCurrentRoom->OutputRoomInfo();
        
        OutputUserInventory();
        //possible ascii art of the map youre in for better reference?
        status = HandleUserInput();

        cout << status << endl;
            
        //calls the end condition function
        EndCondition();
            
        //pauses the game IF the game is still running
        if(!isdone){
            Pause();
            ClearConsole(); 
        }
            
    }
    //final pause so the game doesnt stop upruptly
    if(isdone){
        Pause();
    }

}

int Game::CreateRoom(string name, string description, Items* item){
    int index = roomsVctr.size();
    Rooms* rooms = new Rooms();

    rooms->Setup(name, description, item);
    roomsVctr.push_back(rooms);

    return index;
}

void Game::SetupRooms(){
    cout << "Creation Process." << endl;

    // all possible items in the dungeon
    Items* nothing = new Items("nothing");
    Items* gold = new Items("gold");
    Items* ruby = new Items("ruby");
    Items* sapphire = new Items("sapphire");

    int startingRoom = CreateRoom("Dungeon Entrance", "You have reached the entrance.", nothing); //room0 //index 0
    int OutsideEntrance = CreateRoom("Outside Entrance", "This is the outside near a forest.", nothing); //room1 //index 1
    int dungeonExit = CreateRoom("Dungeon Exit", " You are at the last room of the dungeon.", nothing); //room17 //index 2
    int room2 =CreateRoom("Room2", "2nd room of this dungeon", nothing);
    int room3 =CreateRoom("Room3", "Third room of this dungeon", sapphire);
    int room4 =CreateRoom("Room4", "4th room of this dungeon", ruby);
    int room5 =CreateRoom("Room5", "5th room of this dungeon", gold);
    int room6 =CreateRoom("Room6", "6th room of this dungeon", gold);
    int room7 =CreateRoom("Room7", "7th room of this dungeon", ruby);
    int room8 =CreateRoom("Room8", "8th room of this dungeon", nothing);
    int room9 =CreateRoom("Room9", "9th room of this dungeon", gold);
    int room10 =CreateRoom("Room10", "10th room of this dungeon", gold);
    int room11 =CreateRoom("Room11", "11th room of this dungeon", sapphire);
    int room12 =CreateRoom("Room12", "12th room of this dungeon", gold);
    int room13 =CreateRoom("Room13", "13th room of this dungeon", gold);
    int room14 =CreateRoom("Room14", "14th room of this dungeon", ruby);
    int room15 =CreateRoom("Room15", "15th room of this dungeon", sapphire);
        int room16 =CreateRoom("Room16", "16th room of this dungeon", nothing);

        
    cout << "Setup Process." << endl;
    // the parameters go by whats              NORTH,   SOUTH,    EAST,     WEST
    roomsVctr[startingRoom]   ->SetNeighbors(nullptr, nullptr, roomsVctr[OutsideEntrance], roomsVctr[room2]);
    roomsVctr[OutsideEntrance]->SetNeighbors(nullptr, nullptr, nullptr, roomsVctr[startingRoom]);
    roomsVctr[room2]          ->SetNeighbors(nullptr, roomsVctr[room4], roomsVctr[startingRoom], roomsVctr[room3]);
    roomsVctr[room3]          ->SetNeighbors(nullptr, roomsVctr[room5], roomsVctr[room2], nullptr);
    roomsVctr[room4]          ->SetNeighbors(roomsVctr[room2], nullptr, nullptr, roomsVctr[room5]);
    roomsVctr[room5]          ->SetNeighbors(roomsVctr[room3], roomsVctr[room6], roomsVctr[room4], nullptr);
    roomsVctr[room6]          ->SetNeighbors(roomsVctr[room5], nullptr, roomsVctr[room7], nullptr);
    roomsVctr[room7]          ->SetNeighbors(nullptr, nullptr, roomsVctr[room8], roomsVctr[room6]);
    roomsVctr[room8]          ->SetNeighbors(roomsVctr[room9], nullptr, roomsVctr[room11], roomsVctr[room7]);
    roomsVctr[room9]          ->SetNeighbors(nullptr, roomsVctr[room8], nullptr, nullptr);
    roomsVctr[room10]          ->SetNeighbors(nullptr, roomsVctr[room11], nullptr, nullptr);
    roomsVctr[room11]          ->SetNeighbors(roomsVctr[room10], roomsVctr[room12], nullptr, roomsVctr[room8]);
    roomsVctr[room12]          ->SetNeighbors(roomsVctr[room11], nullptr, nullptr, roomsVctr[room13]);
    roomsVctr[room13]          ->SetNeighbors(nullptr, nullptr, roomsVctr[room12], roomsVctr[room14]);
    roomsVctr[room14]          ->SetNeighbors(nullptr, roomsVctr[room16], roomsVctr[room13], roomsVctr[room15]);
    roomsVctr[room15]          ->SetNeighbors(nullptr, nullptr, roomsVctr[room14], nullptr);
    roomsVctr[room16]          ->SetNeighbors(roomsVctr[room14], nullptr, roomsVctr[dungeonExit], nullptr);


    roomsVctr[dungeonExit]->SetNeighbors(nullptr, nullptr, nullptr, roomsVctr[room16]);


    ptrCurrentRoom = roomsVctr[startingRoom]; 
    ptrDungeonExit = roomsVctr[dungeonExit];
    Pause();
}

string Game::ToLowerString(string str){
    for(char &c : str){
        c = tolower(c);
    }
    return str;
}

string Game::HandleUserInput(){
    string status = "";
    string userInput ;

        
    cout <<"What will you do?  " << endl;
    cout <<"-----EITHER [go] or [get] with direction or item-----" << endl;
   
    getline(cin, userInput);
    //stringstream splits the input by words
    stringstream ss(userInput);
    string command;
    string dORo;
    //takes the first word as a command
    ss >> command;
    string lower_command = ToLowerString(command);
    //takes the second word as direction/object
    ss >> dORo;
    string lower_dORo = ToLowerString(dORo); 

    //checks the first word to see what command u choose, then checks second word to see where you want to go/ what you want to grab
    if(lower_command == "go"){
        if(lower_dORo ==  "north" || lower_dORo ==  "n"){
            //changes current room to room in that direction, or tells the player they cant go in that direction
            if(ptrCurrentRoom->CanGo(NORTH)){
                status = "You went NORTH."; 
                ptrCurrentRoom = ptrCurrentRoom->ptrNeighborNorth;                    
            }
            else{
                status = "You cant go NORTH here."; 
            }
                        
        }
        else if(lower_dORo ==  "south" || lower_dORo ==  "s"){
            //changes current room to room in that direction, or tells the player they cant go in that direction
            if(ptrCurrentRoom->CanGo(SOUTH)){
                status = "You went SOUTH."; 
                ptrCurrentRoom = ptrCurrentRoom->ptrNeighborSouth;                    
            }
            else{
                status = "You cant go SOUTH here."; 
            }
                        
        }
        else if(lower_dORo ==  "east" || lower_dORo ==  "e"){
            //changes current room to room in that direction, or tells the player they cant go in that direction
            if(ptrCurrentRoom->CanGo(EAST)){
                status = "You went EAST."; 
                ptrCurrentRoom = ptrCurrentRoom->ptrNeighborEast;                    
            }
            else{
                status = "You cant go EAST here."; 
            }
                        
        }
        else if(lower_dORo ==  "west" || lower_dORo ==  "w"){
            //changes current room to room in that direction, or tells the player they cant go in that direction
            if(ptrCurrentRoom->CanGo(WEST)){
                status = "You went WEST."; 
                ptrCurrentRoom = ptrCurrentRoom->ptrNeighborWest;                    
            }
            else{
                status = "You cant go WEST here."; 
            }
                        
        } 
        else{
            status = "Unknown Command";
        }             
    }//if first word is get, and second word is the rooms item name, say u grabbed it
    else if(lower_command == "get"){
        if(lower_dORo == ptrCurrentRoom->roomItem->GetItemName()){
           cout << "You grabbed " << ptrCurrentRoom->roomItem->GetItemName() << endl;
           ptrCurrentRoom->AddItemtoInventory(inventory, itemCounts);
           //ptrCurrentRoom->
        }
    }
    else{
        status = "Unknown Command";
    }
    
    return status;
}

void Game::OutputUserInventory(){
    cout << "Inventory: {";
    for (long unsigned int i = 0; i < inventory.size(); i++)
    {
        cout << itemCounts.at(i) << " " << inventory.at(i) << ", ";
    }
    cout << "}" << endl;
}

void Game::ClearConsole(){
    for(int i = 0; i < 50; i++){
        cout << "-----------------------" << endl;
    }

}

void Game::Pause(){
    cout << endl << "Press Enter to continue..." << endl;

    cin.get();
}

void Game::EndCondition(){
    if(ptrCurrentRoom == ptrDungeonExit ){
        isdone = true;
        cout << "This is the exit of the Dungeon. You made it out!" << endl;
    }
}

#endif