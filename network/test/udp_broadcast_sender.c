#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // sleep
#include <arpa/inet.h>  // socket
#include <stdlib.h>     // atoi

#include "network_utils.h" // utils

int main(int argc, char* argv[])
{
    (void)argc;

    struct sockaddr_in broadcast_addr = {0};
    char message[] = "\n \
                        \033[33m99999999     9999999999999999\n \
                  99999999999999999999$$$$$999999$$9999\n \
                9999999$$$$$$$9999$$$$9999$$$$$$$$$$$999\n \
              9999$$$$$$$$$999$$$9999$$$$$$$999$$$$$9999\n \
            9999$$$$$$$9999$$$999$$$$$$$$$99999999$$999\n \
           9999$$$$9999999$$99999999999999999999$$$999\n \
          9999$$9999999999999XXXXXXXXXX999999XX99$999\n \
          999$$9999999999999999XXXXXXXX9999999XX999\n \
          9999999$$$999XX99999999XXXXX99   99999X999\n \
          9999X99999XXX99000099999XXX99    9999 999999\n \
           999XXXXXXX99      999999XX99      9   99X999\n \
          999XXXXXXXX99        99 9XXX99          9XX9999\n \
         9999XXXXXXXX99           9XXXX99         9XXXX9999\n \
        9999XXXXXXXXX99          99XXXXX999      99XXXXXX9999\n \
       999XXXXXXXXXXX999        99XXXXXXXXX999999XXXXX22222X999\n \
      999XXXXXXXXXXXXXX999    999XXXXXXXXXXXXXXXXXXXXX22222XX999\n \
     999XXXXX22222XXXXXXXX9999XXXXXXXXXXXXXXXXXXXX99999XXXXXX9999\n \
    9999XXX222222XXXX9999XXXXXXXXXXXXXXXXXXXXXX999    999XXXX9999\n \
    9999XXXXXXXXXX999    9999XXXXXXXXXXXXXXX9999      99XXXXX9999\n \
    9999XXXXXXXXX9999       9999999999999#####99  999XXXXXXXX999\n \
     9999XXXXXXXXX99999     9##############999999XXXXXXXXXX9999\n \
      9999XXXXXXXXXXXXXX99999999999999999XXXXXXXXXXXXXXX99999\n \
        99999XXXXXXXXXXXXXXXXXXXXXXXXXXXXX999999999999999\n \
          99999999XXXXXXXXXXX99999999999111111999      9999999\n \
          99999999999999999911111111111111111119999999999999999999\n \
       9999#########999999911111111111111111111199#############9999\n \
     9999################9991111111111111111111199###############999\n \
    999####################99911111111111111111199###############999\n \
    99######################9911111111111111111199###############999\n \
    99######################991111111111111111199################999\n \
    9999####################9999111111111111999###############9999\n \
      99999##############999999999999999999999999999999999999999\n \
         99999999999999999                        9999999999\033[0m\n";

    int sockfd = SocketCreate(SOCK_DGRAM, &broadcast_addr, atoi(argv[1]));

    UDPBroadcast(sockfd, &broadcast_addr);

    for (int i = 0; i < 100; ++i)
    {
        UDPSendTo(sockfd, message, strlen(message) + 1, &broadcast_addr);
        sleep(1);
    }
    
    SocketClose(sockfd);

    return (0);
}
