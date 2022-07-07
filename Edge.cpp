#include "Edge.h"


Edge::Edge( Node*  node1,  Node*  node2)
{
	this->nodes.node1 = node1;
	this->nodes.node2 = node2;

	this->shape.line = new sf::VertexArray(sf::Lines, 2);



	(*this->shape.line)[0].position = node1->getCenter();
	(*this->shape.line)[1].position = node2->getCenter();
	

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

	(*this->shape.line)[0].position = this->nodes.node1->getCenter();
	(*this->shape.line)[1].position = this->nodes.node2->getCenter();
}

const Nodes Edge::getNodes() const
{
	return this->nodes;
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

void EdgeCollection::addEdge(Node* node1, Node* node2)
{
	Edge* edge = new Edge(node1, node2);
	this->edges.push_back(edge);
}
