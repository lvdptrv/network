#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace vldptrv::network
{
struct Connection
{
    Connection(void);
    static void Open(std::string_view to);
    std::string Read(size_t size);
    size_t Write(std::string_view data);
    void Close(void) const noexcept;
    ~Connection(void) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv::network