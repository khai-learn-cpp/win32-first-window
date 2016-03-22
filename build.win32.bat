
g++ -Wall -Wextra -std=c++14 -c -o ./main.o ./main.cpp
windres resource.rc -O coff -o resource.res
g++ -mwindows -o ./main.exe ./main.o ./resource.res
