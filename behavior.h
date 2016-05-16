#pragma once
#include "declare.h"

class behavior {
public:
  behavior() = default;
  virtual ~behavior() = default;

  virtual void on_init() {}
  virtual status on_terminate(status status);
  virtual status update() = 0;
  status tick();

  void reset();
  void abort();
  bool is_terminated() const;
  bool is_running() const;
  status get_status() const;

protected:
  status status_;
};
