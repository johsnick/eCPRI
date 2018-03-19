#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>

#include <iostream>
#include <cmath>

#define BUFLEN (int)pow(2, 21) // 2^21 = 2mb

int main(void)
{
  struct sockaddr_in si_me, si_other;
  int s, i, blen, slen = sizeof(si_other);
  char buf[BUFLEN];

  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (s == -1)
  {
    // socket fail
    return(1);
  }

  memset((char *) &si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(1234);
  si_me.sin_addr.s_addr = htonl(inet_network("127.0.0.1"));
  if (bind(s, (struct sockaddr*) &si_me, sizeof(si_me))==-1)
  {
    // bind fail
    return(2);
  }


  int received_data;

  while (true)
  {
    received_data = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &si_other, (socklen_t*)&slen);
    if (received_data == -1)
    {
      // recvfrom fail
      return(3);
    }

    printf("Data: %.*s \nReceived from %s:%d\n\n", blen, buf, inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    // delay(100);
  }

  close(s);
  return 0;
}
