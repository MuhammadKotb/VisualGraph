#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <unordered_set>
#include "Node.h"
#include "Edge.h"


class Graph
{
public:
	std::unordered_map<Node*, std::vector<Node*>> adjacentList;
	Graph(EdgeCollection* edgeCollection);
	~Graph();
	void update();

private:
	EdgeCollection* edgeCollection;
};

