#pragma once
#include <iostream>
#include <TGUI/TGUI.hpp>
#define log(x) std::cout << x << std::endl;
#define RED sf::Color::Red
#define BLACK sf::Color::Black
#define WHITE sf::Color::White
#define GREEN sf::Color::Green
#define BLUE sf::Color::Blue
#define FIRA_CODE_FONT "assets\\FiraCode-Medium.ttf"
#define LEFT_MOUSE sf::Mouse::Left
#define RIGHT_MOUSE sf::Mouse::Right
#define SPACE_KEY sf::Keyboard::Space
#define ENTER_KEY sf::Keyboard::Enter
#define M_KEY sf::Keyboard::M
#define IS_MOUSE_CLICKED sf::Mouse::isButtonPressed
#define IS_KEY_PRESSED sf::Keyboard::isKeyPressed
using tgui::Button;
using tgui::RadioButton;
constexpr unsigned int WINDOW_HEIGHT = 900;
constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int NODE_FONT_SIZE = 25;
constexpr unsigned int EDGE_WEIGHT_FONT_SIZE = 25;
constexpr float NODE_THICKNESS = 2.3f;
constexpr float NODE_RADIUS = 25;
constexpr float EDGE_THICKNESS = 1.0f;
constexpr unsigned int DELAY = 500;