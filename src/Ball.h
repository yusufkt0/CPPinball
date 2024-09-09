#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {

	sf::CircleShape circ;
    float vx;
    float vy;

public:
	Ball(float x, float y, float r);
	~Ball();

	sf::CircleShape get();
    
	void setCenter(float x, float y);
	sf::Vector2f getCenter();
    
    void setvx(float f);
    float getvx();
    void setvy(float f);
    float getvy();
    void setVelo(float xf, float yf);
    
    void move();
    void unmove();

    float getRadius();

};


#endif // BALL_H
