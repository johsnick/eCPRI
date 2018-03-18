#include "ecpri.h"

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void ecpri_init(const char * url, const char * port, ecpri_socket *sock){
  struct addrinfo hints;
  struct addrinfo *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  int s = getaddrinfo(url, port, &hints, &(sock->addr));

  if(s != 0){
    printf("%s\n", gai_strerror(s));
    exit(s);
  }

  sock->sfd = socket(sock->addr->ai_family, sock->addr->ai_socktype, sock->addr->ai_protocol);
  s = connect(sock->sfd, sock->addr->ai_addr, sock->addr->ai_addrlen);
  if(s != 0){
    printf("Failed to Bind\n");
    exit(errno);
  }
}

ecpri_msg ecpri_msg_gen(ecpri_msg_t type, int pc_id, int seq_id, void * data, int data_len) {
  data_len += data_len % 4;
  char * msg = (char *) malloc(8 + data_len);
  msg[0] = ECPRI_VERSION;
  msg[1] = type;
  int payload_len = data_len + 2;
  msg[2] = (payload_len & 0xff00) >> 16;
  msg[3] = (payload_len & 0xff);
  msg[4] = (pc_id & 0xff00) >> 16;
  msg[5] = (pc_id & 0xff);
  msg[6] = (seq_id & 0xff00) >> 16;
  msg[7] = (seq_id & 0xff);
  memcpy(msg + 8, data, data_len);
  ecpri_msg res;
  res.msg = msg;
  res.len = payload_len + 4;

  return res;
}

int ecpri_send(ecpri_socket *sock, ecpri_msg msg){
  int res = write(sock->sfd, msg.msg, msg.len);

  if(res == 0){
    free(msg.msg);
  }

  return res;
}

int ecpri_muttisend(ecpri_socket *sock, ecpri_msg *msgs, int msg_count){
  int i;
  int size = 0;
  for(i = 0; i < msg_count - 1; i++){
    msgs[i].msg[0] |= 1; 
    size += msgs[i].len;
  }
  size += msgs[msg_count - 1].len;
  char * data = (char *) malloc(size);
  int index = 0;
  for(i =0; i < msg_count; i++){
    memcpy(data + index, msgs[i].msg, msgs[i].len);
    index += msgs[i].len;
  }

  int res =  write(sock->sfd, data, size);

  if(res == 0){
    for(i = 0; i < msg_count; i++){
      free(msgs[i].msg);
    }
  }

  return res;
}