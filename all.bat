g++ -c .\server\interfaces.cpp -o .\server\interfaces.o
g++ -c .\server\server.cpp -o .\server\server.o

xcopy .\server\server.o .\client\build /Y
xcopy .\server\interfaces.o .\client\build /Y
xcopy .\server\interfaces.h .\client\source /Y

g++ -c ./client/source/client.cpp  -o ./client/build/client.o
g++ -c ./client/source/wrapper.cpp -o ./client/build/wrapper.o

g++ ./client/build/client.o ./client/build/wrapper.o ./client/build/interfaces.o ./client/build/server.o    -o ./client.exe

"client.exe"

pause