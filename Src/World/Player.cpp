#include "Player.h"

void Player::Update(float deltaTime)
{
  if (input.up)
    transform.y += deltaTime;

  if (input.down)
    transform.y -= deltaTime;

  if (input.left)
    transform.x -= deltaTime;

  if (input.right)
    transform.x += deltaTime;
}