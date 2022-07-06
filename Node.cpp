#include "Node.h"

Node::Node(sf::Vector2f position, int id) : id(id)
{
	this->shape.circle = new sf::CircleShape();
	this->shape.circle->setPosition(position);
	this->shape.circle->setRadius(NODE_RADIUS);
	this->shape.circle->setFillColor(BLACK);
	this->shape.circle->setOutlineThickness(NODE_THICKNESS);
	this->shape.circle->setOutlineColor(RED);
	this->shape.font = new sf::Font();
	this->shape.font->loadFromFile(FIRA_CODE_FONT);
	this->shape.idText = new sf::Text();
	this->shape.idText->setFont(*this->shape.font);
	this->shape.idText->setFillColor(WHITE);
	this->shape.idText->setCharacterSize(NODE_FONT_SIZE);
	this->shape.idText->setString(std::to_string(id));
}	

Node::~Node()
{
	delete (this->shape.circle);
	delete (this->shape.idText);
	delete (this->shape.font);
}

const sf::CircleShape& Node::getCircleShape() const
{
	return *this->shape.circle;
}

const sf::Text& Node::getIdText() const
{
	return *this->shape.idText;
}
void Node::setPosition(sf::Vector2f position)
{
	this->shape.circle->setPosition(position);
}


void Node::setRadius(float radius)
{
	this->shape.circle->setRadius(radius);
}

void Node::setTextPosition(sf::Vector2f position)
{
	this->shape.idText->setPosition(position);
}

bool Node::inNode(sf::Vector2f position) const
{
	return position.x > this->shape.circle->getPosition().x && position.x <this->shape.circle->getPosition().x + this->shape.circle->getRadius() * 2
		&& position.y > this->shape.circle->getPosition().y && position.y < this->shape.circle->getPosition().y + this->shape.circle->getRadius() * 2;
}

NodeCollection::NodeCollection()
{

}
NodeCollection::~NodeCollection()
{
	for (unsigned int i = 0; i < this->nodes.size(); i++)
	{
		delete (nodes[i]);
	}
}


void NodeCollection::addNode(sf::Vector2f position)
{
	Node* node = new Node(position, this->nodes.size());
	this->nodes.push_back(node);
}
