#pragma once
#include <SFML/Graphics.hpp>
#include "MACROS.h"
#include <vector>
class Node
{
public:
	int id = -1;
	Node(sf::Vector2f position, int id);
	~Node();
	const sf::CircleShape& getCircleShape() const;
	const sf::Text& getIdText() const;
	void setPosition(sf::Vector2f position);
	void setRadius(float radius);
	void setTextPosition(sf::Vector2f position);
	bool inNode(sf::Vector2f position) const;


private:
	typedef struct Shape {
		sf::CircleShape* circle = nullptr;
		sf::Text* idText = nullptr;
		sf::Font* font = nullptr;
	} Shape;

	Shape shape;
};


struct NodeCollection
{
	std::vector<Node*> nodes;
	void addNode(sf::Vector2f position);
	NodeCollection();
	~NodeCollection();
};

