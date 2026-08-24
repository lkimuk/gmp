#ifdef GMP_MAX_SUPPORTED_FIELDS
#undef GMP_MAX_SUPPORTED_FIELDS
#endif
#define GMP_MAX_SUPPORTED_FIELDS 4

#include <gmp/gmp.hpp>

struct four_fields {
    int first;
    int second;
    int third;
    int fourth;
};

static_assert(GMP_MAX_SUPPORTED_FIELDS == 4);
static_assert(gmp::member_count_v<four_fields> == 4);
static_assert(gmp::member_name<3, four_fields>() == "fourth");

int main() {}
