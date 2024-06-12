#pragma once
#include "Component.h"

ZT_DEFINE_COMPONENT(Component2)
{
	ZT_COMPONENT_FIELDS(
		ZT_DEFINE_COMPONENT_VARIABLE(int, posX);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posY);
		ZT_DEFINE_COMPONENT_VARIABLE(int, posZ);
		ZT_DEFINE_COMPONENT_VARIABLE(float, diffuseIntensity);
		ZT_DEFINE_COMPONENT_VARIABLE(float, linearAtt);
	);
};