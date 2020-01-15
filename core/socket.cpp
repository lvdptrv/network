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
        : handle_(::socket(domain, type /* SOCK_NONBLOCK*/, protocol))
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

    const int GetHandle(void) const noexcept {
        return handle_;
    }

    ~Impl(void) noexcept
    {
        if (handle_ >= 0)
        {
            ::close(handle_);
        }
    }

    void SetHandle(int handle) noexcept {
        handle_ = handle;
    }
    
    int handle_;
};

Socket::Socket(int domain, int type, int protocol)
    : impl_(std::make_unique<Impl>(domain, type, protocol))
{
}

const int Socket::GetHandle(void) const noexcept {
    return impl_->GetHandle();
}

void Socket::SetHandle(int handle) noexcept {
    impl_->SetHandle(handle);
}

Socket::Socket(int handle) noexcept
    : impl_(std::make_unique<Impl>(handle)) {}

Socket::~Socket(void) noexcept = default;

} // namespace vldptrv::network