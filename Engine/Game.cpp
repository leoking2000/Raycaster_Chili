/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float deltaTime = ft.Mark();

	player.Update(wnd.kbd, deltaTime);

}

void Game::ComposeFrame()
{
	Vector2 playerPos = player.Position();
	Vector2 playerDir = player.Direction();

	Vector2 gfxPlayerPos = playerPos * 10;                 // player pos
	Vector2 gfxPlayerDir = (playerPos + playerDir) * 10;    //player dir

	// ray casting

	Vector2 Cameraplane = player.Plane();

	for (int x = 0; x < gfx.ScreenWidth; x++)
	{
		float cameraX = 2 * x / (float)gfx.ScreenWidth - 1;

		Vector2 rayDir(playerDir + (Cameraplane * cameraX));

		float sideDistX;
		float sideDistY;
		float deltaDistX = std::abs(1 / rayDir.x);
		float deltaDistY = std::abs(1 / rayDir.y);
		int stepX;
		int stepY;
		float perpWallDist;

		bool hit = false; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		Vector2 hitPos((int)playerPos.x, (int)playerPos.y);

		//calculate step and initial sideDist
		if (rayDir.x < 0)
		{
			stepX = -1;
			sideDistX = (playerPos.x - (int)playerPos.x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = ((int)playerPos.x + 1.0 - playerPos.x) * deltaDistX;
		}
		if (rayDir.y < 0)
		{
			stepY = -1;
			sideDistY = (playerPos.y - (int)playerPos.y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = ((int)playerPos.y + 1.0 - playerPos.y) * deltaDistY;
		}

		while (!hit)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				hitPos.x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				hitPos.y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (level.Get(hitPos.x, hitPos.y) != '.') hit = true;

		}

		if (side == 0)
		{
			perpWallDist = (hitPos.x - playerPos.x + (1 - stepX) / 2) / rayDir.x;
		}
		else 
		{
			perpWallDist = (hitPos.y - playerPos.y + (1 - stepY) / 2) / rayDir.y;
		}


		//Calculate height of line to draw on screen
		int lineHeight = (int)(gfx.ScreenWidth / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + gfx.ScreenWidth / 3;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + gfx.ScreenWidth / 3;
		if (drawEnd >= gfx.ScreenWidth) drawEnd = gfx.ScreenWidth - 1;

		Color color;
		switch (level.Get(hitPos.x,hitPos.y))
		{
		case '#':  color = Colors::White; break; 
		case '1':  color = Colors::Green; break; 
		case '2':  color = Colors::Red;   break; 
		case '3':  color = Colors::Blue;  break; 
		default: color = Colors::Magenta; break; 
		}

		if (side == 0)
		{
			gfx.DrawLine(x, drawStart, x, drawEnd, color);
		}
		else {
			gfx.DrawLine(x, drawStart, x, drawEnd, Color(color.GetR() / 2,
														 color.GetG() / 2,
														 color.GetB() / 2));
		}

	}

	if (view2D)
	{
		// Draw map
		for (int yMap = 0; yMap < level.GetHeight(); yMap++)
		{
			for (int xMap = 0; xMap < level.GetWidth(); xMap++)
			{
				if (level.Get(xMap, yMap) != '.')
				{
					gfx.DrawRect(xMap * 10, yMap * 10, 9, 9, Colors::Cyan);
				}

			}
		}
		// Draw player
		gfx.DrawCircle((int)gfxPlayerPos.x, (int)gfxPlayerPos.y, 2, Colors::Red);                  
		gfx.DrawLine(gfxPlayerPos.x, gfxPlayerPos.y, gfxPlayerDir.x, gfxPlayerDir.y, Colors::Red); 

	}

}

