#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <thread>
#include "composite.h"
#include "conditions.h"
#include "actions.h"
using namespace std::chrono_literals;

int main() {

  auto root = std::make_shared<sequence>();
  auto is_hero = std::make_shared<is_hero_in_area>();
  root->add_child(is_hero);
  auto attack_hero = std::make_shared<attack>();
  root->add_child(attack_hero);

  while (1) {
    root->tick();
    std::this_thread::sleep_for(1s);
  }


  getchar();
  return 0;
}
