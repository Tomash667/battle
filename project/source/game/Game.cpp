#include "Pch.h"
#include "Core.h"
#include "Game.h"
#include "Render.h"
#include "Window.h"

Game::Game() : render(nullptr), window(nullptr)
{

}

Game::~Game()
{
	delete render;
	delete window;
}

void Game::Go()
{
	try
	{
		window = new Window(Int2(1024, 768), Window::Windowed);
		window->SetTitle("Unnamed battle game");
		window->Init();

		render->Init(window->GetHandle());
	}
	catch(cstring /*err*/)
	{
		// game initialization failed
		return;
	}

	while(window->Tick())
		render->Draw();
}
