#include "player.hpp"

void Player::MovePlayer()
{
    if (IsKeyPressed(KEY_W))
    {

        pos.y -= 8;
    }
    if (IsKeyPressed(KEY_D))
    {
        pos.x += 8;
    }
    if (IsKeyPressed(KEY_S))
    {
        pos.y += 8;
    }
    if (IsKeyPressed(KEY_A))
    {
        pos.x -= 8;
    }

    // cout << "moving the boix " << endl;
    hitBox.x = pos.x+1;
    hitBox.y = pos.y+1;
}