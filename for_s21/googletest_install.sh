#!/bin/bash
cd /opt/goinfre/$USER
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER:STRING="/usr/local/bin/g++" ..
make
cp -a lib/*.a ../../homebrew/lib
cp -a ../googletest/include/gtest ../../homebrew/include
cd $HOME
if [ ! -f ".zshrc" ]; then
touch .zshrc
fi
echo 'export PATH="/usr/local/Qt-6.6.2/bin:$PATH"' >> .zshrc
echo 'CPATH+=/opt/goinfre/$USER/homebrew/include' >> .zshrc
echo 'LIBRARY_PATH+=/opt/goinfre/$USER/homebrew/lib' >> .zshrc
