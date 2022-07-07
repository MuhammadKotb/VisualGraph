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
	Graph(const EdgeCollection& edgeCollection);
	~Graph();

};

