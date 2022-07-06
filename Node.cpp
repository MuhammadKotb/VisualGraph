#include "Node.h"



Node::Node(sf::Vector2f position)
{
	this->circle = new sf::CircleShape();
	this->circle->setPosition(position);
	this->circle->setRadius(NODE_RADIUS);
	this->circle->setFillColor(BLACK);
	this->circle->setOutlineThickness(NODE_THICKNESS);
	this->circle->setOutlineColor(RED);
}

Node::~Node()
{
	delete (this->circle);
}

const sf::CircleShape& Node::getCircleShape() const
{
	return *this->circle;
}

void Node::setPosition(sf::Vector2f position)
{
	this->circle->setPosition(position);
}


void Node::setRadius(float radius)
{
	this->circle->setRadius(radius);
}

bool Node::inNode(sf::Vector2f position) const
{
	return position.x > this->circle->getPosition().x && position.x < this->circle->getPosition().x + this->circle->getRadius() * 2
		&& position.y > this->circle->getPosition().y && position.y < this->circle->getPosition().y + this->circle->getRadius() * 2;
}

NodeCollection::NodeCollection()
{

}
NodeCollection::~NodeCollection()
{
	for (int i = 0; i < this->nodes.size(); i++)
	{
		delete (nodes[i]);
	}
}


void NodeCollection::addNode(Node* node)
{
	this->nodes.push_back(node);
}
