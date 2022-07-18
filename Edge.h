#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.h"

struct Arrow : public sf::Drawable {
	float x0, x1, y0, y1;
	sf::VertexArray halfArrow;
	sf::VertexArray halfArrow2;
	Arrow(float x0, float y0, float x1, float y1);
	Arrow();
	~Arrow();
	void update(float x0, float y0, float x1, float y1);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


double getLineCircleIntersection(double x0, double y0, double x1, double y1, double centerX, double centerY, double radius);
sf::Vector2f pointOnVector(double x0, double y0, double x1, double y1, double t);
double distanceBetweenTwoPoints(double x0, double y0, double x1, double y1);
typedef struct Nodes {
	Node* node1 = nullptr;
	Node* node2 = nullptr;
} Nodes;

class Edge
{
public:
	float weight;
	Edge(Node* node1,  Node* node2, float weight = 1.0f);
	~Edge();
	void updatePosition();
	const sf::VertexArray& getVertexArray() const;
	const sf::Text& getWeightText() const;
	const Nodes getNodes() const;
	const Arrow& getArrow() const;
	



private:
	
	typedef struct Shape {
		sf::VertexArray* line;
		sf::Font* font;
		sf::Text* weightText;
		Arrow arrow;
	} Shape;
	
	Shape shape;
	Nodes nodes;
};


struct EdgeCollection : public sf::Drawable
{
	std::vector<Edge*> edges;
	bool weighted = true;
	bool directed = true;
	EdgeCollection();
	~EdgeCollection();
	void addEdge(Node* node1, Node* node2, float weight = 1.0f);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


