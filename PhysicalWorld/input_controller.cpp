#include "input_controller.h"

#include <unordered_map>

std::unordered_map <std::string, std::function<void(glm::vec2)>> listeners_windowSizeChange;
std::unordered_map <std::string, std::function<void(glm::vec2)>> listeners_mousePos;
std::unordered_map <std::string, std::function<void(int button, int action, glm::vec2 pos)>> listeners_mouseEvent;
std::unordered_map <std::string, std::function<void(int key, int action)>> listeners_keyEvent;


void windowSizeCallBack(GLFWwindow* window, int width, int height)
{
	for (auto handler : listeners_windowSizeChange)
		handler.second(glm::vec2(width, height));
}

void mousePosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	for (auto handler : listeners_mousePos)
		handler.second(glm::vec2(xpos, ypos));
}

void mouseEventCallBack(GLFWwindow* window, int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	for (auto handler : listeners_mouseEvent)
		handler.second(button, action, glm::vec2(x, y));
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	for (auto handler : listeners_keyEvent)
		handler.second(key, action);
}


template<class T, class F>
void InputController::addListener(std::string key, T& list, F& func)
{
	if (list.find(key) != list.end())
		throw std::string("provide unique Id");
	list[key] = func;
}


void InputController::init(GLFWwindow * window)
{
	m_window = window;
	glfwSetKeyCallback(window, keyCallBack);
	glfwSetWindowSizeCallback(window, windowSizeCallBack);
	glfwSetCursorPosCallback(window, mousePosCallBack);
	glfwSetMouseButtonCallback(window, mouseEventCallBack);
}

void InputController::registerWindowSizeChange(std::string key, const std::function<void(glm::vec2)>& listener)
{
	addListener(key, listeners_windowSizeChange, listener);
}

void InputController::unregisterWindowSizeChange(std::string key)
{
	listeners_windowSizeChange.erase(key);
}

void  InputController::registerMousePos(std::string key, const std::function<void(glm::vec2)>& listener)
{
	addListener(key, listeners_mousePos, listener);
}

void  InputController::unregisterMousePos(std::string key)
{
	listeners_mousePos.erase(key);
}

void  InputController::registerMouseEvent(std::string key, const std::function<void(int button, int action, glm::vec2 pos)>& listener)
{
	addListener(key, listeners_mouseEvent, listener);
}

void  InputController::unregisterMouseEvent(std::string key)
{
	listeners_mouseEvent.erase(key);
}

void InputController::registerKey(std::string key, const std::function<void(int key, int action)>& listener)
{
	addListener(key, listeners_keyEvent, listener);
}

void InputController::unregisterKey(std::string key)
{
	listeners_keyEvent.erase(key);
}


GLFWwindow* InputController::getWindow()
{
	return m_window;
}