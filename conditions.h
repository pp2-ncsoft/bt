#pragma once
#include "behavior.h"

class condition : public behavior {
public:
  virtual status update() = 0;
};

class is_hero_in_area : public condition {
public:
  status update() override;
};
