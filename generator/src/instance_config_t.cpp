#include "instance_config_t.hpp"

EMIR::instance_config_t::instance_config_t(const string& name,
                                           const string& path,
                                           const string& stamp,
                                           int type)
  : name_(name)
  , path_(path)
  , stamp_(stamp)
  , type_(type)
{
}

EMIR::instance_config_t::instance_config_t(void)
  : name_()
  , path_()
  , stamp_()
  , type_(-1)
{
}

EMIR::instance_config_t::~instance_config_t(void)
{
}

void
EMIR::instance_config_t::set(const string& name,
                             const string& path,
                             const string& stamp,
                             int type)
{
    name_ = name;
    path_ = path;
    stamp_ = stamp;
    type_ = type;

}
