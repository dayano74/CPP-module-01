#include <iostream>
#include <string>

#include "FileReplacer.hpp"

void usage(const char* prog) {
  std::cout << "Usage: " << prog << " : <filename> <s1> <s2>" << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
    return 1;
  }

  const std::string filename = argv[1];
  const std::string s1 = argv[2];
  const std::string s2 = argv[3];

  FileReplacer repl(filename, s1, s2);
  std::string err;
  if (!repl.run(err)) {
    std::cerr << "Error: " << err << std::endl;
    return 2;
  }
  return 0;
}
