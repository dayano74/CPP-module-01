#include <iostream>
#include <string>

int main() {
  std::string brain = "HI THIS IS BRAIN";

  std::string* stringPTR = &brain;
  std::string& stringREF = brain;

  std::cout << "Address of brain:     " << &brain << std::endl;
  std::cout << "Address in stringPTR: " << stringPTR << std::endl;
  std::cout << "Address of stringREF: " << &stringREF << std::endl;

  std::cout << "value of brain:     " << brain << std::endl;
  std::cout << "value in stringPTR: " << *stringPTR << std::endl;
  std::cout << "value of stringREF: " << stringREF << std::endl;

  return 0;
}