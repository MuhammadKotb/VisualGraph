#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include "MACROS.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Operations.h"
#include "UserController.h"

/*	if (!rightClicked)
		{
			for (unsigned int i = 0; i < nodeCollection->nodes.size(); i++)
			{
				if (nodeCollection->nodes[i]->inNode((sf::Vector2f)pos))
				{
					delete nodeCollection->nodes[i];
					nodeCollection->nodes.erase(nodeCollection->nodes.begin() + i);
					rightClicked = true;
					break;
				}
			}
			if (!rightClicked)
			{
				nodeCollection->addNode(sf::Vector2f(60.0f, 60.0f));
				rightClicked = true;
			}
		}*/


int main()
{

	std::atomic<bool> done(true);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VisualGraph", sf::Style::Close | sf::Style::Titlebar, settings);
	sf::RenderTexture edgeRenderer;

	NodeCollection* nodeCollection = new NodeCollection();
	EdgeCollection* edgeCollection = new EdgeCollection();

	
	
	Graph* graph = new Graph(edgeCollection);

	UserController* userController = new UserController(edgeCollection, nodeCollection, graph);
	
	bool spacePressed = false;
	bool enterPressed = false;
	bool firedThread = false;

	std::thread dfsThread;



	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}


		userController->listenNodeMovement(window);
		userController->listenEdgeCreation(window);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			if (!spacePressed && done)
			{
				done = false;
				dfsThread = std::thread([&]() { DFS(graph); done = true; });
				dfsThread.detach();
				spacePressed = true;
			}
		}
		else
		{
			spacePressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{

			if (!enterPressed && done)
			{
				done = false;
				dfsThread = std::thread([&]() { BFS(graph); done = true; });
				dfsThread.detach();
				enterPressed = true;
			}
		}
		else
		{
			enterPressed = false;
		}

		userController->listenNodeCreation(window);

		
		window.clear();
		for (const auto& node : nodeCollection->nodes)
		{
			window.draw(node->getCircleShape());
			sf::Vector2f nodePos = node->getCircleShape().getPosition();
			const float radius = node->getCircleShape().getRadius();
			node->setTextPosition(sf::Vector2f(nodePos.x + radius / 2 + 3.5f, nodePos.y + radius / 2 - 1.6f));
			window.draw(node->getIdText());
		}
		for (const auto& edge : edgeCollection->edges)
		{
			edge->updatePosition();
			window.draw(edge->getVertexArray());
		}
		if (userController->connectingNodes)
		{
			window.draw(userController->createdEdge);
		}
		window.display();
	}

	delete(userController);
	delete (graph);
	delete (edgeCollection);
	delete (nodeCollection);
}