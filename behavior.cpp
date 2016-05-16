#include "behavior.h"

status behavior::tick() {
  if (status_ != BH_RUNNING) on_init();

  status_ = update();

  if (status_ != BH_RUNNING) on_terminate(status_);

  return status_;
}

status behavior::on_terminate(status status) {
  return status;
}

void behavior::reset() {
  status_ = BH_INVALID;
}

void behavior::abort() {
  on_terminate(BH_ABORTED);
  status_ = BH_ABORTED;
}

bool behavior::is_terminated() const {
  return status_ == BH_SUCCESS || status_ == BH_FAILURE;
}

bool behavior::is_running() const {
  return status_ == BH_RUNNING;
}

status behavior::get_status() const {
  return status_;
}
