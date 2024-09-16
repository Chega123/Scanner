#include <iostream>
#include <cctype>  // for isalpha, isdigit
#include <fstream>

#include "scanner.hpp"

scanner::scanner(const std::string& filename) : index(0) {
  if (load_content(filename) == true) {
    content_size = content.size();
  } else {
    content_size = 0;
  } 
}

bool scanner::load_content(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    content.resize(size);
    if (file.read(&content[0], size)) {
      file.close();
      return true;
    } else {
      std::cerr << "No se puede leer el archivo :c" << std::endl;
      content.clear();
      return false;
    }
  } else {
    std::cerr << "No se puede abrir el archivo :c" << std::endl;
    content.clear();
    return false;
  }
}

char scanner::get_char() {
  if (index < content_size)
  return content[index++];
  return '\0';
}

char scanner::peek_char(size_t peek) {
  size_t next = index + peek;
  if (next < content_size)
  return content[next];
  return '\0';
}

scanner_output scanner::gettoken() {
  scanner_output classified_words;
  if (content_size == 0)
  return classified_words;
  size_t line = 0, col = 0; index = 0;
  char current_char = content[index];
  std::string word = "";
  const char space = ' ', carriage_return = '\r', line_feed = '\n';
  while (index != content_size) {
    if (current_char == space) {
      get_char();
      col++;
    } else if (current_char == carriage_return || current_char == line_feed) {
      get_char();
      line++;
      col = 0;
    } else if (valid_char(current_char)) {

    }

  }
  return classified_words;
}


bool scanner::valid_char(char c) {
  return (isalpha(c) || c == '_');
}

bool scanner::valid_int(char c) {
  return isdigit(c);
}

bool scanner::valid_symbol(char a) {
  return language.symbols.find(a) != language.symbols.end();
}