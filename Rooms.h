#ifndef ROOMS_H
#define ROOMS_H

class Rooms{
    public: 
        Rooms();
        
    private:
        void FindCurrentRoom();
        void NeighboringRoom();
        int Southroom;
        int Northroom;
        int Westroom;
        int Eastroom;

};
#endif