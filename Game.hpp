#ifndef GAME_HPP
#define GAME_HPP
#include "Rooms.hpp"
#include "items.hpp"

#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <ctime>


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
        //check inventory amount
        int GetItemCount(string item_Name);
        //adds amount of item into counter
        void AddCount(string item_name, int amount);
        //subtracts amount of item from counter
        void SubtractCount(string item_name, int amount);
        //currently, checks if the player has entered the last room, and stops the program
        void EndCondition();
        //counts all the items that ARENT coins in the inventory and outputs the counter as a integer
        int InventoryCounter();
        //outputs ascii art for AncientDoorRoom
        void ASCIIDoor();
        //output ascii art for SlotsRoom
        void ASCIISlots();
        Rooms* ptrDungeonExit;
        Rooms* ptrCurrentRoom;
        Rooms* statueRoom;
        Items* ptrToAncientCoin;
        //vector that stores the rooms info AND item the room has
        vector<Rooms*> roomsVctr;
        vector<string> inventory; // parallel vectors that will store itemnames
        vector<int> itemCounts;   // and each item's count
        //condition of the while loop in RunGame();, as long as this isnt set true the program continuess looping
        bool isdone;
        //checks if the AncientDoor in "AncientDooRoom" is open
        bool isDoorOpen = false;
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

        if (ptrCurrentRoom->roomName == "SlotsRoom")
        {
            ASCIISlots();
        }

        ptrCurrentRoom->OutputRoomInfo();
        EndCondition();
        OutputUserInventory();
        //possible ascii art of the map youre in for better reference?
        status = HandleUserInput();

        cout << status << endl;
            
        //calls the end condition function
 //cutting out endcondition for now       EndCondition();
            
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
    Items* ancientcoin = new Items("Coin");
    ptrToAncientCoin = ancientcoin;

    int startingRoom = CreateRoom("Dungeon Entrance", "\n[You have reached the entrance of this dungeon.]\n[You came for treasure and you expect nothing less!]", nothing); //room0 //index 0
    int OutsideEntrance = CreateRoom("Outside Entrance", "\n[This is forest outside of the Dungeon.]\n[You hear nothing but the wind sending regards.]", nothing); //room1 //index 1
    int dungeonExit = CreateRoom("Dungeon Exit", "\n[You are at the last room of the dungeon.]", nothing); //room17 //index 2
    int room2 =CreateRoom("Dungeon Room2", "\n[Nothing but dim lights and an intersection ahead.]", nothing);
    int room3 =CreateRoom("Dungeon Room3", "\n[You see a hole in the wall leaking some undescribable fluid.]\n[Below you see a cyan object covered in the fluid.]", sapphire);
    int room4 =CreateRoom("Dungeon Room4", "\n[Theres a shining object in the center of the room.]", ruby);
    int room5 =CreateRoom("Dungeon Room5", "\n[Nothing special about this room.]", gold);
    int room6 =CreateRoom("Dungeon Room6", "\n[You see a skeleton on the wall with a bright yellow object in its throat.]", gold);
    int room7 =CreateRoom("Dungeon Room7", "\n[This hall extends a couple more rooms down.]", ruby);
    int room8 =CreateRoom("Dungeon Room8", "\n[Nothing special about this room. You are met with an intersection.]", nothing);
    int room9 =CreateRoom("Dungeon Room9", "\n[You see a blanket covering some object on the floor.]\n[It gives off a putrid smell.]", gold);
    int room10 =CreateRoom("Dungeon Room10", "\n[The people who made this dungeon could've done a better job at decorating.]", gold);
    int room11 =CreateRoom("Dungeon Room11", "\n[Nothing special about this room.]", sapphire);
    int room12 =CreateRoom("Dungeon Room12", "\n[A faint shimmering sound is coming from the room ahead.]", gold);
    int statueRoom =CreateRoom("StatueRoom", "\n[You enter a room in the middle of the hall.]\n[The center reveals a goddess statue, the figure bathed in golden light.]\n[You see an Ancient Coin[coin] glistening at its feet...]", ancientcoin);
    //this statueRoom is equal to the OTHER statueRoom you see above
    this->statueRoom = roomsVctr[statueRoom];
    int room14 =CreateRoom("Dungeon Room14", "\n[You're met with another intersection, but you hear noises WEST.]", ruby);
    int slotsRoom =CreateRoom("SlotsRoom", "\n[This is the end of the hallway. You hear incessant beeping and loud noises.]\n[You have a look and see that its a [slots] machine.]\n[It calls for you to [play] it.]", sapphire);
    int ancientDoorRoom =CreateRoom("AncientDoorRoom", "\n[You take a left at the corridor and see a vast empty room with nothing but another door inside.]", nothing);
  
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
    roomsVctr[room10]         ->SetNeighbors(nullptr, roomsVctr[room11], nullptr, nullptr);
    roomsVctr[room11]         ->SetNeighbors(roomsVctr[room10], roomsVctr[room12], nullptr, roomsVctr[room8]);
    roomsVctr[room12]         ->SetNeighbors(roomsVctr[room11], nullptr, nullptr, roomsVctr[statueRoom]);
    roomsVctr[statueRoom]     ->SetNeighbors(nullptr, nullptr, roomsVctr[room12], roomsVctr[room14]);//room13
    roomsVctr[room14]         ->SetNeighbors(nullptr, roomsVctr[ancientDoorRoom], roomsVctr[statueRoom], roomsVctr[slotsRoom]);
    roomsVctr[slotsRoom]      ->SetNeighbors(nullptr, nullptr, roomsVctr[room14], nullptr);//room15
    roomsVctr[ancientDoorRoom]         ->SetNeighbors(roomsVctr[room14], nullptr, roomsVctr[dungeonExit], nullptr);//room16


    roomsVctr[dungeonExit]->SetNeighbors(nullptr, nullptr, nullptr, roomsVctr[ancientDoorRoom]);


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

        
    cout <<"\n------------------What will you do?------------------" << endl;
    cout <<"-----EITHER [go] or [get] with direction or item-----" << endl << endl;
   
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
        //set boolean false so the door is NOT open initially
        
        //special check to see if you choose to go east towards the locked door in room 16
        if(ptrCurrentRoom->roomName == "AncientDoorRoom" && (lower_dORo ==  "east" || lower_dORo ==  "e")){
            //only does this loop if the door is closed(false), then sets door to open(true) in which case this code block will NOT run again until the program terminates
            if(!isDoorOpen){
                if(GetItemCount("Coin") >= 4){
                    cout << "The four slots shine brilliantly as you insert each Ancient Coin." << endl;
                    SubtractCount("Coin", 4); 
                    // you meet the requirements to open the door
                    status = "The Ancient Door opens up the path to the last room of the dungeon...";
                    //move into dungeon exit
                    ptrCurrentRoom = ptrCurrentRoom->ptrNeighborEast;
                    //the door is ALWAYS open now, so it wont enter this block again
                    isDoorOpen = true;
                }
                else{
                    //you dont meet the requirements to open the door
                    status = "You push the door with all you might but it wont budge.\nIn your attempt to open the door, you notice 4 quarter sized holes on it face.";
                    ASCIIDoor();
                }
            }
             else{
//ATTEMPT1: making the door stay open while keeping the rooms ptr vector the same
                ptrCurrentRoom = ptrCurrentRoom->ptrNeighborEast;
                status = "You went EAST.";
            }
        }
        else if(lower_dORo ==  "north" || lower_dORo ==  "n"){
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
        if(ptrCurrentRoom->roomName == "StatueRoom" && lower_dORo == "coin"){
            if(ptrCurrentRoom->ancientCoinAvailable){
                cout << "You retrieve the Ancient Coin from the statues feet" << endl;
                //call additem function
                AddCount("Coin", 1);
                //once u pick up the coin, it is no longer available to pick up
                ptrCurrentRoom->ancientCoinAvailable = false;
                //changes the current roomitem to the starting roomitem, which is nothing
                ptrCurrentRoom->roomItem = roomsVctr[0]->roomItem;
                status = "The statue's base is now empty.";
            }
            else{
                status = "The Ancient Coin is not here.";
            }

        }
        else if(lower_dORo == ToLowerString(ptrCurrentRoom->roomItem->GetItemName())){
           cout << "You grabbed " << ptrCurrentRoom->roomItem->GetItemName() << endl;
           ptrCurrentRoom->AddItemtoInventory(inventory, itemCounts);
           
           status = "Item obtained.";
        }
    }//if the first word is play
    else if(lower_command == "play"){
        //check room15 and try to play slots // ptrCurrentRoom == roomsVctr[15]
        if(ptrCurrentRoom->roomName == "SlotsRoom" && lower_dORo == "slots"){
            if(GetItemCount("Coin") < 1){
                status = "You need an Ancient Coin to play slots. Try backtracking...";
            }
            else{
                //take 1 coin
                SubtractCount("Coin", 1);
                //rand implementation
                srand(time(0));
                int outcome  = rand() % 2;
                //win condition
                if(outcome == 0){
                    AddCount("Coin", 2);
                    status = "\n[The slots machine dings multiple times. You just won 2 Ancient Coins!]";
                }
                else{ // lose condition
                    status = "[A clink is the last sound you hear before the room gets deafeningly quiet. You lost your Ancient Coin.]";
                }        
                //this->statueRoom from earlier is called to check if ancientCoinAvailable is false,
                if(!this->statueRoom->ancientCoinAvailable){
                    this->statueRoom->ResetCoin(ptrToAncientCoin); 
                    status += "\n[You hear a chime echo behind you. It seems like it came from the StatueRoom?]"; 
                }
            }
        }
        
    }
    else{
        status = "Unknown Command";
    }
    
    return status;
}

