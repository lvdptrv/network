#pragma once

#include <string_view>
#include <memory>

namespace vldptrv
{
struct Configuration
{
    Configuration *instance(void) {
        static Configuration configuration;
        return &configuration;
    }

    std::string Get(const std::string &name);

    ~Configuration(void) noexcept;

private:
    Configuration(void);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv