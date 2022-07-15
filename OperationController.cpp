#include "OperationController.h"




OperationController::OperationController(Graph* graph)
{
	this->graph = graph;
	this->done.store(true);
}
OperationController::~OperationController()
{

}

void OperationController::controlDFS()
{
	if (IS_KEY_PRESSED(SPACE_KEY))
	{

		if (!spacePressed && done)
		{
			done = false;
			DFSThread = std::thread([&]() { DFS(graph); done = true; });
			DFSThread.detach();
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
}

void OperationController::controlBFS()
{
	if (IS_KEY_PRESSED(ENTER_KEY))
	{

		if (!enterPressed && done)
		{
			done = false;
			BFSThread = std::thread([&]() { BFS(graph); done = true; });
			BFSThread.detach();
			enterPressed = true;
		}
	}
	else
	{
		enterPressed = false;
	}
}