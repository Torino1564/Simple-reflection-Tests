#define ZT_COMPONENT_FIELDS(x) \
	public: struct SubresourceData{ x }

#define CAT(x, y) x##y

#define ZT_DEFINE_COMPONENT_VARIABLE(type, var) \
	type var; \
	static constexpr char CAT(type, var)##name[] = #type; \
	static constexpr char CAT(var, type)##name[] = #var; \
	static constexpr unsigned int type##var = CTM::Map<type, CAT(type, var)##name, CAT(var, type)##name, sizeof(type), UUID>

#include <tuple>
#include <iostream>
#include "CTM.h"
#include <format>

//template <typename T>
//struct Map1
//{
//
//};
//
//#define CAT(a, b) a##b
//#define XCAT(a, b) CAT(a, b)
//
//#define COUNT_ARGS(...) COUNT_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)
//#define COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
//
//#define FIRST_ARG(arg, ...) arg
//#define REST_ARGS(arg, ...) __VA_ARGS__
//
//#define COUNT_ARGS_X(...) (sizeof(#__VA_ARGS__))
//
//#define HANDLE_ARG_2(type, varname) \
//	template <> struct Map1<type> \
//	{ \
//		static constexpr const char* typeName = #type; \
//		static constexpr const char* varName = #varname; \
//		static constexpr const unsigned int byteSize = sizeof(type); \
//	};
//
//#define HANDLE_ARG_3(type, varname, x) HANDLE_ARG_2(type, varname)
//#define HANDLE_ARG_4(type, varname, x, y) HANDLE_ARG_2(type, varname)
//#define HANDLE_ARG_5(type, varname, x, y, z) HANDLE_ARG_2(type, varname)
//
//#define EXTRACT_1(_1) _1
//#define EXTRACT_2(_1, _2) _1 _2
//#define EXTRACT_3(_1, _2, _3) _1 _2 _3
//#define EXTRACT_4(_1, _2, _3, _4) _1 _2 _3 _4
//
//#define HANDLE_ARGS(...) HANDLE_ARGS_N(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
//#define HANDLE_ARGS_N(N, ...) XCAT(HANDLE_ARG_, N)(__VA_ARGS__)
//
//#define EXTRACT(...) EXTRACT_N(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
//#define EXTRACT_N(N, ...) XCAT(EXTRACT_, N)(__VA_ARGS__)
//
//#define ZT_DEFINE_COMPONENT(x) class x
//
//HANDLE_ARGS(float, myFloat);
//
//#define ZT_DEF_FIELD(...) HANDLE_ARGS(__VA_ARGS__)
//
//#define TEST(...) \
//	ZT_DEF_FIELD(__VA_ARGS__) \
//	\
//	EXTRACT(__VA_ARGS__)
//
//#define STRINGFY(x) STRINGFY2(x)
//#define STRINGFY2(x) #x
//
//ZT_DEFINE_COMPONENT(TestComp1)
//{
//	ZT_COMPONENT_FIELDS(
//		int member1 = 0;
//	);
//};
struct TestComponent1
{
	static constexpr int UUID = 1;

public: struct SubresourceData {
	int hp; static constexpr char inthpname[] = "int"; static constexpr char hpintname[] = "hp"; static constexpr unsigned int inthp = CTM::Map<int, inthpname, hpintname, sizeof(int), UUID>; float mana; static constexpr char floatmananame[] = "float"; static constexpr char manafloatname[] = "mana"; static constexpr unsigned int floatmana = CTM::Map<float, floatmananame, manafloatname, sizeof(float), UUID>; double energy; static constexpr char doubleenergyname[] = "double"; static constexpr char energydoublename[] = "energy"; static constexpr unsigned int doubleenergy = CTM::Map<double, doubleenergyname, energydoublename, sizeof(double), UUID>; double regen; static constexpr char doubleregenname[] = "double"; static constexpr char regendoublename[] = "regen"; static constexpr unsigned int doubleregen = CTM::Map<double, doubleregenname, regendoublename, sizeof(double), UUID>;
};

	static constexpr unsigned int varCount = CTM::element_count<UUID>();
};

template <auto Tag = [] {} >
extern consteval const char* StaticString(const char* pStr_t)
{
	static constexpr const char[] pStr = pStr_t;
	return pStr;
}

template <const char* Str>
struct TestStruct
{
	static constexpr const char* pString = Str;
};


template <typename Tuple, unsigned N = 0>
void PrintMap()
{
	if constexpr (N < std::tuple_size_v<Tuple>)
	{
		using MapElement = std::tuple_element_t<N, Tuple>;
		typename MapElement::TypeName_t typeNameFunc;
		typename MapElement::VarName_t varNameFunc;
		typename MapElement::VarSize_t varSizeFunc;
		std::cout << std::format("Element Number: {}\n Type Name: {}\n Var Name: {}\n Var Size: {}\n\n", N, typeNameFunc(), varNameFunc(), varSizeFunc());
		PrintMap<Tuple, N + 1>();
	}
	else
	{
		return;
	}
}

template <typename Tuple, unsigned N>
void PrintMapElement()
{
	using MapElement = std::tuple_element_t<N, Tuple>;
	typename MapElement::TypeName_t typeNameFunc;
	typename MapElement::VarName_t varNameFunc;
	typename MapElement::VarSize_t varSizeFunc;
	std::cout << std::format("Element Number: {}\n Type Name: {}\n Var Name: {}\n Var Size: {}\n\n", N, typeNameFunc(), varNameFunc(), varSizeFunc());
}

int main()
{
	int testVar = TestComponent1::varCount;
	PrintMap<CTM::get_list<TestComponent1::UUID>>();
}