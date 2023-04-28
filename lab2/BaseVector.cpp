#include "BaseVector.h"

BaseVector::BaseVector()
{
    num_elem_ = 0;
}

BaseVector::BaseVector(const BaseVector &base)
{
    num_elem_ = base.num_elem_;
}

BaseVector::~BaseVector()
{

}


int BaseVector::get_size() const
{
    return num_elem_;
}

bool BaseVector::is_empty() const
{
    return !num_elem_;
}