void Game::OutputUserInventory(){
    cout << "\nInventory: {";
    for (long unsigned int i = 0; i < inventory.size(); i++)
    {
        cout << itemCounts.at(i) << " " << inventory.at(i) << ", ";
    }
    cout << "}" << endl;
}
/* Code was written with the help of gemini ai
    when given the prompt "how would I make a pause system for a text game"
    the message generated helped me write this code
*/
void Game::ClearConsole(){
    for(int i = 0; i < 20; i++){
        cout << "-----------------------" << endl;
    }

}

void Game::Pause(){
    cout << endl << "Press Enter to continue..." << endl;

    cin.get();
}

int Game::GetItemCount(string item_Name){
    string lower_name = ToLowerString(item_Name);
    for(unsigned long int i = 0; i < inventory.size(); i++){
        if(ToLowerString(inventory[i]) == lower_name){
            return itemCounts[i];
        }
    }
    //return 0 if item not found
    return 0; 
}

/*Code was written with the help of gemini ai
    when given the prompt "how would I implement a simple gambling game involving coins"
    the message generated helped me write this code
*/
void Game::AddCount(string item_name, int amount){
    string lower_name = ToLowerString(item_name);
    for(unsigned long int i = 0; i < inventory.size(); i++){
        if(ToLowerString(inventory[i]) == lower_name){
            itemCounts[i]+= amount;
            return;
        }  
    }
    inventory.push_back(item_name);
    itemCounts.push_back(amount);
        
}

