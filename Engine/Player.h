#pragma once
#include "Vector2.h"
#include "Keyboard.h"
#include "ChiliWin.h"

class Player
{
public:
	Player(const Vector2& pos);

	Vector2 Position() const;
	Vector2	Direction() const;
	Vector2	Plane() const;

	void Update(Keyboard& wnd, float dt);

private:
	Vector2 position;           // world space
	Vector2 direction{ -1,0 };  // world space
	Vector2 Cameraplane = { 0.0f,1.0f };
};

