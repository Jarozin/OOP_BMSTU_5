#ifndef _errors_h
#define _errors_h

#include "stdio.h"
#include <exception>

class baseError : public std::exception
{
public:
  baseError(const char *filename, const char *classname, int line,
            const char *time, const char * info = "Error") noexcept
  {
    sprintf(err_info_, "\nFile name: %s\nClass: %s\nLine#: %d\nTime: %sInfo: %s", filename, classname, line, time, info);
  }
  virtual const char *what() const noexcept override
  {
    return err_info_;
  }

protected:
  char err_info_[250];
};

class memError : public baseError
{
public:
  memError(const char * filename, const char * classname, int line,
           const char *time, const char * info = "Memory error") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};

class emptyError : public baseError
{
public:
  emptyError(const char * filename, const char * classname, int line,
             const char *time, const char * info = "Try to use empty vector") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};

class indexError : public baseError
{
public:
  indexError(const char * filename, const char * classname, int line,
             const char *time, const char * info = "Index out of range") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};

class zero_divError : public baseError
{
public:
  zero_divError(const char * filename, const char * classname, int line,
                const char *time, const char * info = "Zero division error") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};

class deletedObj : public baseError
{
public:
  deletedObj(const char * filename, const char * classname, int line,
             const char *time, const char * info = "Work with deleted object") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};


class iteratorPtrError : public baseError
{
public:
  iteratorPtrError(const char * filename, const char * classname, int line,
             const char *time, const char * info = "Iterators have different pointers") noexcept
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_; }
};
#endif /* _errors_h */
