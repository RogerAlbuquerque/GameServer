#include "Player.h"

void Player::Update(float deltaTime)
{
  if (input.up)
    transform.x += deltaTime;

  if (input.down)
    transform.x -= deltaTime;

  if (input.left)
    transform.y -= deltaTime;

  if (input.right)
    transform.y += deltaTime;
}