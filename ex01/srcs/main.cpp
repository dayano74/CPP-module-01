#include "Zombie.hpp"

int main(void) {
  Zombie* heapZombie = newZombie("HeapFoo");
  heapZombie->announce();
  delete heapZombie;

  std::cout << "-----" << std::endl;

  randomChump("StackBar");
  return 0;
}