#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "socket.hpp"

namespace vldptrv::network
{
struct Connection
{
    Connection(const Socket &listener);
    std::vector Read(size_t size);
    void Write(std::string_view &data);
    void Close(void) const noexcept;
    ~Connection(void) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv::network