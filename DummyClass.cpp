#include "DummyClass.h"
#include "CTM.h"
#include "ComponentsHeader.h"
#include <vector>
#include <iostream>

void DummyClass::DoSomething()
{
	std::cout << "\n\nFrom Dummy Class!" << "\n \n";

	std::vector<int> componentUUIDs = { 1, 2, 3 };

	for (auto UUID : componentUUIDs)
	{
		PrintComponent(UUID);
	}
}
