#include "BaseVector.h"

BaseVector::BaseVector()
{
    num_elem_ = 0;
}

BaseVector::BaseVector(const BaseVector &base)
{
    num_elem_ = base.num_elem_;
}

BaseVector::~BaseVector() = default;
