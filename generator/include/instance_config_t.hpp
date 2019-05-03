#pragma once

#include <string>

using namespace std;

namespace EMIR
{

class instance_config_t
{
  public:
    string name_;
    string path_;
    string stamp_;
    int type_;

  public:
    instance_config_t(const string& name, const string& path, const string& stamp, int type);

    instance_config_t(void);
    ~instance_config_t(void);

    void set(const string& name, const string& path, const string& stamp, int type);
};
}
