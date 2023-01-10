#pragma once
#include "plugin.hpp"

namespace Interface{
class Filter{
public:
    virtual ~Filter(){}
    virtual int process(int i) = 0;
};
}

#define REGISTER_FILTER(name,Class)  PLUGIN_REGISTER_TYPE(Interface::Filter,name,Class)

/**
 * @brief Create a Filter instance
 * 
 * @param name plugin name
 * @return Interface::Filter* 
 */
inline Interface::Filter* createFilter(const char* name)
{
    return TinyLib::PluginManager<Interface::Filter>::getInstance().create(name);
}

void removePlugin(const char* name="")
{
    TinyLib::PluginManager<Interface::Filter>::getInstance().remove(name);
}