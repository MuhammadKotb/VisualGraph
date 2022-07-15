#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "MACROS.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Operations.h"
#include "UserController.h"
#include "OperationController.h"

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

	sf::ContextSettings settings;

	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VisualGraph", sf::Style::Close | sf::Style::Titlebar, settings);

	NodeCollection* nodeCollection = new NodeCollection();

	EdgeCollection* edgeCollection = new EdgeCollection();

	Graph* graph = new Graph(edgeCollection);

	UserController* userController = new UserController(edgeCollection, nodeCollection, graph);

	OperationController* operationController = new OperationController(graph);



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


		userController->controlNodeMovement(window);
		userController->controlEdgeCreation(window);
		userController->controlNodeCreation(window);
		
		operationController->controlDFS();
		operationController->controlBFS();
		window.clear();
		window.draw(*nodeCollection);
		window.draw(*edgeCollection);
		if (userController->connectingNodes)
		{
			window.draw(userController->createdEdge);
		}
		window.display();
	}

	delete(userController);
	delete(operationController);
	delete (graph);
	delete (edgeCollection);
	delete (nodeCollection);
}