#include <iostream>
#include <cctype>  // for isalpha, isdigit
#include <unordered_set>
#include <fstream>

#include "scanner.hpp"

bool scanner::valid_char(char c) {
  return (isalpha(c) || c == '_');
}

bool scanner::valid_int(char c) {
  return isdigit(c);
}

bool scanner::valid_symbol(char a) {
  const std::unordered_set<char> symbols = {'[', ']', '+', '-', '*', '/', '%', '=', '!', '&', '|', '<', '>', ';', ' ', '\'', '\"', ','};
  return symbols.find(a) != symbols.end();
}

void scanner::load_content(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    content.resize(size);
    if (file.read(&content[0], size)) {
      content_size = content.size();
      file.close();
    } else {
      std::cerr << "No se puede leer el archivo :c" << std::endl;
      content_size = 0;
      content.clear();
    }
  } else {
    std::cerr << "No se puede abrir el archivo :c" << std::endl;
    content_size = 0;
    content.clear();
  }
}

char scanner::getchar() {
  if (index < content_size)
  return content[index++];
  return '\0';
}

char scanner::peekchar() {
  int next = index + 1;
  if (next < content_size)
  return content[next];
  return '\0';
}