#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Obstacle {


public:
    Ball ball;
	Obstacle(Ball b) {
		ball = b;
	}

	virtual void checkCollision() = 0;
	virtual sf::CircleShape get() = 0;
};

#endif // OBSTACLE_H