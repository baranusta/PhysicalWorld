#pragma once

#include "vertex_array_object.h"


#define BUF_RADIUS			3
#define BUF_C_SPECULAR		4
#define BUF_C_AMBIENT		5
#define BUF_C_DIFFUSE		6
#ifdef _DEBUG
	#define BUF_MASS		7
	#define BUF_FORCE		8
	#define BUF_VISCOSITY	9
#endif