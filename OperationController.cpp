#include "OperationController.h"




OperationController::OperationController(tgui::Gui* gui, Graph* graph) : gui(gui), graph(graph)
{
	this->done.store(true);
	this->operationsComboBox = std::static_pointer_cast<tgui::ComboBox>(this->gui->get("OperationsComboBox"));
	this->delayTimeEditBox = std::static_pointer_cast<tgui::EditBox>(this->gui->get("DelayTime"));
	this->playButton = std::static_pointer_cast<tgui::Button>(this->gui->get("PlayButton"));
	this->playButton->onClick(&OperationController::chooseOperation, this);
	this->delayTimeEditBox->onTextChange(&OperationController::changeDelay, this);
	/*this->DFSButton = std::static_pointer_cast<tgui::Button>(this->gui->get("DFSButton"));
	this->BFSButton = std::static_pointer_cast<tgui::Button>(this->gui->get("BFSButton"));
	this->DFSButton->onClick(&OperationController::controlDFS, this);
	this->BFSButton->onClick(&OperationController::controlBFS, this);*/
}
OperationController::~OperationController()
{

}

void OperationController::chooseOperation()
{
	const int operation = this->operationsComboBox->getSelectedItemIndex();
	switch (operation)
	{
	case 0 : this->controlBFS();
	case 1: this->controlDFS();
	}

}

void OperationController::controlDFS()
{
	if (done.load())
	{
		done.store(false);
		DFSThread = std::thread([&]() { DFS(graph, this->delayTime); done.store(true); });
		DFSThread.detach();
	}
}

void OperationController::controlBFS()
{

	if (done.load())
	{
		done.store(false);
		BFSThread = std::thread([&]() { BFS(graph, this->delayTime); done.store(true); });
		BFSThread.detach();
	}
}
	
void OperationController::changeDelay()
{
	if (done.load())
	{
		this->delayTime = std::atoi(&((std::string)this->delayTimeEditBox->getText())[0]);
	}
}