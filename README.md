# PluginCPP
A tiny utils for managing cpp plugin, there is no dependences and only one header file.  
  
Another way to use this library is building all the implementation in one library so that  
avoid creating a factory class and many codes like `if(name=="foo") new Foo()`.

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
inline Interface::Filter* createFilter(const char* name)
{
    return TinyLib::PluginManager<Interface::Filter>::getInstance().create(name);
}
```
```
auto square = createFilter("square");
if (square == nullptr){
    std::cout <<"create square filter fail"<<std::endl;
    return 1;
}

std::cout<<"square filter (2) = "<< square->process(2)<<std::endl;
```
