#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <gmp/gmp.hpp>

enum class role { user, administrator };

struct profile {
  std::string name;
  role account_role;
  std::optional<std::string> email;
  std::vector<int> scores;
};

int main() {
  profile source{"Miles", role::administrator, std::nullopt, {90, 95, 100}};

  auto json = gmp::to_json(source, {}, {.pretty = true});
  if (!json) {
    std::cerr << json.error().describe() << '\n';
    return 1;
  }

  std::cout << *json << "\n\n";

  auto xml = gmp::to_xml(source);
  if (!xml) {
    std::cerr << xml.error().describe() << '\n';
    return 1;
  }
  std::cout << *xml << "\n\n";

  auto decoded = gmp::from_json<profile>(*json);
  if (!decoded) {
    std::cerr << decoded.error().describe() << '\n';
    return 1;
  }

  return decoded->name == source.name ? 0 : 1;
}
