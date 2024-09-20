#include "scanner.hpp"

Scanner::Scanner() : text_Arr(nullptr), index(0), sizee(0),
                     line_global(1), col_global(1) {
  tokens_list = { 
    {"boolean","TOKEN_BOOLEAN"}, {"char","TOKEN_CHAR"}, {"array","TOKEN_ARRAY"}, 
    {"else","TOKEN_ELSE"}, {"false","TOKEN_FALSE"}, {"for","TOKEN_FOR"}, 
    {"function","TOKEN_FUNCTION"}, {"if","TOKEN_IF"}, {"integer","TOKEN_INTEGER"}, 
    {"print","TOKEN_PRINT"}, {"return","TOKEN_RETURN"}, {"string","TOKEN_STRING"}, 
    {"true","TOKEN_TRUE"}, {"void","TOKEN_VOID"}, {"while","TOKEN_WHILE"},
    {"[","TOKEN_["}, {"]","TOKEN_]"}, {"(","TOKEN_("}, {")","TOKEN_)"},
    {"++","TOKEN_++"}, {"--","TOKEN_--"}, {"-","TOKEN_NEGNUM"}, {"!","TOKEN_NEGEXPR"},
    {"^","TOKEN_EXPONEN"}, {"*","TOKEN_MULT"}, {"/","TOKEN_DIV"}, {"%","TOKEN_MOD"},
    {"+","TOKEN_SUM"}, {"-","TOKEN_SUB"}, {"<","TOKEN_<"}, {"<=","TOKEN_<="}, 
    {">","TOKEN_>"}, {">=","TOKEN_>="}, {"==","TOKEN_=="}, {"!=","TOKEN_!="}, 
    {"=","TOKEN_="}, {"&&","TOKEN_AND"}, {"||","TOKEN_OR"}, {";","TOKEN_;"},
    {"\'","TOKEN_COMILLA"}, {"\"","TOKEN_COMILLA_DOBLE"}, {",","TOKEN_,"},
    {"//","TOKEN_COMLINE"}, {"{","TOKEN_{"}, {"}","TOKEN_}"}, {":","TOKEN_:"},
    {"/*","TOKEN_COMBLOCKS"}, {"*/","TOKEN_COMBLOCKE"}
  };
}

Scanner::~Scanner() {
  delete[] text_Arr;
}

void Scanner::read_file(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    sizee = file.tellg();
    file.seekg(0, std::ios::beg);
    text_Arr = new char[sizee];
    file.read(text_Arr, sizee);
    file.close();
  } else {
    std::cerr << "No se puede abrir el archivo :c" << std::endl;
    text_Arr = nullptr;
    sizee = 0;
  }
}

void Scanner::add_token(std::string token_name, std::string text) {
  tokens.push_back(Token(token_name, text, line_global, col_global));
}

 void Scanner::log_error(std::string type, std::string message) {
  errors.push_back(Error(type, message, line_global, col_global));
}

char Scanner::get_char() {
  if (index < sizee) {
    return text_Arr[index++];
  }
  return '\0';
}

char Scanner::peek_char() {
  if (index + 1 < sizee) {
    return text_Arr[index + 1];
  }
  return '\0';
}

char Scanner::peek_actual_char() {
  if (index < sizee) {
    return text_Arr[index];
  }
  return '\0';
}

bool Scanner::find_char(char a) {
  return (isalpha(a) || int(a) == 95);
}

bool Scanner::find_int(char a) {
  return isdigit(a);
}

bool Scanner::find_symbol(char a) {
  std::string symbols = "[]+-*/%=!&|<>;:{}() \'\",\n\r\0\\";
  return symbols.find(a) != std::string::npos || a == '\0';
}

void Scanner::handle_symbol(std::string word) {
  if (tokens_list.find(word) != tokens_list.end()) {
    add_token(tokens_list[word], word);
  } else {
    log_error("UnknownSymbolError'",word);
  }
}

