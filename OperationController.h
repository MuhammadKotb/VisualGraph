#pragma once
#include "Operations.h"
#include "MACROS.h"
#include "Graph.h"
#include <atomic>
#include <thread>

class OperationController
{

public:
	std::atomic<bool> done;
	Graph* graph;
	bool spacePressed = false;
	bool enterPressed = false;
	bool firedThread = false;
	std::thread DFSThread;
	std::thread BFSThread;


	OperationController(Graph* graph);
	~OperationController();
	void controlDFS();
	void controlBFS();
};

