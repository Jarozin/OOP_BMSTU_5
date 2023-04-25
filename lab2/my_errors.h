#ifndef _errors_h
#define _errors_h

#include <string.h>

#include <exception>

class baseError : public std::exception
{
public:
  baseError(std::string filename, std::string classname, int line,
            const char *time, std::string info = "Error")
  {
    err_info_ = "\nFile name: " + filename + "\nClass: " + classname +
                "\nLine#: " + std::to_string(line) + "\nTime: " + time +
                "Info: " + info;
  }
  virtual const char *what() const noexcept override
  {
    return err_info_.c_str();
  }

protected:
  std::string err_info_;
};

class memError : public baseError
{
public:
  memError(std::string filename, std::string classname, int line,
           const char *time, std::string info = "Memory error")
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_.c_str(); }
};

class emptyError : public baseError
{
public:
  emptyError(std::string filename, std::string classname, int line,
             const char *time, std::string info = "Try to use empty vector")
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_.c_str(); }
};

class indexError : public baseError
{
public:
  indexError(std::string filename, std::string classname, int line,
             const char *time, std::string info = "Index out of range")
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_.c_str(); }
};

class zero_divError : public baseError
{
public:
  zero_divError(std::string filename, std::string classname, int line,
                const char *time, std::string info = "Zero division error")
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_.c_str(); }
};

class deletedObj : public baseError
{
public:
  deletedObj(std::string filename, std::string classname, int line,
             const char *time, std::string info = "Work with deleted object")
      : baseError(filename, classname, line, time, info){};
  virtual const char *what() const noexcept { return err_info_.c_str(); }
};

#endif /* _errors_h */