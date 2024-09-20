#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Token {
public:
  std::string token_name;
  std::string text;
  int line;
  int col;

  Token(std::string N_, std::string T_, int L_, int C_)
      : token_name(N_), text(T_), line(L_), col(C_) {}
};

class Error {
public:
  std::string type;
  std::string message;
  int line;
  int col;

  Error(std::string T_, std::string M_, int L_, int C_)
      : type(T_), message(M_), line(L_), col(C_) {}
};

class Scanner {
private:
  char* text_Arr;
  int index;
  int sizee;
  int line_global;
  int col_global;
  std::vector<Token> tokens;
  std::vector<Error> errors;
  std::map<std::string, std::string> tokens_list;

public:
  Scanner();
  ~Scanner();

  void read_file(const std::string&);
  void add_token(std::string,std::string);
  void log_error(std::string,std::string);

  char get_char();
  char peek_char();
  char peek_actual_char();

  bool Find_char(char a);
  bool Find_int(char a);
  bool Find_symbol(char a);

  void handle_symbol(std::string word);
  void handle_single_line_comment();
  void handle_block_comment();
  void handle_string();
  
  void scanner();

  std::vector<Token> get_tokens();

  void save_errors_to_json(const std::string& = "../error_logs.json");
  void save_tokens_to_json(const std::string& = "../tokens.json");
};

#endif 