#pragma once

#include <string_view>
#include <memory>

namespace vldptrv
{
struct Configuration
{
    Configuration(std::string_view file = "../configurations/application.json");
    ~Configuration(void) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv