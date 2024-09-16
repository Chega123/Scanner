#include <iostream>
#include <fstream>

#include "scanner.hpp"

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

char scanner::peekchar(size_t peek) {
  size_t next = index + peek;
  if (next < content_size)
  return content[next];
  return '\0';
}