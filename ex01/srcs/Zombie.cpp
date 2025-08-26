#include "../incs/Zombie.hpp"

Zombie::Zombie() : name("") {}

Zombie::Zombie(const std::string& name) : name(name) {
}

Zombie::~Zombie() {
  std::cout << name << ": Destructed!" << std::endl;
}

void Zombie::setName(const std::string& n) { this->name = n; }

void Zombie::announce(void) {
  std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
