#include "Game.hpp"
#include "SplashState.hpp"
#include <Windows.h>
#include "b2GLDraw.h"

namespace KStudio
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height, 32), title, sf::Style::Close | sf::Style::Fullscreen); // Creates the Window

		//Helps to move the SFML window to my second monitor
		_data->window.setPosition(sf::Vector2i(0, 0));
		MONITORINFO mi = { sizeof(mi) };
		HWND hwnd = _data->window.getSystemHandle();
		// get the coordinates of the monitor the window is currently in
		GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi);
		// move the window
		SetWindowPos(hwnd, HWND_TOP,  mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,
		mi.rcMonitor.bottom - mi.rcMonitor.top,SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		_data->window.setMouseCursorGrabbed(true); //Makes the mouse restricted to the game window only

		_data->machine.AddState(StateRef(new SplashState(this->_data))); // Beginning state is the splash state

		//Initalises ans handles the debug rendering of the bodies
		
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		//flags += b2Draw::e_jointBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
		_data->fooDrawInstance.SetFlags(flags);

		_data->game_Start = false;

		this->Run(); // Runs the main game 
	}

	void Game::Run()
	{

		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput(); //Hnadles the Input
				this->_data->machine.GetActiveState()->Update(dt); //Hnadles the game updating each frame

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			
			
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}
