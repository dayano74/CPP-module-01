#include "../incs/Harl.hpp"

#include <iostream>

void Harl::debug(void) {
  std::cout
    << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. "
    << "I really do!" << std::endl;
}

void Harl::info(void) {
  std::cout
    << "I cannot believe adding extra bacon costs more money. "
    << "You didn’t put enough bacon in my burger! "
    << "If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void) {
  std::cout
    << "I think I deserve to have some extra bacon for free. "
    << "I've been coming for years, whereas you started working here just last month."
    << std::endl;
}

void Harl::error(void) {
  std::cout
    << "This is unacceptable! I want to speak to the manager now."
    << std::endl;
}

void Harl::complain(std::string level) {
  typedef void (Harl::*Action)();
  struct Entry { const char* key; Action fn; };
  static const Entry table[] = {
    {"DEBUG",   &Harl::debug},
    {"INFO",    &Harl::info},
    {"WARNING", &Harl::warning},
    {"ERROR",   &Harl::error},
  };
  for (size_t i = 0; i < sizeof(table)/sizeof(table[0]); ++i) {
    if (level == table[i].key){
      (this->*table[i].fn)();
      return;
    }
  }
}
