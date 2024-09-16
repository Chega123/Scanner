#include "language.hpp"
#include <cctype>  // for isalpha, isdigit

bool b_minor::valid_char(char c) {
  return (isalpha(c) || c == '_');
}

bool b_minor::valid_int(char c) {
  return isdigit(c);
}

bool b_minor::valid_symbol(char a) {
  return symbols.find(a) != symbols.end();
}

const std::unordered_set<char> symbols = {'[', ']', '+', '-', '*', '/', '%', '=', '!', '&', '|', '<', '>', ';', ' ', '\'', '\"', ','};

const std::map<std::string, std::string> b_minor::token_list = {
  {"boolean", "TOKEN_BOOLEAN"},
  {"char", "TOKEN_CHAR"},
  {"array", "TOKEN_ARRAY"},
  {"else", "TOKEN_ELSE"},
  {"false", "TOKEN_FALSE"},
  {"for", "TOKEN_FOR"},
  {"function", "TOKEN_FUNCTION"},
  {"if", "TOKEN_IF"},
  {"integer", "TOKEN_INTEGER"},
  {"print", "TOKEN_PRINT"},
  {"return", "TOKEN_RETURN"},
  {"string", "TOKEN_STRING"},
  {"true", "TOKEN_TRUE"},
  {"void", "TOKEN_VOID"},
  {"while", "TOKEN_WHILE"},

  {"[", "TOKEN_["},
  {"]", "TOKEN_]"},
  {"++", "TOKEN_++"},
  {"--", "TOKEN_--"},
  {"-", "TOKEN_NEGNUM"},
  {"!", "TOKEN_NEGEXPR"},
  {"^", "TOKEN_EXPONEN"},
  {"*", "TOKEN_MULT"},
  {"/", "TOKEN_DIV"},
  {"%", "TOKEN_MOD"},
  {"+", "TOKEN_SUM"},
  {"-", "TOKEN_SUB"},
  {"<", "TOKEN_<"},
  {"<=", "TOKEN_<="},
  {">", "TOKEN_>"},
  {">=", "TOKEN_>="},
  {"==", "TOKEN_WHILE"},
  {"!=", "TOKEN_WHILE"},
  {"=", "TOKEN_WHILE"},
  {"&&", "TOKEN_AND"},
  {"||", "TOKEN_OR"},
  {";", "TOKEN_END"},
  {"'", "TOKEN_COMILLA"},
  {"\"", "TOKEN_COMILLA_DOBLE"},
  {",", "TOKEN_SEPARATION"},
  {"//", "TOKEN_COMLINE"},
  {"/*", "TOKEN_COMBLOCKS"}, // COMMENT BLOCK START
  {"*/", "TOKEN_COMBLOCKE"}  // COMMENT BLOCK END
};