void Scanner::handle_single_line_comment() {
  std::string comment = "";
  while (peek_actual_char() != '\n' && peek_actual_char() != '\0') {
    comment += get_char();
  }
  add_token("TOKEN_COMLINE", comment);
}

void Scanner::handle_block_comment() {
  std::string comment = "/";
  get_char();
  col_global++;
  while (peek_actual_char() != '\0') {
    comment += get_char();
    col_global++;
    if (peek_actual_char() == '*' && peek_char() == '/') {
      comment += get_char();
      comment += get_char();
      break;
    }
  }
  if (comment.substr(comment.size() - 2) != "*/") {
    log_error("UnclosedCommentError", "Unclosed block comment");
  } else {
    add_token("TOKEN_COMBLOCK", comment);
  }
}

void Scanner::handle_string() {
  std::string word;
  get_char();
  col_global++;
  while (peek_actual_char() != '\"' && peek_actual_char() != '\n' && peek_actual_char() != '\0') {
    if (peek_actual_char() == '\\' && peek_char() == '\"') {
      word += get_char();
    }
    word += get_char();
    col_global++;
  }
  if (peek_actual_char() == '\"') {
    add_token("TOKEN_TEXT_STRING", word);
    get_char();
    col_global++;
  } else {
    log_error("UnclosedStringError", word);
  }
}

void Scanner::scanner() {
  std::string word;
  char letter;
  while (index < sizee) {
    letter = peek_actual_char();
    word = "";

    if (letter == '#') { break; }

    if (letter == '\n' || letter == ' ' || letter == '\r') {
      get_char();
      if (letter == '\n') { line_global++; col_global = 1; }
      continue;
    }

    if (letter == '/' && peek_char() == '/') {
      handle_single_line_comment();
      continue;
    }

    if (letter == '/' && peek_char() == '*') {
      handle_block_comment();
      continue;
    }

    if (find_char(letter)) {
      bool valid_identifier = true;
      while (find_char(peek_char()) || find_int(peek_char())) {
        word += get_char();
        col_global++;
      }
      word += get_char();
      col_global++;
      if (tokens_list.find(word) != tokens_list.end()) {
        add_token(tokens_list[word], word);
      } else if (valid_identifier) {
        add_token("TOKEN_ID", word);
      } else {
        log_error("InvalidIdentifierError", "Invalid identifier: " + word);
      }
    } else if (find_int(letter)) {
      bool valid_number = true;
      while (find_int(peek_char())) {
        word += get_char();
        col_global++;
      }
      word += get_char();
      col_global++;
      if (valid_number) {
        add_token("TOKEN_NUM", word);
      } else {
        log_error("InvalidNumberError", "Invalid number: " + word);
      }
    } else if (letter == '\"') {
      handle_string();
    } else {
      word += get_char();
      col_global++;
      handle_symbol(word);
    }
  }
  save_errors_to_json();
  save_tokens_to_json();
}

std::vector<Token> Scanner::get_tokens() {
  return tokens;
}

using json = nlohmann::json;

void Scanner::save_errors_to_json(const std::string& filename) {
  json error_log;
  for (const auto& err : errors) {
    json error_entry = {
      {"type", err.type},
      {"message", err.message},
      {"line", err.line},
      {"col", err.col}
    };
    error_log.push_back(error_entry);
  }

  std::ofstream file(filename);
  if (file.is_open()) {
    file << error_log.dump(4);
    file.close();
  } else {
    std::cerr << "Failed to open " << filename << " for writing." << std::endl;
  }
}

void Scanner::save_tokens_to_json(const std::string& filename) {
  json token_list;
  for (const auto& tok : tokens) {
    json token_entry = {
      {"token_name", tok.token_name},
      {"text", tok.text},
      {"line", tok.line},
      {"col", tok.col}
    };
    token_list.push_back(token_entry);
  }

  std::ofstream file(filename);
  if (file.is_open()) {
    file << token_list.dump(4);
    file.close();
  } else {
    std::cerr << "Failed to open " << filename << " for writing." << std::endl;
  }
}