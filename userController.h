#pragma once
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include "MACROS.h"


class UserController
{
public:
	EdgeCollection* edgeCollection;
	NodeCollection* nodeCollection;
	Graph* graph;
	bool leftClick = false;
	bool rightClick = false;
	bool mPressed = false;
	bool spacePressed = false; 
	bool enterPressed = false;
	bool connectingNodes = false;
	Node* movingNode = nullptr;
	Node* fromNode = nullptr;
	Node* toNode= nullptr;
	sf::VertexArray createdEdge;
	UserController(EdgeCollection* edgeCollection, NodeCollection* nodeCollection, Graph* graph);
	~UserController();
	void controlNodeCreation(sf::RenderWindow& window);
	void controlEdgeCreation(sf::RenderWindow& window);
	void controlNodeMovement(sf::RenderWindow& window);
};

