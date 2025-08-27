#include "../incs/HumanA.hpp"

#include <iostream>

HumanA::HumanA(const std::string& name, Weapon& weapon) : name(name), weapon(weapon) {}

void HumanA::attack() const {
  std::cout << this->name << " attack with their "
            << this->weapon.getType() << std::endl;
}
