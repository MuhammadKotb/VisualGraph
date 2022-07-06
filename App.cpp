#include <iostream>
#include <SFML/Graphics.hpp>
#include "MACROS.h"
#include "Node.h"
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VisualGraph", sf::Style::Close | sf::Style::Titlebar, settings);



	NodeCollection nodeCollection;


	bool leftclicked = false;
	bool rightClicked = false;
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
				for (int i = 0; i < nodeCollection.nodes.size(); i++)
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
				nodeCollection.addNode(new Node(sf::Vector2f(60.0f, 60.0f)));
				rightClicked = true;
			}
			
		}
		else
		{
			rightClicked = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		for (const auto& node : nodeCollection.nodes)
		{
			window.draw(node->getCircleShape());
		}
		window.display();
	}

}