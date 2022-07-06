#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.h"
class Edge
{
public:

	Edge(const Node* node1, const Node* node2);
	~Edge();
	void updatePosition();
	const sf::VertexArray& getVertexArray() const;


private:
	
	typedef struct Nodes {
		const Node* node1 = nullptr;
		const Node* node2 = nullptr;
	} Nodes;

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
	void addEdge(const Node* node1, const Node* node2);
};
