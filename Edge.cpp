#include "Edge.h"


Edge::Edge(Node* node1, Node* node2, float weight = 1.0f) : weight(weight)
{
	this->nodes.node1 = node1;
	this->nodes.node2 = node2;

	this->shape.line = new sf::VertexArray(sf::Lines, 2);
	this->shape.font = new sf::Font();
	this->shape.font->loadFromFile(FIRA_CODE_FONT);
	this->shape.weightText = new sf::Text();
	this->shape.weightText->setFont(*this->shape.font);
	this->shape.weightText->setCharacterSize(EDGE_WEIGHT_FONT_SIZE);
	this->shape.weightText->setFillColor(WHITE);

	(*this->shape.line)[0].position = node1->getCenter();
	(*this->shape.line)[1].position = node2->getCenter();

	sf::Vector2f midPoint = sf::Vector2f((node1->getCenter().x + node2->getCenter().x) / 2, (node1->getCenter().y + node2->getCenter().y) / 2);
	this->shape.weightText->setString(std::to_string((int)this->weight));
	this->shape.weightText->setPosition(midPoint);
	
	for (unsigned int i = 0; i < 2; i++)
	{
		(*this->shape.line)[i].color = WHITE;
	}
}

Edge::~Edge()
{
	delete (this->shape.line);
	delete (this->shape.font);
	delete (this->shape.weightText);
}


void Edge::updatePosition()
{

	(*this->shape.line)[0].position = this->nodes.node1->getCenter();
	(*this->shape.line)[1].position = this->nodes.node2->getCenter();
	sf::Vector2f midPoint = sf::Vector2f((this->nodes.node1->getCenter().x + this->nodes.node2->getCenter().x) / 2, (this->nodes.node1->getCenter().y + this->nodes.node2->getCenter().y) / 2);
	this->shape.weightText->setPosition(midPoint);
}

const Nodes Edge::getNodes() const
{
	return this->nodes;
}

const sf::VertexArray& Edge::getVertexArray() const
{
	return *this->shape.line;
}

const sf::Text& Edge::getWeightText() const
{
	return *this->shape.weightText;
}
EdgeCollection::EdgeCollection()
{
	
}

EdgeCollection::~EdgeCollection()
{
	for (unsigned int i = 0; i < this->edges.size(); i++)
	{
		delete (this->edges[i]);
	}
}

void EdgeCollection::addEdge(Node* node1, Node* node2, float weight = 1.0f)
{
	Edge* edge = new Edge(node1, node2, weight);
	this->edges.push_back(edge);
}
