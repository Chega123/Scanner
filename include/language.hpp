
#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <map>
#include <string>
#include <unordered_set>

class b_minor {
private:
public:
  static const std::map<std::string, std::string> token_list;
  static const std::unordered_set<char> symbols;
  bool valid_char(char);
  bool valid_int(char);
  bool valid_symbol(char);
};

#endif 