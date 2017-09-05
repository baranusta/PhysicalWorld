#pragma once

#include "stdafx.h"

#include <functional>

#define PHYSICS_UNSET_INDEX -1

class InputController
{
private:

	GLFWwindow* m_window;
	
	template<class T, class F>
	void addListener(std::string key, T& list, F& func);
	
	InputController()
	{}
public:
	InputController(InputController&) = delete;
	void operator=(InputController&) = delete;

	static InputController& getInstance()
	{
		static InputController controller;
		return controller;
	}

public:
	void init(GLFWwindow*);

	void registerWindowSizeChange(std::string, const std::function<void(glm::vec2)>&);
	void unregisterWindowSizeChange(std::string);

	void registerMousePos(std::string, const std::function<void(glm::vec2)>&);
	void unregisterMousePos(std::string);

	void registerMouseEvent(std::string, const std::function<void(int button, int action, glm::vec2 pos)>&);
	void unregisterMouseEvent(std::string);

	void registerKey(std::string, const std::function<void(int key, int action)>&);
	void unregisterKey(std::string);

	GLFWwindow* getWindow();
};