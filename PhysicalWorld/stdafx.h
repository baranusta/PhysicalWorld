#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

#include "GL\glew.h"
#include "GL\freeglut.h"
#include <GLFW\glfw3.h>

#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define DIV_CEIL(X,Y) ((X + Y - 1) / Y)