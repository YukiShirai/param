#include "param.hpp"

namespace param
{

  typedef std::map<std::string, std::string> ptype;

    bool parameter::contains(std::string &key) const{
        return params.find(key) != params.end();
    }

    parameter::parameter(const std::string filename): valid(true){
        loadfromfile(filename);
    }
    parameter::operator bool() const
    {
      return valid;
    };


    void parameter::loadfromfile(const std::string filename)
    {
      std::ifstream is(filename);
      if (is.fail())
      {
        std::cerr << "Could not open file " << filename << std::endl;
        valid = false;
      }
      readfromstream(is);
    }


    void parameter::readfromstream(std::istream &is)
    {
      std::string line;
      while (getline(is, line))
      {
        if (line.length() > 0 && line[0] == '#')
        {
          continue;
        }
        size_t index = line.find("=");
        if (std::string::npos != index)
        {
          std::string key = line.substr(0, index);
          std::string value = line.substr(index + 1, line.length());
          params.insert(ptype::value_type(key, value));
        }
      }
    }


    void parameter::check_key(std::string &key) const
    {
      if (!contains(key))
      {
        std::cerr << "No such key: " << key << std::endl;
        std::abort();
      }
    }

    template <class T>
    T parameter::get(std::string)
    {
    }


    template <class T>
    T parameter::get(std::string, T value)
    {
      return value;
    }


  template <>
  bool parameter::get<bool>(std::string key, bool value)
  {
    if (!contains(key))
    {
      return value;
    }
    if ("yes" == params[key] || "Yes" == params[key])
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template <>
  bool parameter::get(std::string key)
  {
    check_key(key);
    return get<bool>(key, false);
  }

  template <>
  int parameter::get(std::string key, int value)
  {
    if (!contains(key))
    {
      return value;
    }
    return std::stoi(params[key]);
  }

  template <>
  int parameter::get(std::string key)
  {
    check_key(key);
    return get<int>(key, 0);
  }

  template <>
  double parameter::get(std::string key, double value)
  {
    if (!contains(key))
    {
      return value;
    }
    return std::stod(params[key]);
  }

  template <>
  double parameter::get(std::string key)
  {
    check_key(key);
    return get<double>(key, 0.0);
  }

} // namespace param
