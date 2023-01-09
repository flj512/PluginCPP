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