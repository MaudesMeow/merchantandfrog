#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "global.hpp"


class Player
{
    public:
        Vector2 pos;
        Texture2D sprite;
        

        Player() : sprite(), pos({0,0}) {};
        Player(Texture2D sprite, Vector2 pos)
        {
            this->sprite = sprite;
            this->pos = pos;
        }

        void MovePlayer();


    private:


};




#endif