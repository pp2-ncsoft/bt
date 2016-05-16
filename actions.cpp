#include "actions.h"
#include <iostream>

status attack::update() {
  std::cout << "attack update called" << std::endl;
  return BH_SUCCESS;
}
