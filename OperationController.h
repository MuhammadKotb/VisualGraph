#pragma once
#include "Operations.h"
#include "MACROS.h"
#include "Graph.h"
#include <atomic>
#include <thread>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
class OperationController
{

public:
	std::atomic<bool> done;
	Graph* graph;
	tgui::Gui* gui;
	tgui::Button::Ptr DFSButton;
	tgui::Button::Ptr BFSButton;
	tgui::ComboBox::Ptr operationsComboBox;
	tgui::Button::Ptr playButton;
	tgui::EditBox::Ptr delayTimeEditBox;
	unsigned int delayTime = 1000;
	bool spacePressed = false;
	bool enterPressed = false;
	bool firedThread = false;
	std::thread DFSThread;
	std::thread BFSThread;


	OperationController(tgui::Gui* gui, Graph* graph);
	~OperationController();
	void chooseOperation();
	void controlDFS();
	void controlBFS();
	void changeDelay();
};

