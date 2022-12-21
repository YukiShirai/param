/*
MIT License
Copyright (c) 2019 - present H. Watanabe
The latest version is available at
https://github.com/kaityo256/params

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _PARAM_HPP_
#define _PARAM_HPP_

// #pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace param
{

  typedef std::map<std::string, std::string> ptype;
  class parameter
  {
  private:
    ptype params;
    bool valid;

    bool contains(std::string &key) const;

  public:
    parameter(const std::string filename);


    explicit operator bool() const;


    void loadfromfile(const std::string filename);

    void readfromstream(std::istream &is);

    void check_key(std::string &key) const;


    template <class T>
    T get(std::string);

    template <class T>
    T get(std::string, T value);
  };

  template <>
  bool parameter::get<bool>(std::string key, bool value);

  template <>
  bool parameter::get(std::string key);

  template <>
  int parameter::get(std::string key, int value);

  template <>
  int parameter::get(std::string key);

  template <>
  double parameter::get(std::string key, double value);

  template <>
  double parameter::get(std::string key);

} // namespace param
#endif
