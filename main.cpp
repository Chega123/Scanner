#include <iostream>
#include "scanner.hpp"

using namespace std;


int main() {
  Scanner scanner;
  scanner.read_file("../code.txt");  // Provide the file to scan
  scanner.scanner();

  vector<Token> tokens = scanner.get_tokens();
  for (const auto& tok : tokens) {
    cout << "Token: " << tok.token_name << ", Text: " << tok.text << ", Line: " << tok.line << ", Column: " << tok.col << endl;
  }

  return 0;
}