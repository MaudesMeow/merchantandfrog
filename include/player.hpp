#pragma once

#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "global.hpp"


class Player
{
    public:
        Vector2 pos;
        Texture2D sprite;
        Rectangle hitBox;
        

        Player() : sprite(), pos({0,0}), hitBox() {};
        Player(Texture2D sprite, Vector2 pos)
        {
            this->sprite = sprite;
            this->pos = pos;
            hitBox.x = pos.x+4;
            hitBox.y = pos.y+4;
            hitBox.height = 6;
            hitBox.width = 6;
        }

        void MovePlayer();


    private:


};




#endif