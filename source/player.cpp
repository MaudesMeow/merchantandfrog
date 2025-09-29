#include "player.hpp"

void Player::MovePlayer()
{
    if (IsKeyPressed(KEY_D))
    {
        pos.x += 8;
    }
}