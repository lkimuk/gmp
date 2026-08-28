#include <array>
#include <cassert>
#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#include <gmp/gmp.hpp>

namespace {

enum class color { red, green, blue };

struct address {
  std::string city;
  int postcode;
};

struct person {
  std::string name;
  int age;
  std::optional<std::string> nickname;
  std::vector<int> scores;
  address home;
  color favorite;
};

struct immutable {
  const int value;
};

struct account {
  std::string display_name;
  int level;
};

struct session {
  std::string user;
  int cache;
  int version;
};

struct generated_defaults {
  std::string label;
};

struct duplicate_schema_member {
  int first;
  int second;
};

struct duplicate_schema_wire {
  int first;
  int second;
};

struct unknown_schema_member {
  int value;
};

struct transient_schema_collision {
  int hidden;
  int value;
};

struct alias_schema_collision {
  int first;
  int second;
};

struct duplicate_schema_alias {
  int value;
};

class opaque_id {
public:
  explicit opaque_id(std::uint64_t value) : value_(value) {}
  [[nodiscard]] std::uint64_t value() const noexcept { return value_; }

private:
  std::uint64_t value_;
};

struct wire_record {
  int code;
  std::string text;
};

class opaque_record {
public:
  opaque_record(int code, std::string text)
      : code_(code), text_(std::move(text)) {}
  int code() const noexcept { return code_; }
  const std::string &text() const noexcept { return text_; }

private:
  int code_;
  std::string text_;
};

} // namespace

template <> struct gmp::serialization_traits<opaque_id> {
  template <typename Archive>
  static gmp::serialization_result<void> serialize(Archive &archive,
                                                   const opaque_id &value) {
    return archive.write_unsigned(value.value());
  }

  template <typename Archive>
  static gmp::serialization_result<opaque_id>
  deserialize(Archive &archive, gmp::type_tag<opaque_id>) {
    if (archive.kind() != gmp::serialization_kind::unsigned_integer) {
      return gmp::make_serialization_error(
          gmp::serialization_errc::type_mismatch, "expected opaque id integer");
    }
    return opaque_id(archive.read_unsigned());
  }
};

template <> struct gmp::serialization_traits<opaque_record> {
  template <typename Archive>
  static gmp::serialization_result<void> serialize(Archive &archive,
                                                   const opaque_record &value) {
    return archive.object(2, [&](auto &object) {
      auto status = object.field("code", value.code());
      if (!status) {
        return status;
      }
      return object.field("text", value.text());
    });
  }

  template <typename Archive>
  static gmp::serialization_result<opaque_record>
  deserialize(Archive &archive, gmp::type_tag<opaque_record>) {
    auto value = archive.template decode<wire_record>();
    if (!value) {
      return value.error();
    }
    return opaque_record(value->code, std::move(value->text));
  }
};

template <> struct gmp::serialization_schema<account> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"display_name">.name<"name">().alias<"display_name">());
};

template <> struct gmp::serialization_schema<session> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"cache">.transient(), gmp::field<"version">.defaulted<1>());
};

template <> struct gmp::serialization_schema<generated_defaults> {
  static constexpr auto fields =
      gmp::define_schema(gmp::field<"label">.default_with<[] {
        return std::string("generated");
      }>());
};

template <> struct gmp::serialization_schema<duplicate_schema_member> {
  static constexpr auto fields = gmp::define_schema(gmp::field<"first">,
                                                     gmp::field<"first">);
};

template <> struct gmp::serialization_schema<duplicate_schema_wire> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"first">.name<"same">(),
      gmp::field<"second">.name<"same">());
};

template <> struct gmp::serialization_schema<unknown_schema_member> {
  static constexpr auto fields =
      gmp::define_schema(gmp::field<"does_not_exist">);
};

template <> struct gmp::serialization_schema<transient_schema_collision> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"hidden">.name<"value">().transient());
};

template <> struct gmp::serialization_schema<alias_schema_collision> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"first">.alias<"legacy">(),
      gmp::field<"second">.alias<"legacy">());
};

template <> struct gmp::serialization_schema<duplicate_schema_alias> {
  static constexpr auto fields = gmp::define_schema(
      gmp::field<"value">.alias<"legacy">().alias<"legacy">());
};

