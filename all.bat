g++ -c .\source\server\component.cpp -o .\build\server\component.o
g++ -c .\source\server\container.cpp -o .\build\server\container.o

g++ -shared .\build\server\container.o .\build\server\component.o -o .\build\server\component.dll -Wl,--kill-at -lole32 -loleaut32 -luser32


g++ -c .\source\server2\component.cpp -o .\build\server2\component.o
g++ -c .\source\server2\container.cpp -o .\build\server2\container.o

g++ -shared .\build\server2\container.o .\build\server2\component.o -o .\build\server2\component2.dll -Wl,--kill-at -lole32 -loleaut32 -luser32


xcopy .\source\server\interfaces.h  .\source\client /Y


g++ -c ./source/client/client.cpp  -o ./build/client/client.o
g++ -c ./source/client/wrapper.cpp -o ./build/client/wrapper.o

g++ ./build/client/client.o ./build/client/wrapper.o -o ./client.exe -Wl,--kill-at -lole32 -loleaut32 -luser32

"client.exe"

pause