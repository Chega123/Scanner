#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>

class classified_word {
public:
  std::string word;
  std::string token_type;
  int line, col;
  classified_word(std::string,std::string,int,int);
};

class scanner {
private:
char* scanner_p = nullptr;
std::string content;
size_t content_size;
size_t index;

bool valid_char(char);
bool valid_int(char);
bool valid_symbol(char);

void load_content(const std::string&);

public:
//devuelve el siguiente carácter del input y mueve el puntero del carácter al siguiente.
  char getchar();
//devuelve el siguiente carácter sin mover el puntero.
  char peekchar();
//llama al scanner 
  void gettoken();

};

#endif 