#include "socket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <system_error>

namespace vldptrv::network
{
struct Socket::Impl
{
    Impl(int domain, int type, int protocol)
        : handle_(::socket(AF_INET, SOCK_STREAM, 0))
    {
        if (handle_ < 0)
        {
            throw std::system_error(errno, std::system_category());
        }
    }

    explicit Impl(int handle = -1)
        : handle_(-1)
    {
    }

    const int GetHandle(void) const noexcept;

    ~Impl(void) noexcept
    {
        if (handle_ >= 0)
        {
            ::close(handle_);
        }
    }

private:
    int handle_;
};

Socket::Socket(int domain, int type, int protocol)
    : impl_(std::make_unique<Impl>(domain, type | SOCK_NONBLOCK, protocol))
{
}

int Socket::GetHandle(void) const noexcept {
    return impl_->GetHandle();
}

Socket::Socket(int handle) noexcept
    : impl_(std::make_unique<Impl>(handle)) {}

} // namespace vldptrv::network