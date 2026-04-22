#include <string_view>

#include <gmp/gmp.hpp>

struct Person {
    int age;
    double score;
};

int main() {
    Person person{42, 98.5};
    bool visited_age = false;
    bool visited_score = false;

    static_assert(gmp::member_count<Person>() == 2);
    static_assert(gmp::member_name<0, Person>() == "age");
    static_assert(gmp::member_name<1, Person>() == "score");

    auto& age = gmp::member_ref<0>(person);
    age += 1;

    gmp::for_each_member(person, [&](std::string_view name, auto& value) {
        if (name == "age") {
            visited_age = true;
            value += 1;
        } else if (name == "score") {
            visited_score = true;
        }
    });

    return (person.age == 44 && visited_age && visited_score) ? 0 : 1;
}
