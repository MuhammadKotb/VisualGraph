#include "Graph.h"
#include "MACROS.h"




Graph::Graph(EdgeCollection* edgeCollection)
{
	this->edgeCollection = edgeCollection;
	update();
}

Graph::~Graph()
{

}

void Graph::update()
{

	this->adjacentList.clear();

	for (unsigned int i = 0; i < this->edgeCollection->edges.size(); i++)
	{
		Edge* edge = this->edgeCollection->edges[i];
		Node* node1 = edge->getNodes().node1;
		Node* node2 = edge->getNodes().node2;
		if (this->adjacentList.contains(node1))
		{
			this->adjacentList.at(node1).push_back(node2);
		}
		else
		{
			this->adjacentList.insert({ node1, std::vector<Node*>() });
			this->adjacentList.at(node1).push_back(node2);
		}
		if (this->edgeCollection->directed)
		{
			continue;
		}
		if (this->adjacentList.contains(node2))
		{
			this->adjacentList.at(node2).push_back(node1);
		}
		else
		{
			this->adjacentList.insert({ node2, std::vector<Node*>() });
			this->adjacentList.at(node2).push_back(node1);
		}
	}
}




