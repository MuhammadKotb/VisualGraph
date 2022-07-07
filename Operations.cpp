#include "Operations.h"
#include <thread>
#include <chrono>
#include <queue>
void recursiveDFS(Graph* graph, Node* node, std::unordered_set<int>& visited)
{
	visited.insert(node->id);
	node->setFillColor(RED);
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	node->setFillColor(BLACK);
	for (const auto& adjNode : graph->adjacentList.at(node))
	{
		if (!visited.contains(adjNode->id))
		{
			recursiveDFS(graph, adjNode, visited);
		}
		if (visited.contains(adjNode->id))
		{
			node->setFillColor(BLUE);
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
			node->setFillColor(BLACK);

		}
				
	}
	
}

void DFS(Graph* graph)
{
	graph->update();
	std::unordered_set<int> visited;
	
	for (const auto& kv : graph->adjacentList)
	{
		if (!visited.contains(kv.first->id))
		{
			recursiveDFS(graph, kv.first, visited);
		}
	}
}


void recursiveBFS(Graph* graph, Node* node, std::unordered_set<int>& visited, std::queue<Node*>& adjNodes)
{
	visited.insert(node->id);
	if (!adjNodes.empty())
	{
		adjNodes.pop();
	}
	node->setFillColor(RED);
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	node->setFillColor(BLACK);
	for (const auto& adjNode : graph->adjacentList.at(node))
	{
		if (!visited.contains(adjNode->id))
		{
			adjNodes.push(adjNode);
		}
	}
	if (!adjNodes.empty())
	{
		recursiveBFS(graph, adjNodes.front(), visited, adjNodes);
	}
}


void BFS(Graph* graph)
{
	graph->update();

	std::queue<Node*> ajdNodes;
	std::unordered_set<int> visited;

	for (const auto& kv : graph->adjacentList)
	{
		if (!visited.contains(kv.first->id))
		{
			recursiveBFS(graph, kv.first, visited, ajdNodes);
		}
	}
}

