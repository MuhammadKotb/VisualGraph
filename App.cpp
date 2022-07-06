#include <iostream>
#include <SFML/Graphics.hpp>
#include "MACROS.h"
#include "Node.h"
#include "Edge.h"
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VisualGraph", sf::Style::Close | sf::Style::Titlebar, settings);

	NodeCollection nodeCollection;
	EdgeCollection edgeCollection;

	bool leftclicked = false;
	bool rightClicked = false;
	bool spacePressed = false;
	Node* currentNode = nullptr;



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
				pos.x -= (int)currentNode->getCircleShape().getRadius();
				pos.y -= (int)currentNode->getCircleShape().getRadius();
				currentNode->setPosition((sf::Vector2f)pos);
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
				edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[1]);
				edgeCollection.addEdge(nodeCollection.nodes[0], nodeCollection.nodes[2]);
				edgeCollection.addEdge(nodeCollection.nodes[1], nodeCollection.nodes[2]);
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

}