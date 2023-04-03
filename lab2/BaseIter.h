#ifndef BaseIter_h
#define BaseIter_h
#include <iterator>
    class BaseIter
{
public:
    BaseIter();
    BaseIter(const BaseIter&);
    virtual ~BaseIter() = default;;
    virtual explicit operator bool() const = 0;
protected:
    int index = 0;
    int num_elem = 0;
};

#endif /* BaseIter_h */
