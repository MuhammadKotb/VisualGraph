#include "Edge.h"


Edge::Edge(const Node* node1, const Node* node2)
{
	this->nodes.node1 = node1;
	this->nodes.node2 = node2;

	this->shape.line = new sf::VertexArray(sf::Lines, 2);

	sf::Vector2f node1Pos = node1->getCircleShape().getPosition();
	sf::Vector2f node2Pos = node2->getCircleShape().getPosition();
	const float node1Radius = node1->getCircleShape().getRadius();
	const float node2Radius = node2->getCircleShape().getRadius();
	const float centerX1 = node1Pos.x + node1Radius;
	const float centerY1 = node1Pos.y + node1Radius;
	const float centerX2 = node2Pos.x + node2Radius;
	const float centerY2 = node2Pos.y + node2Radius;

	(*this->shape.line)[0].position = sf::Vector2f(centerX1, centerY1);
	(*this->shape.line)[1].position = sf::Vector2f(centerX2, centerY2);
	

	for (unsigned int i = 0; i < 2; i++)
	{
		(*this->shape.line)[i].color = WHITE;
	}
}

Edge::~Edge()
{
	delete (this->shape.line);
}


void Edge::updatePosition()
{
	sf::Vector2f node1Pos = this->nodes.node1->getCircleShape().getPosition();
	sf::Vector2f node2Pos = this->nodes.node2->getCircleShape().getPosition();
	const float node1Radius = this->nodes.node1->getCircleShape().getRadius();
	const float node2Radius = this->nodes.node2->getCircleShape().getRadius();

	const float centerX1 = node1Pos.x + node1Radius;
	const float centerY1 = node1Pos.y + node1Radius;
	const float centerX2 = node2Pos.x + node2Radius;
	const float centerY2 = node2Pos.y + node2Radius;

	(*this->shape.line)[0].position = sf::Vector2f(centerX1, centerY1);
	(*this->shape.line)[1].position = sf::Vector2f(centerX2, centerY2);

}

const sf::VertexArray& Edge::getVertexArray() const
{
	return *this->shape.line;
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

void EdgeCollection::addEdge(const Node* node1, const Node* node2)
{
	Edge* edge = new Edge(node1, node2);
	this->edges.push_back(edge);
}
