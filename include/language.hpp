
#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <map>
#include <string>
#include <unordered_set>

class b_minor {
private:
public:
  static const std::map<std::string, std::string> literal_tokens;
  static const std::map<std::string, std::string> keywords;
  static const std::map<std::string, std::string> types;
  static const std::unordered_set<char> symbols;
};

#endif 