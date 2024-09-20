#include <iostream>
#include "scanner.hpp"

using namespace std;

int main() {
  Scanner scanner;
  scanner.read_file("../code.txt");
  scanner.scanner();

  vector<Token> tokens = scanner.get_tokens();
  cout << endl;cout << endl;cout << endl;
  return 0;
}