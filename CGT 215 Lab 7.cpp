// CGT 215 Lab 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 300));
	ball.setRadius(20);
	ball.setVelocity(Vector2f(0.5, 0.5)); // Setting initial velocity
	world.AddPhysicsBody(ball);

	// Floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Left wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 600));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	// Right wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 600));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	// Ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Center box
	PhysicsRectangle centerBox;
	centerBox.setSize(Vector2f(100, 100));
	centerBox.setCenter(Vector2f(400, 300));
	centerBox.setStatic(true);
	world.AddPhysicsBody(centerBox);

	// Counting collisions
	int thudCount(0);
	int bangCount(0);

	// Collision responses
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	centerBox.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		bangCount++;
		cout << "bang " << bangCount << endl;
		if (bangCount >= 3) {
			cout << "Exiting after 3 bangs on the center box" << endl;
			exit(0);
		}
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());

		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color(0, 0, 0));

		window.draw(ball);
		window.draw(floor);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(ceiling);
		window.draw(centerBox);

		window.display();
	}

	return(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
