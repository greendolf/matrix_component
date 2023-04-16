g++ -c .\source\server\interfaces.cpp -o .\build\server\interfaces.o
g++ -c .\source\server\component.cpp -o .\build\server\component.o
g++ -c .\source\server\container.cpp -o .\build\server\container.o

g++ -c .\source\server\dllmanager.cpp -o .\build\server\dllmanager.o

g++ -shared .\build\server\container.o .\build\server\component.o .\build\server\interfaces.o -o .\build\server\component.dll -Wl,--kill-at

g++ -shared .\build\server\dllmanager.o -o .\build\server\dllmanager.dll -Wl,--kill-at

xcopy .\source\server\interfaces.h  .\build\client /Y

xcopy .\build\server\dllmanager.dll  .\build\client /Y

g++ -c ./source/client/client.cpp  -o ./build/client/client.o
g++ -c ./source/client/wrapper.cpp -o ./build/client/wrapper.o

g++ ./build/client/client.o ./build/client/wrapper.o -o ./client.exe

"client.exe"

pause