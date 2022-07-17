#pragma once
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include "MACROS.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
class UserController
{
public:
	EdgeCollection* edgeCollection;
	NodeCollection* nodeCollection;
	Graph* graph;
	tgui::Gui* gui;
	tgui::Button::Ptr newNodeButton;
	tgui::RadioButton::Ptr weightedButton;
	tgui::RadioButton::Ptr unweightedButton;
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
	UserController(tgui::Gui* gui, EdgeCollection* edgeCollection, NodeCollection* nodeCollection, Graph* graph);
	~UserController();
	void controlNodeCreation();
	void controlEdgeCreation(sf::RenderWindow& window);
	void controlNodeMovement(sf::RenderWindow& window);
};

