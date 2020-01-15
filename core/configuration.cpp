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
    Impl(void) try
    {
        boost::property_tree::read_json("../configurations/application.json", root_);        
        for(auto &parameter: root_) {
            parameters_[parameter.first] = parameter.second.get_value<std::string>();
        }
    }
    catch (boost::property_tree::ptree_error &e)
    {
    }

    std::string Get(const std::string &name) {
        return parameters_[name];
    }

private:
    std::map<std::string, std::string> parameters_;
    boost::property_tree::ptree root_;
};

Configuration::Configuration(void)
    : impl_(std::make_unique<Impl>()) {}

std::string Configuration::Get(const std::string &name) {
    return impl_->Get(name);
}

Configuration::~Configuration(void) noexcept = default;
} // namespace vldptrv