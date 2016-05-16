#include "conditions.h"
#include <iostream>

status is_hero_in_area::update() {
  std::cout << "is_hero_in_area update called" << std::endl;
  return BH_SUCCESS;
}
