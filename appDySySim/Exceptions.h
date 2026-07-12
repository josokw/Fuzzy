#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <source_location>
#include <string>

namespace dysysim {

class FactoryAddError : public std::exception
{
public:
   explicit FactoryAddError(
      const std::string &key,
      const std::source_location &loc = std::source_location::current())
      : key_{key}
      , location_{loc}
   {
   }
   const char *what() const noexcept override
   {
      return "SimBlockFactory add() error";
   }
   const auto &getKey() const { return key_; }
   const auto &getLocation() const { return location_; }

private:
   const std::string key_;
   const std::source_location location_;
};

class FactoryUnknownTypeError : public std::exception
{
public:
   explicit FactoryUnknownTypeError(
      const std::string &type,
      const std::source_location &loc = std::source_location::current())
      : type_{type}
      , location_{loc}
   {
   }
   const char *what() const noexcept override
   {
      return "SimBlockFactory unknown type error";
   }
   const auto &getType() const { return type_; }
   const auto &getLocation() const { return location_; }

private:
   const std::string type_;
   const std::source_location location_;
};

class SyntaxError : public std::exception
{
public:
   explicit SyntaxError(
      int lineNumber, const std::string &codeLine,
      const std::source_location &loc = std::source_location::current())
      : lineNumber_{lineNumber}
      , codeLine_{codeLine}
      , location_{loc}
   {
   }
   const char *what() const noexcept override { return "Parser syntax error"; }
   int getLineNumber() const { return lineNumber_; }
   const auto &getCodeLine() const { return codeLine_; }
   const auto &getLocation() const { return location_; }

private:
   const int lineNumber_;
   const std::string codeLine_;
   const std::source_location location_;
};

class ConfigError : public std::exception
{
public:
   explicit ConfigError(
      const std::source_location &loc = std::source_location::current())
      : location_{loc}
   {
   }
   const char *what() const noexcept override
   {
      return "Parser config error\n";
   }
   const auto &getLocation() const { return location_; }

private:
   const std::source_location location_;
};

class ModelError : public std::exception
{
public:
   explicit ModelError(
      const std::source_location &loc = std::source_location::current())
      : location_{loc}
   {
   }
   const char *what() const noexcept override { return "Model error\n"; }
   const auto &getLocation() const { return location_; }

private:
   const std::source_location location_;
};

} // namespace dysysim

#endif
