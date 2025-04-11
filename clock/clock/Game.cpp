/// <summary>
/// author Pete Lowe May 2022
/// you need to change the above line or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
#ifdef _DEBUG
			render(); // want to debug drawing while stepping through code
#endif // _DEBUG

		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Num0 <= t_event.key.code && sf::Keyboard::Num9 >= t_event.key.code && !m_alarmSet)
	{
		m_alarmTime = static_cast<float>(t_event.key.code - sf::Keyboard::Num0);
		m_stopWatch.restart();
		m_alarmSet = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (t_deltaTime.asMilliseconds() != 16)
	{
		std::cout << "time warp" << std::endl; // expecting 60 fps of action
	}
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_alarmSet)
	{
		if (m_stopWatch.getElapsedTime().asSeconds() > m_alarmTime)
		{
			m_alarmSet = false;
		}
	}
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color{ 90,110,200,255 });
	m_timeMessage.setString(getElapsedTime()); // update the time message to the current time
	m_window.draw(m_timeMessage);	// elapsed
	m_timeMessage.move(sf::Vector2f{ 0.0f,40.0f });
	m_timeMessage.setString(getRemainingTime(120));
	m_window.draw(m_timeMessage); // remaining

	m_timeMessage.move(sf::Vector2f{ 0.0f,40.0f });
	if (m_alarmSet)
	{
		m_timeMessage.setString(std::to_string(static_cast<int>(m_alarmTime)) + " second timer active");
	}
	else
	{
		m_timeMessage.setString("Press a number on keyboard to set delay timer");
	}
	m_window.draw(m_timeMessage); // remaining
	m_timeMessage.move(sf::Vector2f{ 0.0f,-40.0f }); // return to orignal location


	m_timeMessage.move(sf::Vector2f{ 0.0f,-40.0f }); // return to orignal location
	m_window.display();
}

std::string Game::getElapsedTime()
{
	std::string elapsed;
	int seconds;
	int minutes;
	seconds = static_cast<int>( m_timer.getElapsedTime().asSeconds());
	minutes = seconds / 60;
	seconds = seconds % 60;
	if (seconds > 9) // add leading zero
	{
		elapsed = "Time elasped -> " + std::to_string(minutes) + ":" + std::to_string(seconds);
	}
	else
	{
		elapsed = "Time elapsed -> " + std::to_string(minutes) + ":0" + std::to_string(seconds);
	}
	return elapsed;
}

std::string Game::getRemainingTime(int t_duration)
{
	std::string remaining;
	int seconds;
	int minutes;
	seconds = t_duration - static_cast<int>(m_timer.getElapsedTime().asSeconds());
	minutes = seconds / 60;
	seconds = seconds % 60;
	if (seconds > 9) // add leading zero
	{
		remaining = "Time remaining -> " + std::to_string(minutes) + ":" + std::to_string(seconds);
	}
	else
	{
		remaining = "Time remaining -> " + std::to_string(minutes) + ":0" + std::to_string(seconds);
	}
	return remaining;
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_timeMessage.setFont(m_ArialBlackfont);
	m_timeMessage.setString("Time");
	m_timeMessage.setPosition(40.0f, 20.0f);
	m_timeMessage.setCharacterSize(25U);
	m_timeMessage.setOutlineColor(sf::Color::Black);
	m_timeMessage.setFillColor(sf::Color::White);
	m_timeMessage.setOutlineThickness(1.0f);

}


