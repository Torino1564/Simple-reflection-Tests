#pragma once
#include "Component.h"

struct Component3 : public ComponentBase<Component3>
{
public:
	struct SubresourceData {
		ZT_DEFINE_COMPONENT_VARIABLE(int, posX);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posY);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posZ);
		ZT_DEFINE_COMPONENT_VARIABLE(float, attackCooldown);
		ZT_DEFINE_COMPONENT_VARIABLE(float, attackDmg);
	};
};