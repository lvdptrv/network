#include <memory>
#include <optional>
#include <string>
#include <filesystem>

namespace vldptrv::network::http {
    struct Header {
    enum class RequestMethod {
        get, post, head, options,
    };

    enum class Scheme {
        none, http, https,
    };

    enum class Version {
        http10, http11, http2,
    };

    explicit Header(std::string_view data);

    RequestMethod RequestMethod(void);
    std::optional<std::string> &QueryParam(std::string_view key);
    std::filesystem::path &Path(void);
    Scheme Scheme(void);
    Version Version(void);
    std::string &Body(void);
    std::string &Field(std::string_view key);

    ~Header(void) noexcept;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}