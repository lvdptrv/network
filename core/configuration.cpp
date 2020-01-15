#include "configuration.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <map>
#include <variant>
#include <string>

namespace vldptrv
{
struct Configuration::Impl
{
    Impl(std::string_view file) try
    {
        boost::property_tree::read_json("../configurations/application.json", root_);        
        for(auto &parameter: root_) {
            parameters_[parameter.first] = parameter.second.get_value<std::string>();
        }
    }
    catch (boost::property_tree::ptree_error &e)
    {
    }

private:
    std::map<std::string, std::variant<std::string, uint64_t>> parameters_;
    std::string listen_hostname_ = "localhost";
    boost::property_tree::ptree root_;
};

Configuration::Configuration(std::string_view file)
    : impl_(std::make_unique<Impl>(file)) {}

Configuration::~Configuration(void) noexcept = default;
} // namespace vldptrv