static_assert(!gmp::detail::valid_schema<duplicate_schema_member>());
static_assert(!gmp::detail::valid_schema<duplicate_schema_wire>());
static_assert(!gmp::detail::valid_schema<unknown_schema_member>());
static_assert(!gmp::detail::valid_schema<transient_schema_collision>());
static_assert(!gmp::detail::valid_schema<alias_schema_collision>());
static_assert(!gmp::detail::valid_schema<duplicate_schema_alias>());
static_assert(gmp::enum_count<color>() == 3);
static_assert(gmp::enum_count<color, "not-a-prefix">() == 0);

int main() {
  const person source{
      "Miles",      28, std::nullopt, {90, 95, 100}, {"Shanghai", 200000},
      color::green,
  };

  auto encoded = gmp::to_json(source);
  assert(encoded);
  assert(encoded->find("\"name\":\"Miles\"") != std::string::npos);
  assert(encoded->find("\"favorite\":\"green\"") != std::string::npos);

  auto decoded = gmp::from_json<person>(*encoded);
  assert(decoded);
  assert(decoded->name == source.name);
  assert(decoded->age == source.age);
  assert(!decoded->nickname);
  assert(decoded->scores == source.scores);
  assert(decoded->home.city == source.home.city);
  assert(decoded->favorite == source.favorite);

  auto xml = gmp::to_xml(source);
  assert(xml);
  assert(xml->find("<gmp version=\"1\"><value kind=\"object\">") == 0);
  assert(xml->find("<member name=\"name\">") != std::string::npos);
  auto xml_decoded = gmp::from_xml<person>(*xml);
  assert(xml_decoded);
  assert(xml_decoded->name == source.name);
  assert(xml_decoded->scores == source.scores);
  assert(xml_decoded->home.city == source.home.city);
  assert(xml_decoded->favorite == source.favorite);
  auto pretty_xml = gmp::to_xml(source, {}, {.pretty = true});
  assert(pretty_xml && pretty_xml->find('\n') != std::string::npos);
  auto pretty_xml_decoded = gmp::from_xml<person>(*pretty_xml);
  assert(pretty_xml_decoded && pretty_xml_decoded->name == source.name);

  auto reordered =
      gmp::from_json<address>(R"({"postcode":200000,"city":"Shanghai"})");
  assert(reordered);
  assert(reordered->city == "Shanghai");

  auto missing = gmp::from_json<address>(R"({"city":"Shanghai"})");
  assert(!missing);
  assert(missing.error().code == gmp::serialization_errc::missing_field);
  assert(missing.error().path == "postcode");

  auto unknown = gmp::from_json<address>(
      R"({"city":"Shanghai","postcode":200000,"extra":1})");
  assert(!unknown);
  assert(unknown.error().code == gmp::serialization_errc::unknown_field);

  gmp::deserialization_options ignore_unknown;
  ignore_unknown.unknown_fields = gmp::unknown_field_policy::ignore;
  auto ignored = gmp::from_json<address>(
      R"({"city":"Shanghai","postcode":200000,"extra":1})", ignore_unknown);
  assert(ignored);

  auto duplicate = gmp::from_json<address>(
      R"({"city":"Shanghai","city":"Beijing","postcode":200000})");
  assert(!duplicate);
  assert(duplicate.error().code == gmp::serialization_errc::duplicate_field);

  gmp::deserialization_options keep_last;
  keep_last.duplicate_fields = gmp::duplicate_field_policy::keep_last;
  auto replaced = gmp::from_json<address>(
      R"({"city":"Shanghai","city":"Beijing","postcode":200000})", keep_last);
  assert(replaced && replaced->city == "Beijing");

  auto immutable_value = gmp::from_json<immutable>(R"({"value":42})");
  assert(immutable_value);
  assert(immutable_value->value == 42);

  auto custom = gmp::to_json(opaque_id(42));
  assert(custom && *custom == "42");
  auto custom_round_trip = gmp::from_json<opaque_id>(*custom);
  assert(custom_round_trip && custom_round_trip->value() == 42);
  auto custom_xml = gmp::to_xml(opaque_id(42));
  assert(custom_xml &&
         *custom_xml ==
             R"(<gmp version="1"><value kind="unsigned">42</value></gmp>)");
  auto custom_xml_round_trip = gmp::from_xml<opaque_id>(*custom_xml);
  assert(custom_xml_round_trip && custom_xml_round_trip->value() == 42);

  auto account_json = gmp::to_json(account{"Miles", 3});
  assert(account_json &&
         account_json->find("\"name\":\"Miles\"") != std::string::npos);
  auto legacy_account =
      gmp::from_json<account>(R"({"display_name":"Miles","level":3})");
  assert(legacy_account && legacy_account->display_name == "Miles");

  auto session_json = gmp::to_json(session{"Miles", 99, 2});
  assert(session_json && session_json->find("cache") == std::string::npos);
  auto session_value = gmp::from_json<session>(R"({"user":"Miles"})");
  assert(session_value);
  assert(session_value->cache == 0);
  assert(session_value->version == 1);

  using tuple_type = std::tuple<int, std::string, bool>;
  auto tuple_value = gmp::from_json<tuple_type>(R"([7,"seven",true])");
  assert(tuple_value);
  assert(std::get<0>(*tuple_value) == 7);

  auto fixed_custom = gmp::from_json<std::array<opaque_id, 2>>(R"([10,20])");
  assert(fixed_custom);
  assert((*fixed_custom)[1].value() == 20);

  auto list_value = gmp::from_json<std::list<int>>(R"([1,2,3])");
  assert(list_value && list_value->size() == 3);

  auto set_value = gmp::from_json<std::set<int>>(R"([3,1,2])");
  assert(set_value && set_value->size() == 3);
  auto duplicate_set = gmp::from_json<std::set<int>>(R"([1,1])");
  assert(!duplicate_set);

  using variant_type = std::variant<int, std::string>;
  variant_type variant = std::string("text");
  auto variant_json = gmp::to_json(variant);
  assert(variant_json);
  auto variant_value = gmp::from_json<variant_type>(*variant_json);
  assert(variant_value);
  assert(std::get<std::string>(*variant_value) == "text");
  auto bad_variant_index =
      gmp::from_json<variant_type>(R"({"index":2,"value":0})");
  assert(!bad_variant_index);
  assert(bad_variant_index.error().code ==
         gmp::serialization_errc::value_out_of_range);
  assert(bad_variant_index.error().path == "index");

  std::map<std::string, int> map{{"one", 1}, {"two", 2}};
  auto map_json = gmp::to_json(map);
  assert(map_json);
  auto map_value = gmp::from_json<std::map<std::string, int>>(*map_json);
  assert(map_value && *map_value == map);

  std::map<int, std::string> numeric_map{{1, "one"}, {2, "two"}};
  auto numeric_map_json = gmp::to_json(numeric_map);
  assert(numeric_map_json && *numeric_map_json == R"([[1,"one"],[2,"two"]])");
  auto numeric_map_value =
      gmp::from_json<std::map<int, std::string>>(*numeric_map_json);
  assert(numeric_map_value && *numeric_map_value == numeric_map);
  auto bad_numeric_map_key =
      gmp::from_json<std::map<int, std::string>>(R"([["bad","value"]])");
  assert(!bad_numeric_map_key);
  assert(bad_numeric_map_key.error().path == "0.0");

  std::map<std::string, int> empty_key{{"", 1}};
  auto empty_key_value = gmp::to_serialization_value(empty_key);
  assert(empty_key_value);
  auto empty_key_round_trip =
      gmp::from_serialization_value<std::map<std::string, int>>(
          *empty_key_value);
  assert(empty_key_round_trip && *empty_key_round_trip == empty_key);

  auto generated = gmp::from_json<generated_defaults>(R"({})");
  assert(generated && generated->label == "generated");

  auto custom_dom = gmp::to_serialization_value(opaque_id(77));
  assert(custom_dom && custom_dom->is<std::uint64_t>());
  auto custom_from_dom = gmp::from_serialization_value<opaque_id>(*custom_dom);
  assert(custom_from_dom && custom_from_dom->value() == 77);

  auto record_json = gmp::to_json(opaque_record(9, "nine"));
  assert(record_json && *record_json == R"({"code":9,"text":"nine"})");
  auto record = gmp::from_json<opaque_record>(*record_json);
  assert(record && record->code() == 9 && record->text() == "nine");
  auto record_xml = gmp::to_xml(opaque_record(9, "nine"));
  assert(record_xml);
  auto record_from_xml = gmp::from_xml<opaque_record>(*record_xml);
  assert(record_from_xml && record_from_xml->code() == 9 &&
         record_from_xml->text() == "nine");

  auto escaped_xml = gmp::to_xml(std::string("<&>\"'"));
  assert(escaped_xml && escaped_xml->find("&lt;&amp;&gt;") != std::string::npos);
  auto escaped_xml_value = gmp::from_xml<std::string>(*escaped_xml);
  assert(escaped_xml_value && *escaped_xml_value == "<&>\"'");
  auto single_quoted_xml = gmp::from_xml<std::string>(
      R"(<gmp version='1'><value kind='string'>single</value></gmp>)");
  assert(single_quoted_xml && *single_quoted_xml == "single");

  auto empty_key_xml = gmp::to_xml(empty_key);
  assert(empty_key_xml && empty_key_xml->find("name=\"\"") != std::string::npos);
  auto empty_key_from_xml =
      gmp::from_xml<std::map<std::string, int>>(*empty_key_xml);
  assert(empty_key_from_xml && *empty_key_from_xml == empty_key);

  auto numeric_map_xml = gmp::to_xml(numeric_map);
  assert(numeric_map_xml);
  auto numeric_map_from_xml =
      gmp::from_xml<std::map<int, std::string>>(*numeric_map_xml);
  assert(numeric_map_from_xml && *numeric_map_from_xml == numeric_map);

  auto malformed_xml =
      gmp::from_xml<std::string>(
          R"(<gmp version="1"><value kind="string">&unknown;</value></gmp>)");
  assert(!malformed_xml);
  assert(malformed_xml.error().code == gmp::serialization_errc::invalid_escape);
  auto dtd_xml = gmp::parse_xml(
      "<!DOCTYPE gmp><gmp version=\"1\"><value kind=\"null\"/></gmp>");
  assert(!dtd_xml);
  assert(dtd_xml.error().code == gmp::serialization_errc::unsupported_type);
  auto xml_depth = gmp::parse_xml(
      "<gmp version=\"1\"><value kind=\"array\"></value></gmp>",
      {.max_depth = 0});
  assert(!xml_depth);
  assert(xml_depth.error().code == gmp::serialization_errc::depth_limit_exceeded);
  auto declared_xml = gmp::from_xml<std::string>(
      R"(<?xml version="1.0" encoding="UTF-8"?><gmp version="1"><value kind="string">&#x4E2D;</value></gmp>)");
  assert(declared_xml && *declared_xml == "\xE4\xB8\xAD");
  auto normalized_xml = gmp::from_xml<std::string>(
      "<gmp version=\"1\"><value kind=\"string\">a\r\nb\r"
      "c</value></gmp>");
  assert(normalized_xml && *normalized_xml == "a\nb\nc");
  auto bad_encoding_xml = gmp::parse_xml(
      R"(<?xml version="1.0" encoding="UTF-16"?><gmp version="1"><value kind="null"/></gmp>)");
  assert(!bad_encoding_xml);
  assert(bad_encoding_xml.error().code ==
         gmp::serialization_errc::unsupported_type);
  auto bad_declaration_xml = gmp::parse_xml(
      R"(<?xml encoding="UTF-8"?><gmp version="1"><value kind="null"/></gmp>)");
  assert(!bad_declaration_xml);
  assert(bad_declaration_xml.error().code ==
         gmp::serialization_errc::invalid_syntax);
  auto unsupported_xml_version =
      gmp::parse_xml(R"(<gmp version="2"><value kind="null"/></gmp>)");
  assert(!unsupported_xml_version);
  assert(unsupported_xml_version.error().code ==
         gmp::serialization_errc::unsupported_type);
  std::string forbidden_xml_character("bad\0text", 8);
  auto forbidden_xml = gmp::to_xml(forbidden_xml_character);
  assert(!forbidden_xml);
  assert(forbidden_xml.error().code ==
         gmp::serialization_errc::value_out_of_range);
  gmp::xml_write_options tiny_xml;
  tiny_xml.max_output_size = 8;
  auto xml_output_limit = gmp::to_xml(source, {}, tiny_xml);
  assert(!xml_output_limit);
  assert(xml_output_limit.error().code ==
         gmp::serialization_errc::size_limit_exceeded);

  auto unicode = gmp::from_json<std::string>(R"("\u4e2d\u6587 \ud83d\ude00")");
  assert(unicode && *unicode == "中文 😀");

  std::string invalid_utf8("\xc0\xaf", 2);
  auto invalid_string = gmp::to_json(invalid_utf8);
  assert(!invalid_string);

  auto literal = gmp::to_json("text");
  assert(literal && *literal == R"("text")");
  const char *null_string = nullptr;
  auto null_string_json = gmp::to_json(null_string);
  assert(null_string_json && *null_string_json == "null");
  const char embedded[] = {'a', '\0', 'b', '\0'};
  auto embedded_literal = gmp::to_json(embedded);
  assert(embedded_literal && *embedded_literal == R"("a\u0000b")");
  gmp::serialization_value null_literal(static_cast<const char *>(nullptr));
  assert(null_literal.is<gmp::serialization_value::null_t>());
  gmp::serialization_value signed_literal(42);
  assert(signed_literal.is<std::int64_t>() &&
         signed_literal.get<std::int64_t>() == 42);
  gmp::serialization_value unsigned_literal(42u);
  assert(unsigned_literal.is<std::uint64_t>() &&
         unsigned_literal.get<std::uint64_t>() == 42);
  gmp::serialization_value float_literal(0.5f);
  assert(float_literal.is<double>() && float_literal.get<double>() == 0.5);
  gmp::serialization_value view_literal(std::string_view("view"));
  assert(view_literal.is<std::string>() &&
         view_literal.get<std::string>() == "view");

  gmp::detail::json_writer json_writer;
  assert(json_writer.write_null());
  assert(json_writer.finish());
  assert(!json_writer.finish());
  assert(!json_writer.write_null());

  gmp::value_writer value_writer;
  assert(value_writer.write_null());
  assert(value_writer.finish());
  assert(!value_writer.finish());
  assert(!value_writer.write_null());

  gmp::value_writer invalid_value_writer;
  assert(invalid_value_writer.begin_object(1));
  assert(!invalid_value_writer.begin_array(0));

  gmp::serialization_options numeric_enum;
  numeric_enum.enums = gmp::enum_encoding::underlying;
  auto numeric_color = gmp::to_json(color::blue, numeric_enum);
  assert(numeric_color && *numeric_color == "2");
  auto rejected_numeric_color = gmp::from_json<color>(*numeric_color);
  assert(!rejected_numeric_color);
  gmp::deserialization_options allow_numeric_enum;
  allow_numeric_enum.enums = gmp::enum_decoding::name_or_underlying;
  auto accepted_numeric_color =
      gmp::from_json<color>(*numeric_color, allow_numeric_enum);
  assert(accepted_numeric_color && *accepted_numeric_color == color::blue);

  auto overflow = gmp::from_json<std::uint8_t>("256");
  assert(!overflow);
  assert(overflow.error().code == gmp::serialization_errc::integer_overflow);

  auto malformed = gmp::parse_json(R"({"x":1,})");
  assert(!malformed);
  assert(malformed.error().offset != 0);

  auto pretty = gmp::to_json(source, {}, {.pretty = true, .indent_width = 2});
  assert(pretty && pretty->find('\n') != std::string::npos);

  gmp::serialization_options shallow;
  shallow.max_depth = 1;
  auto depth_error = gmp::to_json(source, shallow);
  assert(!depth_error);
  assert(depth_error.error().code ==
         gmp::serialization_errc::depth_limit_exceeded);

  gmp::json_read_options no_json_containers;
  no_json_containers.max_depth = 0;
  auto empty_depth_error = gmp::parse_json("[]", no_json_containers);
  assert(!empty_depth_error);
  assert(empty_depth_error.error().code ==
         gmp::serialization_errc::depth_limit_exceeded);

  gmp::json_write_options limited_output;
  limited_output.max_output_size = 4;
  auto output_error = gmp::to_json(source, {}, limited_output);
  assert(!output_error);
  assert(output_error.error().code ==
         gmp::serialization_errc::size_limit_exceeded);

  gmp::json_write_options bounded_indent;
  bounded_indent.pretty = true;
  bounded_indent.indent_width = std::numeric_limits<unsigned>::max();
  bounded_indent.max_output_size = 16;
  auto indent_error = gmp::to_json(source, {}, bounded_indent);
  assert(!indent_error);
  assert(indent_error.error().code ==
         gmp::serialization_errc::size_limit_exceeded);

  gmp::serialization_options no_members;
  no_members.max_container_size = 0;
  auto aggregate_size_error = gmp::to_json(source, no_members);
  assert(!aggregate_size_error);
  assert(aggregate_size_error.error().code ==
         gmp::serialization_errc::size_limit_exceeded);

  gmp::deserialization_options no_variant_members;
  no_variant_members.max_container_size = 1;
  auto variant_size_error =
      gmp::from_json<variant_type>(*variant_json, no_variant_members);
  assert(!variant_size_error);
  assert(variant_size_error.error().code ==
         gmp::serialization_errc::size_limit_exceeded);
}
