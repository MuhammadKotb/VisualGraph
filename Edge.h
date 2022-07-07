#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.h"

typedef struct Nodes {
	Node* node1 = nullptr;
	Node* node2 = nullptr;
} Nodes;

class Edge
{
public:

	Edge( Node*  node1,  Node*  node2);
	~Edge();
	void updatePosition();
	const sf::VertexArray& getVertexArray() const;
	const Nodes getNodes() const;


private:
	
	typedef struct Shape {
		sf::VertexArray* line;
	} Shape;

	Shape shape;
	Nodes nodes;
};


struct EdgeCollection
{
	std::vector<Edge*> edges;
	EdgeCollection();
	~EdgeCollection();
	void addEdge( Node*  node1,  Node*  node2);
};
