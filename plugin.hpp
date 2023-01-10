/**
 * @file plugin.hpp
 * @author flj
 * @brief plugin for c++
 * @version 0.1
 * @date 2023-01-09
 * 
 * @copyright Copyright (c) 2023
 * 
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 */
#pragma once

#include <stdexcept>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>


namespace TinyLib {
/**
 * @brief a utils to manage cpp plugins or replace Factory mode.
 * 
 * @tparam T Note: the T should have a default constructor.
 */
template <typename T>
class PluginManager {
 public:
  typedef T* TypePtr;
  typedef std::function<TypePtr()> InstanceCreator;

  static PluginManager& getInstance() {
    static PluginManager inst;
    return inst;
  }

  void registerCreator(const std::string& name, const InstanceCreator& creator,
                       const std::string& type) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (creators_.find(name) != creators_.end()) {
        throw std::runtime_error( name + " has already register for "+ type);
    } else {
      creators_[name] = creator;
    }
  }
  void remove(const std::string& name = ""){
    std::lock_guard<std::mutex> lock(mtx_);
    if (name.empty()){
        creators_.clear();
    }else{
        creators_.erase(name);
    }
  }
/**
 * @brief create an instance by class name, the name should be same as in PLUGIN_REGISTER_TYPE
 * 
 * @param name class name
 * @return TypePtr 
 */
  TypePtr create(const std::string& name) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = creators_.find(name);
    if (it == creators_.end()) {
      return nullptr;
    } else {
      return (it->second)();
    }
  }

 private:
  PluginManager() = default;
  PluginManager(const PluginManager&) = delete;
  PluginManager(const PluginManager&&) = delete;

  std::mutex mtx_;
  std::map<std::string, InstanceCreator> creators_;
};
}

/**
 * @brief A macro used to to automatically register class creator. 
 * This macro create a class and a static instance of that class.
 * The static instance will register creator when the library(static or shared) is loaded.
 * Since the static object is never referenced by other code,so be careful
 * about compiler's optimization. we must to pass always link flag to linker to
 * prevent optimization.
 */
#define PLUGIN_REGISTER_TYPE(Type, name, Class)                              \
  class __Register##Class {                                                  \
   public:                                                                   \
    __Register##Class() {                                                    \
      TinyLib::PluginManager<Type>::getInstance().registerCreator(           \
          name, []() { return new Class(); }, #Type);                        \
    }                                                                        \
  };                                                                         \
  static __Register##Class __register_instance_##Class
