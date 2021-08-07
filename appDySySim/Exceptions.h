#ifndef EXCEPTIONS_H
#define EXECPTIONS_H

#include <exception>
#include <sstream>

namespace dysysim {

class FactoryInitError : public std::exception
{
public:
   explicit FactoryInitError(const std::string &key)
      : key_{key}
   {
   }
   const char *what() const throw() override
   {
      return "SimBlockFactory init() error";
   }
   const auto &getKey() const { return key_; }

private:
   const std::string key_;
};

class SyntaxError : public std::exception
{
public:
   explicit SyntaxError(int lineNumber, const std::string &codeLine)
      : lineNumber_{lineNumber}
      , codeLine_{codeLine}
   {
   }
   const char *what() const throw() { return "Parser syntax error"; }
   int getLineNumber() const { return lineNumber_; }
   const auto &getCodeLine() const { return codeLine_; }

private:
   const int lineNumber_;
   const std::string codeLine_;
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
