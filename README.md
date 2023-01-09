# PluginCPP
A tiny utils for managing cpp plugin, there is no dependences and only one header file.  

# Usage
The folder `example` contains an example to demonstrate how to use.

## Define plugin
```
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
```
## Implement plugin
don't need to create header files
```
#include "filter_plugin.hpp"

namespace Impl{
class Square : public Interface::Filter
{
public:
    Square()
    {

    }
    ~Square(){}
    int process(int i)
    {
        return i*i;
    }
};
// register inside the namespace
REGISTER_FILTER("square",Square);
}
```
## Use plugin
```
/**
 * @brief Create a Filter instance
 * 
 * @param name plugin name
 * @return Interface::Filter* 
 */
Interface::Filter* createFilter(const char* name)
{
    return TinyLib::PluginManager<Interface::Filter>::getInstance().create(name);
}
```
