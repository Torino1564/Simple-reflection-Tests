#include <tuple>
#include <iostream>
#include <format>
#include "ComponentsHeader.h"
#include <vector>
#include "DummyClass.h"

int main()
{
	std::cout << "From main!" << "\n\n";
	std::vector<unsigned int> componentUUIDs = { Component1::UUID, Component2::UUID, Component3::UUID };
	
	for (auto UUID : componentUUIDs)
	{
		PrintComponent(UUID);
	}


	DummyClass dummyObj;
	dummyObj.DoSomething();
}