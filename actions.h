#pragma once
#include "behavior.h"

class action : public behavior {
  //actions() = default;
  //~actions() = default;
  virtual status update() = 0;
};

class attack : public action {
public:
  status update() override;
};
