#ifndef CLASSIFIED_WORD_HPP
#define CLASSIFIED_WORD_HPP

#include <string>
#include <vector>

class classified_word {
public:
  std::string word, token_type;
  unsigned int line, col;

  classified_word(const std::string&,const std::string&,unsigned int,unsigned int);
  classified_word();
  classified_word(const classified_word&);
  classified_word& operator=(const classified_word&);
  bool operator==(const classified_word&) const;
  bool operator!=(const classified_word&) const;
  void display() const;
};

using scanner_output = std::vector<classified_word>;

#endif 