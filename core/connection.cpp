#include "connection.hpp"
#include "socket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <system_error>
#include <string>
#include <vector>
#include <cerrno>

namespace vldptrv::network
{
struct Connection::Impl : Socket
{
    Impl(const Socket &listener)
        : Socket(::accept4(listener.GetHandle(), reinterpret_cast<sockaddr *>(&address_), reinterpret_cast<socklen_t *>(address_.sin_zero), SOCK_NONBLOCK))
    {
        while ((GetHandle() < 0) && (EAGAIN == errno))
        {
            SetHandle(::accept4(listener.GetHandle(), reinterpret_cast<sockaddr *>(&address_), reinterpret_cast<socklen_t *>(address_.sin_zero), SOCK_NONBLOCK));
        }

        if (GetHandle() < 0)
        {
            throw std::system_error(errno, std::system_category());
        }
    }

    std::vector<char> Read(size_t size)
    {
        std::vector<char> buffer(size);
        std::basic_string_view<char> read_range(buffer.data(), buffer.size());

        do
        {
            auto recv_size = ::recv(GetHandle(), const_cast<char *>(read_range.data()), read_range.size(), MSG_NOSIGNAL);
            if (recv_size > 0)
            {
                read_range.remove_prefix(recv_size);
            }
            else if (recv_size == 0)
            {
                break;
            }
            else if (EAGAIN != errno)
            {
                throw std::system_error(errno, std::generic_category());
            }
        } while (buffer.size() < size);

        return buffer;
    }

    size_t Write(std::string_view data)
    {
        size_t total = 0;

        do
        {
            auto send_size = ::send(GetHandle(), data.data(), data.size(), MSG_NOSIGNAL);
            if (send_size > 0)
            {
                data.remove_prefix(total += send_size);
            }
            else if (send_size == 0)
            {
                break;
            }
            else if (EAGAIN != errno)
            {
                throw std::system_error(errno, std::generic_category());
            }
        } while (data.size() > 0);

        return total;
    }

    ~Impl(void) noexcept
    {
        if (GetHandle() < 0)
        {
            return;
        }
        ::shutdown(GetHandle(), SHUT_RDWR);
    }

private:
    sockaddr_in address_;
};

Connection::Connection(const Socket &listener)
    : impl_(std::make_unique<Impl>(listener)) {}

std::vector<char> Connection::Read(size_t size) {
    return impl_->Read(size);
}

Connection::~Connection(void) noexcept = default;

} // namespace vldptrv::network