#include <SFML/Graphics.hpp>
#include "CVPinball.h"
#include "Ball.h"
#include "Bumper.h"
#include "Flipper.h"
#include <vector>
#include <chrono>
#include <thread>

CVPinball::CVPinball() {}

CVPinball::~CVPinball() {}

void CVPinball::playGame() {
	sf::RenderWindow window(sf::VideoMode(400,600), "CV Pinball");

	sf::RectangleShape background(sf::Vector2f(400, 600));

	background.setFillColor(sf::Color(95, 139, 211));

	Ball ball(200, 350, 10);
	ball.setVelo(1,0);
    
    Bumper bumper1(ball, 100, 100, 30);
    Bumper bumper2(ball, 300, 100, 30);
    Bumper bumper3(ball, 200, 250, 30);


    Flipper flipper(ball, sf::Vector2f(100, 550), -1, 3);
    Flipper flipper2(ball, sf::Vector2f(300, 550), 1, 3);
    /*
	std::vector<Obstacle&> obstacles(3);
	obstacles[0] = &bumper1;
	*/
    //bool lflipped = false;
    //bool rflipped = false;
    
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            flipper.flip();
        } else {
            flipper.unflip();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            flipper2.flip();
        } else {
            flipper2.unflip();
        }
    
    
        
        // Bouncing off sides
        float nextx = ball.getCenter().x + ball.getvx();
        float nexty = ball.getCenter().y + ball.getvy();

		if (nextx > (window.getSize().x - ball.getRadius()) or nextx < ball.getRadius()) {
			ball.setvx(-ball.getvx());
		}
        
        if (nexty < ball.getRadius()) {
			ball.setvy(-ball.getvy());
		}

        // Resetting after fall
		if (nexty > (window.getSize().y + ball.getRadius())) {
            ball.setCenter(150,500);
            ball.setVelo(0, 0);
        }

		//Collision Detection
		bumper1.checkCollision();
		bumper2.checkCollision();
		bumper3.checkCollision();
        flipper.checkCollision();
        flipper2.checkCollision();
        
        // Gravity
        float gravity = 10;
        if (ball.getvy() < gravity) ball.setvy(ball.getvy()+1);
        
        //Friction
        float friction = 0.1;
        if (ball.getvx() > 0) {
            ball.setvx(ball.getvx() - friction);
        }
        if (ball.getvy() > 0) {
            ball.setvy(ball.getvy() - friction);
        }

        ball.move();
		window.clear();
		window.draw(background);
		
		window.draw(ball.get());
		/*for (std::vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		{
			window.draw(i.get());
		}*/
		bumper1.draw(window);
        bumper2.draw(window);
        bumper3.draw(window);

		window.draw(flipper.get());
        window.draw(flipper.getLine());
        window.draw(flipper2.get());
        window.draw(flipper2.getLine());

		window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}