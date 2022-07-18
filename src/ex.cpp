#include "../include/json.hpp"

namespace json {
std::tuple<std::vector < JSONToken > , std::string> lex(std::string raw_json) {
  std::vector<JSONToken> tokens;
  // All tokens will embed a pointer to the raw JSON for debugging purposes
  auto original_copy = std::make_shared<std::string>(raw_json);

  auto generic_lexers = {lex_syntax, lex_string, lex_number, lex_null, lex_true, lex_false};
  for (int i = 0; i < raw_json.length(); i++) {
    // Skip past whitespace
    if (auto new_index = lex_whitespace(raw_json, i); i != new_index) {
      i = new_index - 1;
      continue;
    }

    auto found = false;
    for (auto lexer : generic_lexers) {
      if (auto [token, new_index, error] = lexer(raw_json, i); i != new_index) {
        // Error while lexing, return early
        if (error.length()) {
          return {{}, error};
        }

        // Store reference to the original source
        token.full_source = original_copy;
        tokens.push_back(token);
        i = new_index - 1;
        found = true;
        break;
      }
    }

    if (found) {
      continue;
    }

    return format_error("Unable to lex", raw_json, i);
  }

  return {tokens, ""};
}
} // namespace json