void Game::SubtractCount(string item_name, int amount){
    string lower_name = ToLowerString(item_name);
    for(unsigned long int i = 0; i < inventory.size(); i++){
        if(ToLowerString(inventory[i]) == lower_name){
            itemCounts[i] -= amount;
            //prevents negative numbers
            if(itemCounts[i] < 0){
                itemCounts[i] = 0;
            }
            return;
        }
    }
}

void Game::EndCondition(){
    if(ptrCurrentRoom->roomName == "Dungeon Exit" ){
        cout << "\n[In front of you lies a void.]\n[It pulls you closer, as if to suck you in...]" << endl;
        //now do inventory check if player has 6 gold, if so, do the below with some extra couts for flair
        if(InventoryCounter() == 11){
            isdone = true;
            cout << "\n[A violent white fills the room, and as it dims a hole emerges.]\n[You've made it out of the Dungeon!]" << endl; 
        }
        else{
            cout << "\n['We won't accept this.']['Return when you get...hmmm...richer.']" << endl;
        }

    }
}
int Game::InventoryCounter(){
    int counter = 0;
    for(unsigned long int i = 0;i < inventory.size(); i++){
        if(inventory[i] != "Coin"){
            counter += itemCounts[i];
        }
    }
    return counter;
}
/* Asci art was inspired by art from https://www.asciiart.eu
    provided to us by our professor
*/
void Game::ASCIISlots()
{
    cout << "                               || " << endl;
    cout << "nununununununununununununu    ||||" << endl;
    cout << "OO||||||||||||||||||||||OO   ||||||" << endl;
    cout << "OO||||||||||||||||||||||OO    ||||" << endl;
    cout << "OO|||||000||||||||||||||OO     ||" << endl;
    cout << "OO||||00 00|||||||||||||OO     ||" << endl;
    cout << "OO|||000 000||||||||||||OO-----//" << endl;
    cout << "OO||||00 00|||||||||||||OO-----//" << endl;
    cout << "OO|||||000||||||||||||||OO" << endl; 
    cout << "OO||||||||||||||||||||||OO" << endl;
    cout << "OO||||||----------||||||OO" << endl;
    cout << "OO||||||          ||||||OO" << endl;
    cout << "OO||||||----------||||||OO" << endl;
    cout << "OO||||||||||||||||||||||OO" << endl;
    cout << "nununununununununununununu" << endl;
    cout << endl;
}

void Game::ASCIIDoor()
{
    cout << endl;
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
    cout << "O:::::::::::::::::::::::O" << endl;
    cout << "O::::0000:::::::0000::::O" << endl;
    cout << "O:::0----0:::::0----0:::O" << endl;
    cout << "O::::0000:::::::0000::::O" << endl;
    cout << "O:::::::::::::::::::::::O" << endl;
    cout << "O::::::::::::::::::::00:O" << endl;
    cout << "O:::::::::::::::::::0000O" << endl;
    cout << "O::::::::::::::::::::00:O" << endl;
    cout << "O:::::::::::::::::::::::O" << endl;
    cout << "O::::0000:::::::0000::::O" << endl;
    cout << "O:::0----0:::::0----0:::O" << endl;
    cout << "O::::0000:::::::0000::::O" << endl;
    cout << "O:::::::::::::::::::::::O" << endl;
    cout << "O:::::::::::::::::::::::O" << endl;
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
    cout << endl;
}

#endif