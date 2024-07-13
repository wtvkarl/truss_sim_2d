#ifndef STATE_MANAGER_IMPLEMENTATION_H
#define STATE_MANAGER_IMPLEMENATION_H

#include <GLFW/glfw3.h>
#include "Force.h"
#include "Point.h"

enum Mode { NORMAL, PLACE, CONNECT };
Mode STATE_MODE = NORMAL;

GLfloat cursorX = 0, cursorY = 0; //cursor pos
GLfloat x_norm = 0, y_norm = 0; //normalized cursor 

#endif