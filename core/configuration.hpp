#pragma once

#include <memory>

namespace vldptrv::network
{
struct Configuration
{
    Configuration(void) noexcept;
    static Configuration *instance(void);
    void Store(std::string_view key, std::string_view value);
    template<typename T> T &Load(std::string_view key);
    void Remove(std::string_view key);
    void Refresh(void);
    ~Configuration(void) noexcept;

private:
    Configuration(void);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv::network