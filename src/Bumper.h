#ifndef BUMPER_H
#define BUMPER_H

#include "Ball.h"
#include <SFML/Graphics.hpp>

class Bumper {

	Ball& ball;
	sf::CircleShape circ;
    sf::RectangleShape rect;
	float posx;
	float posy;
	float radius;

public:
	Bumper(Ball& b, float x, float y, float r);
	~Bumper();

	sf::Vector2f getCenter();

	void checkCollision();
    
    sf::CircleShape get();
    
    void draw(sf::RenderWindow& wind);

};

#endif // BUMPER_H