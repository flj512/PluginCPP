#include <iostream>
#include <dlfcn.h>
#include "filter_plugin.hpp"

int main()
{
    auto add_lib = dlopen("libadd.so",RTLD_LAZY);
    auto square_lib = dlopen("libsquare.so",RTLD_LAZY);
    if(add_lib == nullptr || square_lib == nullptr){
        std::cout<<"load shared library fail"<<std::endl;
        return 1;
    }

    auto add = createFilter("add");
    if (add == nullptr){
        std::cout <<"create add filter fail"<<std::endl;
        return 1;
    }
    auto square = createFilter("square");
    if (square == nullptr){
        std::cout <<"create square filter fail"<<std::endl;
        return 1;
    }

    std::cout<<"add filter (2) = "<< add->process(2)<<std::endl;
    std::cout<<"square filter (2) = "<< square->process(2)<<std::endl;

    delete square;
    delete add;


    removePlugin();//need to remove all the plugin before close library
    dlclose(square_lib);
    dlclose(add_lib);

    return 0;
}