#pragma once
#define ZT_COMPONENT_FIELDS(x) public: struct SubresourceData{ x }

#define CAT(x, y) x##y

#define ZT_DEFINE_COMPONENT_VARIABLE(type, var) \
	type var; \
	using CAT(var, _t) = CTM::Map_t<type, #type, #var, sizeof(type), UUID>

#include "CTM.h"
#include "CTC.h"
#include <iostream>

static constexpr unsigned int componentList = 0;

template <typename T>
struct ComponentBase
{
public:
	static constexpr unsigned int UUID = CTC::counter<T, componentList>;
private:
	CTM::setter<0, std::tuple<>, CTM::tu_tag, UUID> setter;
public:
	static constexpr unsigned int varCount = CTM::element_count<UUID>();
};

#define ZT_DEFINE_COMPONENT(x) struct x : public ComponentBase<x>

template <unsigned ComponentN = 0, bool FoundCmp = false, typename Component = Component0, unsigned ElementN = 0>
void PrintComponent(const unsigned int UUID)
{
	if constexpr (!FoundCmp)
	{
		if constexpr (ComponentN >= CTC::element_count<componentList>())
		{
			return;
		}
		using CurrentComponent = std::tuple_element_t<ComponentN, CTC::get_list<componentList>>;
		if (CurrentComponent::UUID == UUID)
		{
			std::cout << std::format("Component Fields - UUID: {}", CurrentComponent::UUID) << "\n \n \n";
			PrintComponent<ComponentN, true, CurrentComponent>(UUID);
			return;
		}
		else
		{
			if constexpr (ComponentN < CTC::element_count<componentList>() - 1)
				return PrintComponent<ComponentN + 1, false>(UUID);
		}
	}
	else
	{
		using VarMap = CTM::get_list<Component::UUID>;
		if constexpr (ElementN < std::tuple_size_v<VarMap>)
		{
			using MapElement = std::tuple_element_t<ElementN, VarMap>;
			typename MapElement::TypeName_t typeNameFunc;
			typename MapElement::VarName_t varNameFunc;
			typename MapElement::VarSize_t varSizeFunc;
			std::cout << std::format("Element Number: {}\n Type Name: {}\n Var Name: {}\n Var Size: {}\n\n", ElementN, typeNameFunc(), varNameFunc(), varSizeFunc());
			PrintComponent<ComponentN, true, Component, ElementN + 1>(UUID);
		}
		else
		{
			return;
		}
	}
}