#ifndef GMP_META_TO_FIXED_STRING_HPP_
#define GMP_META_TO_FIXED_STRING_HPP_

#include <cstdint>
#include <gmp/meta/fixed_string.hpp>

namespace gmp {

namespace detail {

template<std::intmax_t N>
struct to_fixed_string_impl {
    static constexpr auto value = []() {
        constexpr auto buflen = []() {
            unsigned int len = (N == 0) ? 1 : (N > 0 ? 1 : 2);
            for (auto n = N; n; len++, n /= 10);
            return len;
        }();
        
        char buf[buflen] = {};
        auto ptr = buf + buflen;
        *--ptr = '\0';
        
        if constexpr (N != 0) {
            auto n = N < 0 ? -N : N;
            for (; n; n /= 10)
                *--ptr = "0123456789"[n % 10];
            if constexpr (N < 0)
                *--ptr = '-';
        } else {
            buf[0] = '0';
        }
        
        return fixed_string<buflen - 1>(buf);
    }();
};

} // namespace detail

template<std::intmax_t N>
static constexpr auto to_fixed_string_v = detail::to_fixed_string_impl<N>::value;

} // namespace gmp

#endif // GMP_META_TO_FIXED_STRING_HPP_