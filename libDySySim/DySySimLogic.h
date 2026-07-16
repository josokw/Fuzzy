#ifndef DYSYSIMLOGIC_H
#define DYSYSIMLOGIC_H

#include "ErrorCodes.h"
#include "SimBlock.h"

namespace dysysim {

class And : public SimBlock
{
public:
   And();
   ~And() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<And>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override { out_ = andInputs(); }

private:
    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Or : public SimBlock
{
public:
   Or();
   ~Or() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Or>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override { out_ = orInputs(); }

private:
    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

class Not : public SimBlock
{
public:
   Not();
   ~Not() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<Not>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override { out_ = notInput(); }

private:
    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

class NAnd : public SimBlock
{
public:
   NAnd();
   ~NAnd() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<NAnd>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override { out_ = is_0(andInputs() ? 1.0 : 0.0); }

private:
    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

class NOr : public SimBlock
{
public:
   NOr();
   ~NOr() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<NOr>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override { out_ = is_0(orInputs() ? 1.0 : 0.0); }

    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

class XOr : public SimBlock
{
public:
   XOr();
   ~XOr() override = default;

   std::shared_ptr<SimBlock> create() override
   {
      return std::make_shared<XOr>();
   }

    [[nodiscard]] std::vector<std::error_code>
    config(const SimBlock::configData_t &config) override;

    void exe() override
    {
       auto nand = is_0(andInputs());
       out_ = convert01(nand and orInputs());
    }

    [[nodiscard]] std::vector<std::error_code>
    configDataIsOK(const SimBlock::configData_t &config) const override;
};

} // namespace dysysim

#endif
