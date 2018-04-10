#ifndef _ECPRI_DEF
#define _ECPRI_DEF

#include <sys/socket.h>
#include <netdb.h>

#define ECPRI_VERSION 0b0101 // v1.1

#define ECPRI_MAX_PAYLOAD_LEN 508

typedef enum
{
  IQ_DATA = 0,
  BIT_SEQUENCE = 1,
  REAL_TIME_CONTROL = 2,
  GENERIC_DATA = 3,
  REMOTE_MEMORY_ACCESS = 4,
  ONE_WAY_DELAY_MEASURE = 5,
  REMOTE_RESET = 6,
  EVENT_INDICATION = 7
} ecpri_msg_t;

typedef struct {
  uint16_t pc_id;
  uint16_t seq_id;
  char data[ECPRI_MAX_PAYLOAD_LEN - 4];
} ecpri_iq_t;

typedef struct {
  uint8_t protocol;
  uint8_t msg_type;
  uint16_t size;
} ecpri_header;

typedef struct {
  int sfd;
  struct addrinfo *addr;
} ecpri_socket;

typedef struct {
  ecpri_header header;
  union {
    ecpri_iq_t iq;
    char raw[ECPRI_MAX_PAYLOAD_LEN];
  } payload;
} __attribute__((packed)) ecpri_message;

void ecpri_init(const char * url, const char * port, ecpri_socket * sock);
void ecpri_close(ecpri_socket *sock);
ecpri_message * ecpri_msg_gen(ecpri_msg_t type, int pc_id, int seq_id, void * data, int data_len);
int ecpri_send(ecpri_socket *sock, ecpri_message * msg);
// int ecpri_muttisend(ecpri_socket *sock, ecpri_msg *msgs, int msg_count);
void ecpri_listen(const char * url, const char * port, void (*func)(ecpri_message *));
void ecpri_message_ntoh(ecpri_message *msg);

#endif
