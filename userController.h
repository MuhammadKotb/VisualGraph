#pragma once
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>

#define LEFT_MOUSE sf::Mouse::Left
#define RIGHT_MOUSE sf::Mouse::Right
#define SPACE_KEY sf::Keyboard::Space
#define ENTER_KEY sf::Keyboard::Enter
#define M_KEY sf::Keyboard::M
#define IS_MOUSE_CLICKED sf::Mouse::isButtonPressed
#define IS_KEY_PRESSED sf::Keyboard::isKeyPressed
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
	void listenNodeCreation(sf::RenderWindow& window);
	void listenEdgeCreation(sf::RenderWindow& window);
	void listenNodeMovement(sf::RenderWindow& window);
};

