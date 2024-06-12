#pragma once
#include <tuple>
#include <concepts>
#include <type_traits>
#include <string>

namespace CTC
{
    // E1
    template<typename...>
    struct type_list {};

    template <typename T, typename Input_t>
    using tuple_append_t = decltype(
        std::tuple_cat(std::declval<T>(), std::declval<std::tuple<Input_t>>())
        );


    // E2
    template<class TypeList, typename T>
    struct type_list_append;

    template<typename... Ts, typename T>
    struct type_list_append<type_list<Ts...>, T> {
        using type = type_list<Ts..., T>;
    };


    // E3
    template<unsigned N, typename List, unsigned int ID>
    struct state_t {
        static constexpr unsigned n = N;
        static constexpr unsigned id = ID;
        using list = List;
    };


    namespace {
        struct tu_tag {};           // E4
    }


    template<
        unsigned N,
        std::same_as<tu_tag> TUTag,
        unsigned int ID
    >
    struct reader {
        friend auto state_func(reader<N, TUTag, ID>);
    };


    template<
        unsigned N,
        typename List,
        std::same_as<tu_tag> TUTag,
        unsigned int ID
    >
    struct setter {
        // E5
        friend auto state_func(reader<N, TUTag, ID>) {
            return List{};
        }

        static constexpr state_t<N, List, ID> state{};
    };

    // TODO: AUTOMATE THIS
    template struct setter<0, std::tuple<>, tu_tag, 0>;     // E6
    template struct setter<0, std::tuple<>, tu_tag, 1>;
    template struct setter<0, std::tuple<>, tu_tag, 2>;
    template struct setter<0, std::tuple<>, tu_tag, 3>;
    template struct setter<0, std::tuple<>, tu_tag, 4>;
    template struct setter<0, std::tuple<>, tu_tag, 5>;
    template struct setter<0, std::tuple<>, tu_tag, 6>;
    template struct setter<0, std::tuple<>, tu_tag, 7>;
    template struct setter<0, std::tuple<>, tu_tag, 8>;
    template struct setter<0, std::tuple<>, tu_tag, 9>;
    template struct setter<0, std::tuple<>, tu_tag, 10>;
    template struct setter<0, std::tuple<>, tu_tag, 11>;
    template struct setter<0, std::tuple<>, tu_tag, 12>;
    template struct setter<0, std::tuple<>, tu_tag, 13>;


    // E7
    template<
        std::same_as<tu_tag> TUTag,
        auto EvalTag,
        unsigned int ID,
        unsigned N = 0
    >
    [[nodiscard]]
    static consteval auto get_state() {
        constexpr bool counted_past_n = requires(reader<N, TUTag, ID> r) {
            state_func(r);
        };

        if constexpr (counted_past_n) {
            return get_state<TUTag, EvalTag, ID, N + 1>();
        }
        else {
            // E7.1
            constexpr reader<N - 1, TUTag, ID> r;
            return state_t<N - 1, decltype(state_func(r)), ID>{};
        }
    }


    // E8
    template<
        unsigned int ID = 0,
        std::same_as<tu_tag> TUTag = tu_tag,
        auto EvalTag = [] {},
        auto State = get_state<TUTag, EvalTag, ID>()
    >
    using get_list = typename std::remove_cvref_t<decltype(State)>::list;
    template<
        unsigned int ID = 0,
        std::same_as<tu_tag> TUTag = tu_tag,
        auto EvalTag = [] {},
        auto State = get_state<TUTag, EvalTag, ID>()
    >
    consteval auto element_count()
    {
        return State.n;
    }


    // E9
    template<
        typename T,
        std::same_as<tu_tag> TUTag,
        auto EvalTag,
        unsigned int ID
    >
    [[nodiscard]]
    consteval auto append_impl() {
        using cur_state = decltype(get_state<TUTag, EvalTag, ID>());            // E9.1
        using cur_list = typename cur_state::list;
        using new_list = tuple_append_t<cur_list, T>;      // E9.2
        setter<cur_state::n + 1, new_list, TUTag, ID> s;                        // E9.3
        return s.state;                                                     // E9.4
    }


    // E10
    template<
        typename T,
        unsigned int ID,
        std::same_as<tu_tag> TUTag = tu_tag,
        auto EvalTag = [] {},
        auto State = append_impl<T, TUTag, EvalTag, ID>()
    >
    constexpr auto append = [] { return State; };           // E10.1

    template <unsigned N, unsigned int ID>
    struct readerC {
        friend auto counted_flag(readerC<N, ID>);
    };

    template <unsigned N, unsigned int ID>
    struct setterC {
        friend auto	counted_flag(readerC<N, ID>) {}

        static constexpr unsigned n = N;
    };

    template<auto Tag, typename T, unsigned int ID, unsigned NextVal = 0>
    [[nodiscard]]
    consteval auto counter_impl()
    {
        constexpr bool counted_past_value = requires(readerC<NextVal, ID> r) {
            counted_flag(r);
        };

        if constexpr (counted_past_value) {
            return counter_impl<Tag, T, ID, NextVal + 1>();
        }
        else
        {
            append<T, ID>;
            setterC<NextVal, ID> s;
            return s.n;
        }
    }

    template <typename T, unsigned int ID = 0, auto Tag = [] {}, auto Val = counter_impl<Tag, T, ID>() >
    constexpr auto counter = Val;
}


