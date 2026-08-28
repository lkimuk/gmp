#include <cassert>
#include <string>
#include <vector>
#include <gmp/serialization/xml.hpp>

namespace {
struct xml_document {
  std::string title;
  std::vector<int> values;
};
}

static_assert(gmp::serialization_reader<gmp::value_reader>);

int main() {
  const xml_document source{"standalone", {1, 2, 3}};
  auto encoded = gmp::to_xml(source);
  assert(encoded);
  auto decoded = gmp::from_xml<xml_document>(*encoded);
  assert(decoded);
  assert(decoded->title == source.title);
  assert(decoded->values == source.values);

  const auto null_document =
      R"(<gmp version="1"><value kind="null"/></gmp>)";
  const auto declaration_cases = {
      std::string(R"(<?xml version="1.0"?>)") + null_document,
      std::string(R"(<?xml version="1.0" encoding="UTF-8"?>)") +
          null_document,
      std::string(R"(<?xml version="1.0" standalone="yes"?>)") +
          null_document,
      std::string(
          R"(<?xml version="1.0" encoding="utf-8" standalone="no"?>)") +
          null_document,
  };
  for (const auto &document : declaration_cases) {
    assert(gmp::parse_xml(document));
  }

  const auto malformed_declarations = {
      std::string(R"(<?xml encoding="UTF-8" version="1.0"?>)") +
          null_document,
      std::string(
          R"(<?xml version="1.0" standalone="yes" encoding="UTF-8"?>)") +
          null_document,
      std::string(R"(<?xml version="1.0" version="1.0"?>)") +
          null_document,
      std::string(R"(<?xml version="1.1"?>)") + null_document,
      std::string(R"(<?xml version="1.0" encoding="UTF-16"?>)") +
          null_document,
  };
  for (const auto &document : malformed_declarations) {
    assert(!gmp::parse_xml(document));
  }

  assert(gmp::parse_xml(
      R"(<gmp version = '1'><value kind = 'null' /></gmp>)"));
  assert(!gmp::parse_xml(
      R"(<gmp version="1"><value kind="string">&#X41;</value></gmp>)"));

  gmp::detail::xml_writer writer;
  assert(writer.write_null());
  assert(writer.finish());
  assert(!writer.finish());
  assert(!writer.write_null());
}
