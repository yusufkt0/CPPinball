#include "Ball.h"
#include <iostream>
#include <chrono>
#include <thread>

Ball::Ball(float x, float y, float r) {
    circ.setRadius(r);
    //circ.setPosition(200,300);
    circ.setFillColor(sf::Color(90,90,90));
    circ.setOutlineColor(sf::Color::Black);
    setCenter(x,y);
    //std::cout << circ.getOrigin().x << " " << circ.getOrigin().y << std::endl;
    vx = 0;
    vy = 0;
}

Ball::~Ball() {}

sf::CircleShape Ball::get() {
	return circ;
}

void Ball::setCenter(float x, float y) {
    //std::cout << "setCenter" << std::endl;
	float r = circ.getRadius();
	circ.setPosition(x-r, y-r);
}

sf::Vector2f Ball::getCenter() {
	float r = circ.getRadius();
	sf::Vector2f p = circ.getPosition();
	return sf::Vector2f(p.x + r, p.y + r);
}

void Ball::setvx(float f) {
    vx=f;
}

float Ball::getvx() {
    return vx;
}

void Ball::setvy(float f) {
    vy=f;
}

float Ball::getvy() {
    return vy;
}

void Ball::setVelo(float xf, float yf) {
    vx = xf;
    vy = yf;
}

void Ball::move() {
	circ.move(vx, vy);
}

void Ball::unmove() {
    circ.move(-vx, -vy);
}

float Ball::getRadius() {
    return circ.getRadius();
}


