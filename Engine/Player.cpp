#include "Player.h"

Player::Player(const Vector2& pos)
    :
    position(pos)
{
}

Vector2 Player::Position() const
{
    return position;
}

Vector2 Player::Direction() const
{
    return direction;
}

Vector2 Player::Plane() const
{
	return Cameraplane;
}

void Player::Update(Keyboard& kbd, float dt)
{

	if (kbd.KeyIsPressed(VK_UP))
	{
		position += direction * 2 * dt;
	}

	if (kbd.KeyIsPressed(VK_DOWN))
	{
		position -= direction * 2 * dt;
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		direction.Rotate(-dt);
		Cameraplane.Rotate(-dt);
		direction.Normalize();
		Cameraplane.Normalize();
	}

	if (kbd.KeyIsPressed(VK_LEFT))
	{
		direction.Rotate(dt);
		Cameraplane.Rotate(dt);
		direction.Normalize();
		Cameraplane.Normalize();
	}


}
