#include "Bumper.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Bumper::Bumper(Ball& b, float x, float y, float r) : ball(b) {

    circ.setRadius(r);
    circ.setFillColor(sf::Color(211, 95, 95));
    circ.setPosition(x-r, y-r);
    
    rect.setSize(sf::Vector2f(r,r));
    rect.setFillColor(sf::Color(230,230,230));
    rect.setPosition(x-r/2, y-r/2);
    
    posx = x;
    posy = y;
    radius = r;
}

Bumper::~Bumper() {}

sf::Vector2f Bumper::getCenter() {
	float r = circ.getRadius();
	sf::Vector2f p = circ.getPosition();
	return sf::Vector2f(p.x + r, p.y + r);
}

void Bumper::checkCollision() {
	sf::Vector2f p1 = getCenter();
	sf::Vector2f p2 = ball.getCenter();
	p2.x += ball.getvx();
	p2.y += ball.getvy();
    float dx = (p2.x - p1.x);
    float dy = (p2.y - p1.y);
    float distance = std::sqrt(dx * dx + dy * dy);
    
	if( distance < radius + ball.getRadius()) {
        //std::cout << "colliding" << std::endl;
        float ux = dx / distance;
        float uy = dy / distance;
        float projectv = ball.getvx() * ux + ball.getvy() * uy;
        float px = projectv * ux;
        float py = projectv * uy;
        px = -(2 * px - ball.getvx());
        py = -(2 * py - ball.getvy());
        ball.setVelo(px, py);
    }
}

sf::CircleShape Bumper::get() { return circ;}

void Bumper::draw(sf::RenderWindow& wind) {
    wind.draw(circ);
    //std::cout << "drawing" << std::endl;
    wind.draw(rect);
}