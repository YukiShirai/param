# Single-header C++ library for parameter file
This repository enables the user to load parameter files without recompiling. 

This repo is originally from [here](https://github.com/kaityo256/param).

# Dependencies
- Ubuntu 20.04
- CMake 3.15+
- C++11
  
# Build and Install 
- First you can install all dependencies using:
```
sudo apt-get install build-essential cmake
```
- Then, you can git clone this repo on your preferred directory. I use `~` and thus the project would be located as `~/param`.
- You need to build the project as follows:
```
cd ~/param
mkdir build
cd build
cmake ..
cmake --build .
sudo make install . 
```
- Note that if you want to remove (i.e., uninstall) the installed files, you can run the following command at `~/param/build`. 
```
sudo xargs rm < install_manifest.txt
```
- and that's it! You can use the following CMake commands in your CMakeLists.txt, in order to use the param. 
```
find_package(param REQUIRED)

target_link_libraries(BINARY_NAME
	                    PUBLIC
		                  param)
```
- In your C++ codes, you can then include the param as follows:
```
  #include "param/param.hpp"
  #include <unistd.h>
  #include <stdio.h>
  #include <iostream>

  int main(){
    std::string filename = "param.cfg";
    param::parameter param(filename);
    if (!param)
    {
      std::cerr << "Could not find file " << filename << std::endl;
      std::abort();
    }
    return 0;
  }
```
- Note that if your CMake project complains during your `cmake ..` like:
```
/usr/bin/ld: cannot find -lparam
```
- then check where your `libparam.so` was installed. It can be `/usr/local/lib`. If that's the case, crate symbolic link as follows:
```
sudo ln -s /usr/local/lib/libparam.so /usr/lib/libparam.so
```



# Usage

Pass the file name to the constructor.

```cpp
param::parameter param(filename);
```

You can check the error on reading file as

```cpp
  if (!param) {
    std::cerr << "Error occurs" << std::endl;
  }
```

The format of an input file (a parameter file) is `key=value`.

```sh
# Comment
bool=yes
int=12345
double=12.345
```

Lines starting with `#` are considered comments.

You can obtain the values by the keys.

```cpp
bool b = param.get<bool>("bool");
int  i = param.get<int>("int");
double d = param.get<double>("double");
```

You can specify the default value at the second argument if a key does not exist.

```cpp
bool b = param.get<bool>("non-existing key", false);
int  i = param.get<int>("non-existing key", 0);
double d = param.get<double>("non-existing key", 0.0);
```

# License

This software is released under the MIT License, see [LICENSE](LICENSE).
