/// <summary>
/// author Pete Lowe May 2022
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	std::string getElapsedTime();
	std::string getRemainingTime(int t_duration);
	void setupFontAndText();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_timeMessage; // text used for message on screen
	sf::Clock m_timer; // clock ued to keep track of time
	sf::Clock m_stopWatch; // clock used for delays
	bool m_exitGame; // control exiting game
	bool m_alarmSet{ false }; // true when waiting for alarm
	float m_alarmTime; // duration of alarm timer
};

#endif // !GAME_HPP

