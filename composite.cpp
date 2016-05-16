#include "composite.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <assert.h>
// -------------------------------------
// composite
// -------------------------------------
bool composite::add_child(std::shared_ptr<behavior> p) {
  auto it = std::find(children_.begin(), children_.end(), p);
  if (it != children_.end()) return false;

  children_.push_back(p);
  return true;
}

bool composite::remove_child(std::shared_ptr<behavior> p) {
  auto it = std::find(children_.begin(), children_.end(), p);
  if (it != children_.end()) {
    children_.erase(it);
    return true;
  }
  return false;
}

void composite::clean_children() {
  children_.clear();
}

// -------------------------------------
// sequence 
// -------------------------------------
void sequence::on_init() {
  current_child_ = children_.begin();
}

status sequence::update() {
  while (true) {
    auto it = current_child_->get();
    if (!it) return BH_INVALID;

    status rtn = it->tick();

    if (rtn != BH_SUCCESS) return rtn;
    
    // 다음 leaf node로 이동
    if (++current_child_ == children_.end()) return BH_SUCCESS;
  }
  return BH_INVALID;
}

// -------------------------------------
// selector 
// -------------------------------------
void selector::on_init() {
  current_child_ = children_.begin();
}

status selector::update() {
  while (true) {
    auto it = current_child_->get();
    if (!it) return BH_INVALID;

    status rtn = it->tick();
    // success or running  같은것으로 간주함
    if (rtn != BH_FAILURE) return rtn;

    // 다음 leaf node로 이동
    if (++current_child_ == children_.end()) return BH_FAILURE;
  }
  return BH_INVALID;
}

// -------------------------------------
// random selector
// -------------------------------------
void random_selector::on_init() {
  current_child_ = children_.begin();
}

status random_selector::update() {
  auto index = get_index();

  // success or running  같은것으로 간주함
  status rtn = children_[index]->tick();
  if (rtn == BH_SUCCESS || rtn == BH_SUCCESS || rtn == BH_FAILURE) return rtn;

  return BH_INVALID;
}

size_t random_selector::get_index() {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, 100);
  int random_value = distribution(generator);

  auto index = -1;
  for (size_t i = 0; i < possibilities_.size(); i++) {
    if (i == 0) {
      if (random_value <= possibilities_[i]) index = i;
    }
    else {
      if (random_value > possibilities_[i-1] && random_value <= possibilities_[i]) index = i;
    }

    if (index > 0) break;
  }

  assert(index > -1); // 만약 조건이 false 이면

  return index;
}
