#pragma once

#include <type_traits>
#include <string>

namespace guim::tt
{
    template<typename T1, typename T2>
    constexpr bool is_same_decay = std::is_same_v<std::decay_t<T1>, std::decay_t<T2>>;

    template<typename T1, typename T2>
    using enable_if_is_type = std::enable_if_t<is_same_decay<T1, T2>>;

    template<typename T>
    using enable_if_string = enable_if_is_type<T, std::string>;

	template<typename T>
	constexpr bool is_string = is_same_decay<T, std::string>;

	template<typename T>
	constexpr bool is_cstring = is_same_decay<T, const char[]> || is_same_decay<T, const char*>;

	template<typename T>
	constexpr bool is_stringish = is_string<T> || is_cstring<T>;

	template<typename T>
	using enable_if_stringish = std::enable_if_t<is_stringish<T>>;	

    template<typename, typename = void>
    struct is_iterable : std::false_type { } ;

    template<typename T>
    struct is_iterable<
        T, 
        std::void_t<
            decltype(std::declval<T>().begin()),
            decltype(std::declval<T>().end())
        >
    > : std::true_type { };

    template<typename T, typename TElem>
    constexpr bool is_iterable_of = is_iterable<T>::value && is_same_decay<decltype(*(std::declval<T>().begin())), TElem>;
}