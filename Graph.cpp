#include "Graph.h"
#include "MACROS.h"

Graph::Graph(const EdgeCollection& edgeCollection)
{
	log("Size  : " << " " << edgeCollection.edges.size());
	for (unsigned int i = 0; i < edgeCollection.edges.size(); i++)
	{
		Edge* edge = edgeCollection.edges[i];
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

Graph::~Graph()
{

}


