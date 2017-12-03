#pragma once

class Render;
class Window;

class Game
{
public:
	Game();
	~Game();
	void Go();

private:
	Render* render;
	Window* window;
};
