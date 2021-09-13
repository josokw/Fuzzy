#ifndef EXCEPTIONS_H
#define EXECPTIONS_H

#include <exception>
#include <sstream>

namespace dysysim {

class FactoryAddError : public std::exception
{
public:
   explicit FactoryAddError(const std::string &key)
      : key_{key}
   {
   }
   const char *what() const throw() override
   {
      return "SimBlockFactory add() error";
   }
   const auto &getKey() const { return key_; }

private:
   const std::string key_;
};

class FactoryUnknownTypeError : public std::exception
{
public:
   explicit FactoryUnknownTypeError(const std::string &type)
      : type_{type}
   {
   }
   const char *what() const throw() override
   {
      return "SimBlockFactory unknown type error";
   }
   const auto &getType() const { return type_; }

private:
   const std::string type_;
};

class ConfigError : public std::exception
{
public:
   const char *what() const throw() { return "Parser config error\n"; }
};

class ModelError : public std::exception
{
public:
   const char *what() const throw() { return "Model error\n"; }
};

} // namespace dysysim

#endif
