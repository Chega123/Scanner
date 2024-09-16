#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "classified_word.hpp"
#include "language.hpp"

class scanner {
private:
  std::unique_ptr<char[]> scanner_pointer;
  std::string content;
  size_t content_size;
  size_t index;

  b_minor language;

//devuelve el siguiente carácter del input y mueve el puntero del carácter al siguiente.
  char getchar();
//devuelve el siguiente carácter sin mover el puntero.
  char peekchar(size_t=0);

public:
//llama al scanner 
  scanner_output gettoken();
//carga el contenido desde archivo
  void load_content(const std::string&);
};

#endif 