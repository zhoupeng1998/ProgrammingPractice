## Installing gtest in Ubuntu

```
sudo apt update
sudo apt install cmake libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib
```