#include "filter_plugin.hpp"

namespace Impl{
class Add : public Interface::Filter
{
public:
    Add():_base(1)
    {

    }
    ~Add(){}
    int process(int i)
    {
        return _base + i;
    }
private:
    int _base;
};
// register inside the namespace
REGISTER_FILTER("add",Add);
}

