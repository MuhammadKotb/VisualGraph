#pragma once
#include <SFML/Graphics.hpp>
#include "MACROS.h"
#include <vector>
class Node
{
public:
	Node(sf::Vector2f position);
	~Node();
	const sf::CircleShape& getCircleShape() const;
	void setPosition(sf::Vector2f position);
	void setRadius(float radius);
	bool inNode(sf::Vector2f position) const;

private:
	sf::CircleShape* circle;


};


struct NodeCollection
{
	std::vector<Node*> nodes;
	void addNode(Node* node);
	NodeCollection();
	~NodeCollection();
};

