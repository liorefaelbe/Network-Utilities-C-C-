#include <cstdlib>    // atoi

#include "server.hpp" // Server

using namespace std;
using namespace ilrd_166_7;

/*******************************Main****************************************/

int main(int argc, char* argv[])
{
    (void)argc;

    Server s(atoi(argv[1]));
    s.Run();
 
    return (0);
}