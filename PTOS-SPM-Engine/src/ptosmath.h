#pragma once

#include "predefines.h"
#include "mathoperators.h"
#include "vector.h"
#include "matrix.h"
#include "transform.h"

namespace PTOS {
	template<typename T> T radians(T degrees) { return degrees * 0.017453292519943295; }
	template<typename T> T degrees(T radians) { return radians * 57.29577951308232; }
}