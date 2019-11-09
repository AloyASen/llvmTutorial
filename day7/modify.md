$ clang++ load.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -fno-rtti -o toy

case 2::
--------
$ clang++ store.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -fno-rtti -o toy

case 3
-------

$ clang++ insert.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -fno-rtti -o toy

case 4
-------

$ clang++ extract.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -fno-rtti -o toy
