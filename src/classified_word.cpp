#include <iostream>

#include "classified_word.hpp"

classified_word::classified_word(const std::string& word_, const std::string& token_type_, unsigned int line_, unsigned int col_)
  : word(word_), token_type(token_type_), line(line_), col(col_) {}

classified_word::classified_word() : word(""), token_type(""), line(0), col(0) {}

classified_word::classified_word(const classified_word& other) = default;

classified_word& classified_word::operator=(const classified_word& other) = default;

bool classified_word::operator==(const classified_word& other) const {
  return word == other.word && token_type == other.token_type &&
         line == other.line && col == other.col;
}

bool classified_word::operator!=(const classified_word& other) const {
  return !(*this == other);
}

void classified_word::display() const {
  std::cout << "Word: " << word << ", Token: " << token_type 
            << ", Line: " << line << ", Column: " << col << std::endl;
}