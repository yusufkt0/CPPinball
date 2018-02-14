#include "Flipper.h"
#include <cmath>
#include <iostream>
#include "Collision.h"

Flipper::Flipper(Ball& b, sf::Vector2f o, float f, float size) : ball(b) {
	origin = o;
	side = f;

	

	shape = sf::ConvexShape(5);
    //shape.setOrigin(o);
    pointA = sf::Vector2f(0,-(5  * size));
    pointB = sf::Vector2f(-(25 * side * size),(8  * size));
	shape.setPoint(0, pointA);
	shape.setPoint(1, sf::Vector2f( (5  * side * size),  -(5  * size)));
	shape.setPoint(2, sf::Vector2f( (5  * side * size),  0));
	shape.setPoint(3, sf::Vector2f(-(20 * side * size),  (10 * size)));
	shape.setPoint(4, pointB);
	shape.setPoint(5, sf::Vector2f(-(20 * side * size),  (6  * size)));
    shape.setPosition(o);
    /*{
    line = sf::VertexArray(sf::LineStrip, 2);
    line[0].position = pointA;
    line[0].color = sf::Color::Red;
    line[1].position = pointB;
    line[0].color = sf::Color::Red;
    }*/
    pointA.x += o.x;
    pointA.y += o.y;
    pointB.x += o.x;
    pointB.y += o.y;
    
    //std::cout << "A " << pointA.x << " " << pointA.y << std::endl;
    //std::cout << "B " << pointB.x << " " << pointB.y << std::endl;
/*
	if (f == 1) {
		shape.setOrigin(25, 5);
        shape.setPosition(25, 0);
	} else {
		shape.setOrigin(5, 5);
        shape.setPosition(5, 0);
	}
*/
	shape.setFillColor(sf::Color(90,90,90));
	shape.setOutlineColor(sf::Color::Black);
}

Flipper::~Flipper() {}

sf::VertexArray Flipper::getLine() {
    return line;
}

void Flipper::rotate(float f) {
    float g = f * side;
    shape.rotate(g);
    g = g * (3.14159265358979/180);
	float newAx = std::cos(g) * (pointA.x - origin.x) - std::sin(g) * (pointA.y - origin.y) + origin.x;
    float newAy = std::sin(g) * (pointA.x - origin.x) + std::cos(g) * (pointA.y - origin.y) + origin.y;
    float newBx = std::cos(g) * (pointB.x - origin.x) - std::sin(g) * (pointB.y - origin.y) + origin.x;
    float newBy = std::sin(g) * (pointB.x - origin.x) + std::cos(g) * (pointB.y - origin.y) + origin.y;
    pointA.x = newAx;
    pointA.y = newAy;
    pointB.x = newBx;
    pointB.y = newBy;
    //std::cout << "A " << pointA.x << " " << pointA.y << std::endl;
    //std::cout << "B " << pointB.x << " " << pointB.y << std::endl;
}

void Flipper::flip() {
    if (position < 45) {
        rotate(speed);
        position+=speed;
    }
}

void Flipper::unflip() {
    if (position > 0) {
        rotate(-speed);
        position-=speed;
    }
}

float signum(float f) {
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 0;
}

float Flipper::speedAt(sf::Vector2f bcenter) {
    if (position == 0 || position == 45) {
        return 0;
    } else {
        float dx = origin.x - bcenter.x;
        float dy = origin.y - bcenter.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        return (speed/360.) * 2 * 3.14159265358979 * distance;
    }
}

