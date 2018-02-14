#ifndef FLIPPER_H
#define FLIPPER_H

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Flipper {
    
    Ball& ball;
	sf::ConvexShape shape;
	sf::Vector2f origin;
	float side;
	sf::Vector2f pointA;
	sf::Vector2f pointB;
    float position = 0;
    float speed = 15;
    bool ballIsUnder= false;
    sf::VertexArray line;
public:
	Flipper(Ball& b, sf::Vector2f o, float f, float size);
	~Flipper();

    sf::VertexArray getLine();
    void rotate(float f);
	void flip();
    void unflip();
    
    float speedAt(sf::Vector2f bcenter);

    void checkCollision();
    //void collide();

	sf::ConvexShape get();

};

#endif // FLIPPER_H