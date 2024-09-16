#include "language.hpp"

const std::unordered_set<char> symbols = {'[', ']', '+', '-', '*', '/', '%', '=', '!', '&', '|', '<', '>', ';', ' ', '\'', '\"', ','};

const std::map<std::string, std::string> b_minor::literal_tokens = {
  {"[",   "TOKEN_["},
  {"]",   "TOKEN_]"},
  {"++",  "TOKEN_++"},
  {"--",  "TOKEN_--"},
  {"-",   "TOKEN_NEGNUM"},
  {"!",   "TOKEN_NEGEXPR"},
  {"^",   "TOKEN_EXPONEN"},
  {"*",   "TOKEN_MULT"},
  {"/",   "TOKEN_DIV"},
  {"%",   "TOKEN_MOD"},
  {"+",   "TOKEN_SUM"},
  {"-",   "TOKEN_SUB"},
  {"<",   "TOKEN_<"},
  {"<=",  "TOKEN_<="},
  {">",   "TOKEN_>"},
  {">=",  "TOKEN_>="},
  {"==",  "TOKEN_WHILE"},
  {"!=",  "TOKEN_WHILE"},
  {"=",   "TOKEN_WHILE"},
  {"&&",  "TOKEN_AND"},
  {"||",  "TOKEN_OR"},
  {";",   "TOKEN_END"},
  {"'",   "TOKEN_COMILLA"},
  {"\"",  "TOKEN_COMILLA_DOBLE"},
  {",",   "TOKEN_SEPARATION"},
  {"//",  "TOKEN_COMLINE"},
  {"/*",  "TOKEN_COMBLOCKS"}, // COMMENT BLOCK START
  {"*/",  "TOKEN_COMBLOCKE"}  // COMMENT BLOCK END
};

const std::map<std::string, std::string> b_minor::keywords = {
  {"boolean", "TOKEN_BOOLEAN"},
  {"char",    "TOKEN_CHAR"},
  {"array",   "TOKEN_ARRAY"},
  {"else",    "TOKEN_ELSE"},
  {"false",   "TOKEN_FALSE"},
  {"for",     "TOKEN_FOR"},
  {"function","TOKEN_FUNCTION"},
  {"if",      "TOKEN_IF"},
  {"integer", "TOKEN_INTEGER"},
  {"print",   "TOKEN_PRINT"},
  {"return",  "TOKEN_RETURN"},
  {"string",  "TOKEN_STRING"},
  {"true",    "TOKEN_TRUE"},
  {"void",    "TOKEN_VOID"},
  {"while",   "TOKEN_WHILE"}
};

const std::map<std::string, std::string> b_minor::types = {
  {"boolean", "TOKEN_BOOLEAN"},
  {"char",    "TOKEN_CHAR"},
  {"integer", "TOKEN_INTEGER"},
  {"string",  "TOKEN_STRING"}
};