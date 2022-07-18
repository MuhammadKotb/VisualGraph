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
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Student {
public:
	virtual void func() = 0;
};
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
	tgui::Gui* gui = new tgui::Gui(window);
	gui->loadWidgetsFromFile("UI.txt");
	NodeCollection* nodeCollection = new NodeCollection();

	//nodeCollection->addNode(sf::Vector2f(10.0f, 15.0f));
	//nodeCollection->addNode(sf::Vector2f(10.0f, 15.0f));
	//nodeCollection->addNode(sf::Vector2f(10.0f, 15.0f));
	//nodeCollection->addNode(sf::Vector2f(10.0f, 15.0f));
	//nodeCollection->addNode(sf::Vector2f(10.0f, 15.0f));
	//nodeCollection->addNode(sf::Vector2f(150.0f, 50.0f));
	//nodeCollection->addNode(sf::Vector2f(100.0f, 150.0f));
	EdgeCollection* edgeCollection = new EdgeCollection();

	//edgeCollection->addEdge(nodeCollection->nodes[0], nodeCollection->nodes[1], 50);
	//edgeCollection->addEdge(nodeCollection->nodes[0], nodeCollection->nodes[2], 89);
	//edgeCollection->addEdge(nodeCollection->nodes[2], nodeCollection->nodes[3], 87);
	//edgeCollection->addEdge(nodeCollection->nodes[4], nodeCollection->nodes[6], 10);
	//edgeCollection->addEdge(nodeCollection->nodes[0], nodeCollection->nodes[5], 75);
	//edgeCollection->addEdge(nodeCollection->nodes[1], nodeCollection->nodes[5], 63);
	//edgeCollection->addEdge(nodeCollection->nodes[3], nodeCollection->nodes[4], 90);
	//edgeCollection->addEdge(nodeCollection->nodes[1], nodeCollection->nodes[4], 21);
	//edgeCollection->addEdge(nodeCollection->nodes[5], nodeCollection->nodes[4], 98);


	Graph* graph = new Graph(edgeCollection);
	UserController* userController = new UserController(gui, edgeCollection, nodeCollection, graph);

	OperationController* operationController = new OperationController(gui, graph);




	while (window.isOpen()) 
	{

		sf::Event event;

		while (window.pollEvent(event))
		{
			gui->handleEvent(event);
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
		

		window.clear();
		gui->draw();
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