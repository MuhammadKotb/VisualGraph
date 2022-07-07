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
	float weight;
	Edge( Node*  node1,  Node*  node2, float weight);
	~Edge();
	void updatePosition();
	const sf::VertexArray& getVertexArray() const;
	const sf::Text& getWeightText() const;
	const Nodes getNodes() const;


private:
	
	typedef struct Shape {
		sf::VertexArray* line;
		sf::Font* font;
		sf::Text* weightText;
	} Shape;
	
	Shape shape;
	Nodes nodes;
};


struct EdgeCollection
{
	std::vector<Edge*> edges;
	EdgeCollection();
	~EdgeCollection();
	void addEdge(Node* node1, Node* node2, float weight);
};
