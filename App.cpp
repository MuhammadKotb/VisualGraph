#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include "MACROS.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Operations.h"

bool finished = false;

void foo()
{
	log("in foo");
	finished = true;
}

void bar()
{
	log("in bar");
}


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

	
	bool leftclicked = false;
	bool rightClicked = false;
	bool spacePressed = false;
	bool enterPressed = false;
	bool firedThread = false;
	bool connectingNodes = false;
	bool mPressed = false;
	Node* currentNode = nullptr;

	std::thread dfsThread;

	Node* node1 = nullptr;
	Node* node2 = nullptr;
	sf::VertexArray edge(sf::Lines, 2);

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
				for (const auto& node : nodeCollection->nodes)
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

			if (!rightClicked)
			{
				for (unsigned int i = 0; i < nodeCollection->nodes.size(); i++)
				{
					if (nodeCollection->nodes[i]->inNode((sf::Vector2f)pos))
					{
						node1 = nodeCollection->nodes[i];
						rightClicked = true;
						break;
					}
				}
			}
			if (node1)
			{
				connectingNodes = true;
				edge[0].position = node1->getCenter();
				edge[1].position = (sf::Vector2f)pos;
			}
		}
		else
		{
			if (rightClicked)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);

				if (node1)
				{
					for (unsigned int i = 0; i < nodeCollection->nodes.size(); i++)
					{
						if (nodeCollection->nodes[i]->inNode((sf::Vector2f)pos))
						{
							node2 = nodeCollection->nodes[i];
							rightClicked = true;
							break;
						}
					}
				}
				if (node1 && node2)
				{
					if (node1 != node2)
					{
						edgeCollection->addEdge(node1, node2);
					
					}
				}
			}
			node1 = nullptr;
			node2 = nullptr;
			connectingNodes = false;
			rightClicked = false;
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			if (!mPressed)
			{
				nodeCollection->addNode(sf::Vector2f(60.0f, 60.0f));
				mPressed = true;
			}
		}
		else
		{
			mPressed = false;
		}
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
		if (connectingNodes)
		{
			window.draw(edge);
		}
		window.display();
	}
	
	delete (graph);
	delete (edgeCollection);
	delete (nodeCollection);
}