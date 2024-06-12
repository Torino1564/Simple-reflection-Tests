#pragma once
#include "Component.h"

struct Component1 : public ComponentBase<Component1>
{
public:
	struct SubresourceData {
		ZT_DEFINE_COMPONENT_VARIABLE(int, posX);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posY);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posZ);
		ZT_DEFINE_COMPONENT_VARIABLE(float, field1);
		ZT_DEFINE_COMPONENT_VARIABLE(float, field2);
	};
};