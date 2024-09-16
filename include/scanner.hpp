#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "classified_word.hpp"
#include "language.hpp"

class scanner {
private:
  size_t content_size, index;
  std::string content;
  b_minor language;

  bool valid_char(char);
  bool valid_int(char);
  bool valid_symbol(char);

  bool is_identifier(size_t,classified_word&);
  bool is_comment(size_t,classified_word&);
  bool is_keyword(size_t,classified_word&);
  bool load_content(const std::string&);

//devuelve el siguiente carácter del input y mueve el puntero del carácter al siguiente.
  char get_char();
//devuelve el siguiente carácter sin mover el puntero.
  char peek_char(size_t=0);

public:
//llama al scanner 
  scanner_output gettoken();
  scanner(const std::string&);
};

#endif 