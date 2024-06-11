#define ZT_COMPONENT_FIELDS(x) \
	public: struct SubresourceData{ x }

#include <tuple>
#include <iostream>

template <typename T>
struct Map
{

};

#define CAT(a, b) a##b
#define XCAT(a, b) CAT(a, b)

#define COUNT_ARGS(...) COUNT_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)
#define COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N

#define FIRST_ARG(arg, ...) arg
#define REST_ARGS(arg, ...) __VA_ARGS__

#define COUNT_ARGS_X(...) (sizeof(#__VA_ARGS__))

#define HANDLE_ARG_2(type, varname) \
	template <> struct Map<type> \
	{ \
		static constexpr const char* typeName = #type; \
		static constexpr const char* varName = #varname; \
		static constexpr const unsigned int byteSize = sizeof(type); \
	};

#define HANDLE_ARG_3(type, varname, x) HANDLE_ARG_2(type, varname)
#define HANDLE_ARG_4(type, varname, x, y) HANDLE_ARG_2(type, varname)
#define HANDLE_ARG_5(type, varname, x, y, z) HANDLE_ARG_2(type, varname)

#define EXTRACT_1(_1) _1
#define EXTRACT_2(_1, _2) _1 _2
#define EXTRACT_3(_1, _2, _3) _1 _2 _3
#define EXTRACT_4(_1, _2, _3, _4) _1 _2 _3 _4

#define HANDLE_ARGS(...) HANDLE_ARGS_N(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
#define HANDLE_ARGS_N(N, ...) XCAT(HANDLE_ARG_, N)(__VA_ARGS__)

#define EXTRACT(...) EXTRACT_N(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
#define EXTRACT_N(N, ...) XCAT(EXTRACT_, N)(__VA_ARGS__)

#define ZT_DEFINE_COMPONENT(x) class x

HANDLE_ARGS(float, myFloat);

#define ZT_DEF_FIELD(...) HANDLE_ARGS(__VA_ARGS__)

#define TEST(...) \
	ZT_DEF_FIELD(__VA_ARGS__) \
	\
	EXTRACT(__VA_ARGS__)

#define STRINGFY(x) STRINGFY2(x)
#define STRINGFY2(x) #x

ZT_DEFINE_COMPONENT(TestComp1)
{
	ZT_COMPONENT_FIELDS(
		int member1 = 0;
	);
};

int main()
{
	std::cout << STRINGFY(EXTRACT_2(x, y)) << '\n';
	return 0;
}