#include "BaseIter.h"
BaseIter::BaseIter()
{
  index_ = 0;
  num_elem_ = 0;
}
BaseIter::BaseIter(const BaseIter &iter)
{
  index_ = iter.index_;
  num_elem_ = iter.num_elem_;
}

BaseIter::~BaseIter() = default;
