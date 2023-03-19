g++ -c .\server\interfaces.cpp -o .\server\interfaces.o
g++ -c .\server\server.cpp -o .\server\server.o

move /Y .\server\server.o .\client
move /Y .\server\interfaces.o .\client

g++ -c ./client/client.cpp  -o ./client/client.o

g++ ./client/client.o ./client/interfaces.o ./client/server.o    -o ./client.exe

"client.exe"

pause