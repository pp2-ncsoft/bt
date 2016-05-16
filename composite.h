#pragma once

#include "behavior.h"
#include <memory>
#include <vector>

using behaviors = std::vector<std::shared_ptr<behavior>>;

class composite : public behavior {
public:
  bool add_child(std::shared_ptr<behavior> p);
  bool remove_child(std::shared_ptr<behavior> p);
  void clean_children();

protected:
  behaviors children_;
};

class sequence : public composite {
public:
  void on_init() override;
  status update() override;

private:
  behaviors::iterator current_child_;
};

class selector : public composite {
public:
  void on_init() override;
  status update() override;

private:
  behaviors::iterator current_child_;
};

class random_selector : public composite {
public:
  void on_init() override;
  status update() override;

private:
  behaviors::iterator current_child_;

  size_t get_index();
  std::vector<int> possibilities_;
};
