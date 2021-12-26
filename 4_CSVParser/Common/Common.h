#pragma once

#include <tuple>
#include <iostream>

namespace {

    template<class Ch, class Tr, size_t I, class... Args>
    struct printer {
        static void print(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
            printer<Ch, Tr, I - 1, Args...>::print(os, t);
            os << ", ";
            os << std::get<I>(t);
        }
    };

    template<class Ch, class Tr, class... Args>
    struct printer<Ch, Tr, 0, Args...> {
        static void print(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
            os << std::get<0>(t);
        }
    };

    template<class Ch, class Tr, class... Args>
    void print_tuple(std::basic_ostream<Ch,Tr>& os, const std::tuple<Args...>& t) {
        printer<Ch, Tr, sizeof...(Args) - 1, Args...>::print(os, t);
    }
}

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
    -> std::basic_ostream<Ch, Tr>& {
    os << '(';
    print_tuple(os, t);
    return os << ')';
}
