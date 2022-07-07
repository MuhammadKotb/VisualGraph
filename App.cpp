#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "MACROS.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Operations.h"


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VisualGraph", sf::Style::Close | sf::Style::Titlebar, settings);

	NodeCollection nodeCollection;
	EdgeCollection edgeCollection;


	nodeCollection.addNode(sf::Vector2f(60.0f, 60.0f));
	nodeCollection.addNode(sf::Vector2f(120.0f, 60.0f));
	nodeCollection.addNode(sf::Vector2f(150.0f, 100.0f));
	nodeCollection.addNode(sf::Vector2f(120.0f, 110.0f));
	nodeCollection.addNode(sf::Vector2f(10.0f, 10.0f));
	nodeCollection.addNode(sf::Vector2f(150.0f, 140.0f));
	nodeCollection.addNode(sf::Vector2f(150.0f, 140.0f));
	nodeCollection.addNode(sf::Vector2f(150.0f, 140.0f));
	nodeCollection.addNode(sf::Vector2f(150.0f, 140.0f));

	edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[1]);
	edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[2]);
	edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[3]);
	edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[4]);
	edgeCollection.addEdge(nodeCollection.nodes[1], nodeCollection.nodes[5]);
	edgeCollection.addEdge(nodeCollection.nodes[1], nodeCollection.nodes[6]);
	edgeCollection.addEdge(nodeCollection.nodes[2], nodeCollection.nodes[7]);
	edgeCollection.addEdge(nodeCollection.nodes[2], nodeCollection.nodes[8]);


	
	Graph* graph = new Graph(edgeCollection);

	
	bool leftclicked = false;
	bool rightClicked = false;
	bool spacePressed = false;
	bool firedThread = false;
	Node* currentNode = nullptr;

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);

			if (!leftclicked)
			{
				for (const auto& node : nodeCollection.nodes)
				{
					leftclicked = node->inNode((sf::Vector2f)pos);
					if (leftclicked)
					{
						currentNode = node;
						break;
					}
				}
			}
			if (leftclicked)
			{
				
				if (pos.x > 0 && pos.x < WINDOW_WIDTH && pos.y > 0 && pos.y < WINDOW_HEIGHT)
				{
					pos.x -= (int)currentNode->getCircleShape().getRadius();
					pos.y -= (int)currentNode->getCircleShape().getRadius();
					currentNode->setPosition((sf::Vector2f)pos);
				}
				
			}
		}
		else
		{
			leftclicked = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			if (!rightClicked)
			{
				for (unsigned int i = 0; i < nodeCollection.nodes.size(); i++)
				{
					if (nodeCollection.nodes[i]->inNode((sf::Vector2f)pos))
					{
						delete nodeCollection.nodes[i];
						nodeCollection.nodes.erase(nodeCollection.nodes.begin() + i);
						rightClicked = true;
						break;
					}
				}
			}
			if (!rightClicked)
			{
				nodeCollection.addNode(sf::Vector2f(60.0f, 60.0f));
				rightClicked = true;
			}
		}
		else
		{
			rightClicked = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			if (!spacePressed)
			{
				if (!firedThread)
				{
					dfsThread = std::thread(BFS, graph);
					firedThread = true;
				}
				spacePressed = true;
			}

		}
		else
		{
			spacePressed = false;
		}
		window.clear();
		for (const auto& node : nodeCollection.nodes)
		{
			window.draw(node->getCircleShape());
			sf::Vector2f nodePos = node->getCircleShape().getPosition();
			const float radius = node->getCircleShape().getRadius();
			node->setTextPosition(sf::Vector2f(nodePos.x + radius / 2 + 3.5f, nodePos.y + radius / 2 - 1.6f));
			window.draw(node->getIdText());
		}

		for (const auto& edge : edgeCollection.edges)
		{
			edge->updatePosition();
			window.draw(edge->getVertexArray());
		}
		window.display();
	}
	if (firedThread)
	{
		dfsThread.join();
	}




	delete (graph);




}