void Flipper::checkCollision() {
	sf::Vector2f offA = sf::Vector2f(pointA.x, pointA.y-ball.getRadius()); /// Wrong
	sf::Vector2f offB = sf::Vector2f(pointB.x, pointB.y-ball.getRadius()); /// Wrong
	sf::Vector2f bcenter = ball.getCenter();

    float nextx = bcenter.x + ball.getvx();
    float nexty = bcenter.y + ball.getvy();

	float dx = offB.x - offA.x;
	float dy = offB.y - offA.y;
	float distance = std::sqrt(dx * dx + dy * dy);
	float ux = (-dy) / distance * side;
    float uy = dx / distance * side;
    float px = nextx - offA.x;
    float py = nexty - offA.y;
    float dotproduct= (px*ux) + (py*uy);
    
     

    if(!ballIsUnder && dotproduct <= 0 && ((offA.x <= nextx && nextx <= offB.x && side == -1) || (offB.x <= nextx && nextx <= offA.x && side == 1))) {
        ballIsUnder = true;
        //std::cout << " bx " << bcenter.x << " by " << bcenter.y;
        //std::cout << " Ax " << offA.x << " Ay " << offA.y;
        //std::cout << " Bx " << offB.x << " By " << offB.y;
    	//float ux2 = uy;
    	//float uy2 = -ux;
    	//float dotproduct2 = (px*ux2) + (py*uy2);
        //std::cout << " " << dotproduct2 << std::endl;
        px = ball.getCenter().x - offA.x;
        py = ball.getCenter().y - offA.y;
        dotproduct= (px*ux) + (py*uy);
        while (dotproduct > 0) {
            float nx = ball.getCenter().x + signum(ball.getvx());
            float ny = ball.getCenter().y + signum(ball.getvy());
            ball.setCenter(nx,ny);
            px = ball.getCenter().x - offA.x;
            py = ball.getCenter().y - offA.y;
            dotproduct= (px*ux) + (py*uy);
        }
    	if ((side == -1 && offA.x <= bcenter.x && bcenter.x <= offB.x) || (side == 1 && offB.x <= bcenter.x && bcenter.x <= offA.x)) { //dotproduct2 && dotproduct2 <= 25) {
    		float projectv = ball.getvx() * ux + ball.getvy() * uy;
	        float projectx = projectv * ux;
	        float projecty = projectv * uy;
	        projectx = ball.getvx() - 2 * projectx + 2 * speedAt(ball.getCenter()) * ux;
	        projecty = ball.getvy() - 2 * projecty + 2 * speedAt(ball.getCenter()) * uy;
	        ball.setVelo(projectx, projecty);
            std::cout << speedAt(ball.getCenter()) << " " << position << " " << projectx << " " << projecty << " " << ux << " " << uy << std::endl;
    	}
    } else {
        ballIsUnder = false;
    }
}
/*
bool Flipper::checkCollision() {
    sf::Vector2f offA = sf::Vector2f(pointA.x, pointA.y-ball.getRadius()); /// Wrong
    sf::Vector2f offB = sf::Vector2f(pointB.x, pointB.y-ball.getRadius()); /// Wrong
    sf::Vector2f bcenter = ball.getCenter();

    //float nextx = bcenter.x + ball.getvx();
    //float nexty = bcenter.y + ball.getvy();

    float dx = offB.x - offA.x;
    float dy = offB.y - offA.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float ux = (-dy) / distance * side;
    float uy = dx / distance * side;
    float px = bcenter.x - offA.x;
    float py = bcenter.y - offA.y;
    float dotproduct= (px*ux) + (py*uy);
    
     

    if(dotproduct <= 0 && dotproduct > -10 && ((side == -1 && offA.x <= bcenter.x && bcenter.x <= offB.x) || (side == 1 && offB.x <= bcenter.x && bcenter.x <= offA.x))) {
        return true;
    } else {
        return false;
    }
}

void Flipper::collide() {
    float dx = offB.x - offA.x;
    float dy = offB.y - offA.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float ux = (-dy) / distance * side;
    float uy = dx / distance * side;
    float projectv = ball.getvx() * ux + ball.getvy() * uy;
    float projectx = projectv * ux;
    float projecty = projectv * uy;
    projectx = ball.getvx() - 2 * projectx;
    projecty = ball.getvy() - 2 * projecty;
    ball.setVelo(projectx, projecty);
}
*/
/*
void Flipper::checkCollision() {
    
    if (Collision::BoundingBoxTest(ball.get(), shape)) {
        sf::Vector2f offA = sf::Vector2f(pointA.x, pointA.y-ball.getRadius()); /// Wrong
        sf::Vector2f offB = sf::Vector2f(pointB.x, pointB.y-ball.getRadius()); /// Wrong
        sf::Vector2f bcenter = ball.getCenter();

        //bcenter.x += ball.getvx();
        //bcenter.y += ball.getvy();

        float dx = offB.x - offA.x;
        float dy = offB.y - offA.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float ux = (-dy) / distance * side;
        float uy = dx / distance * side;
        float projectv = ball.getvx() * ux + ball.getvy() * uy;
        float projectx = projectv * ux;
        float projecty = projectv * uy;
        projectx = ball.getvx() - 2 * projectx;
        projecty = ball.getvy() - 2 * projecty;
        ball.setVelo(projectx, projecty);
    }
}
*/

sf::ConvexShape Flipper::get() { return shape;}