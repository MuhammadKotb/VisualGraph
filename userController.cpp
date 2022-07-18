#include "UserController.h"
#include <SFML/Graphics.hpp>
UserController::UserController(tgui::Gui* gui, EdgeCollection* edgeCollection, NodeCollection* nodeCollection, Graph* graph) : 
	gui(gui), edgeCollection(edgeCollection), nodeCollection(nodeCollection), graph(graph)
{
	this->createdEdge = sf::VertexArray(sf::Lines, 2);
	this->newNodeButton = std::static_pointer_cast<tgui::Button>(this->gui->get("newNodeButton"));
	this->weightedButton = std::static_pointer_cast<tgui::RadioButton>(this->gui->get("WeightedRadioButton"));
	this->unweightedButton = std::static_pointer_cast<tgui::RadioButton>(this->gui->get("UnweightedRadioButton"));
	this->directedButton = std::static_pointer_cast<tgui::RadioButton>(this->gui->get("DirectedRadioButton"));
	this->undirectedButton = std::static_pointer_cast<tgui::RadioButton>(this->gui->get("UndirectedRadioButton"));
	this->newNodeButton->onClick(&UserController::controlNodeCreation, this);
	this->weightedButton->setChecked(true);
	this->directedButton->setChecked(true);

	this->weightedButton->onCheck([&]() {this->edgeCollection->weighted = true; this->graph->update(); });
	this->unweightedButton->onCheck([&]() {this->edgeCollection->weighted = false; this->graph->update(); });
	this->directedButton->onCheck([&]() {this->edgeCollection->directed = true; this->graph->update(); });
	this->undirectedButton->onCheck([&]() {this->edgeCollection->directed = false; this->graph->update(); });
}

UserController::~UserController()
{

}

void UserController::controlNodeMovement(sf::RenderWindow& window)
{

	if (IS_MOUSE_CLICKED(LEFT_MOUSE))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);

		if (!this->leftClick)
		{
			for (const auto& node : nodeCollection->nodes)
			{
				this->leftClick = node->inNode((sf::Vector2f)pos);
				if (this->leftClick)
				{
					this->movingNode = node;
					break;
				}
			}
		}
		if (this->leftClick)
		{

			if (pos.x > 0 && pos.x < WINDOW_WIDTH && pos.y > 0 && pos.y < WINDOW_HEIGHT)
			{
				pos.x -= (int)this->movingNode->getCircleShape().getRadius();
				pos.y -= (int)this->movingNode->getCircleShape().getRadius();
				this->movingNode->setPosition((sf::Vector2f)pos);
			}
		}
	}
	else
	{
		this->leftClick = false;
	}

}

void UserController::controlNodeCreation()
{
	nodeCollection->addNode(sf::Vector2f(60.0f, 60.0f));
}

void UserController::controlEdgeCreation(sf::RenderWindow& window)
{
	if (IS_MOUSE_CLICKED(RIGHT_MOUSE))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);


		if (!this->rightClick)
		{
			for (unsigned int i = 0; i < this->nodeCollection->nodes.size(); i++)
			{
				if (this->nodeCollection->nodes[i]->inNode((sf::Vector2f)pos))
				{
					this->fromNode = this->nodeCollection->nodes[i];
					this->rightClick = true;
					break;
				}
			}
		}
		if (fromNode)
		{
			this->connectingNodes = true;
			this->createdEdge[0].position = fromNode->getCenter();
			this->createdEdge[1].position = (sf::Vector2f)pos;
		}

	}
	else
	{
		if (this->rightClick)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);

			if (fromNode)
			{
				for (unsigned int i = 0; i < nodeCollection->nodes.size(); i++)
				{
					if (nodeCollection->nodes[i]->inNode((sf::Vector2f)pos))
					{
						toNode = nodeCollection->nodes[i];
						this->rightClick = true;
						break;
					}
				}
			}
			if (fromNode && toNode)
			{
				if (fromNode != toNode)
				{
					edgeCollection->addEdge(fromNode, toNode);

				}
			}
		}
		fromNode = nullptr;
		toNode = nullptr;
		connectingNodes = false;
		this->rightClick = false;

	}
}