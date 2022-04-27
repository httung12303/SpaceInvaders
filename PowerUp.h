#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"

class PowerUp : public BaseObject{
public:
	PowerUp() {}
	~PowerUp() { BaseObject::~BaseObject(); }
};