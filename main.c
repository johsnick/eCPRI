#include "ecpri.h"
#include <signal.h>

ecpri_socket sock;

void close_socket(){
  printf("Closing Socket\n");
  ecpri_close(&sock);
  exit(0);
}
 
int main (){
  ecpri_init("216.171.62.200", "1234", &sock);

  signal(SIGINT, close_socket);

  uint16_t seq_id = 0;
  while(1) {
    ecpri_message * msg = ecpri_msg_gen(GENERIC_DATA, 5, seq_id++, "testing 1234", 20);
    ecpri_send(&sock, msg);
    printf("Sent msg: %d\n", seq_id);
  }
  ecpri_close(&sock);
}