#include "ecpri.h"

int main (){
  ecpri_socket sock;
  ecpri_init("127.0.0.1", "1234", &sock);
  int seq_id = 0;
  while(1) {
    ecpri_message * msg = ecpri_msg_gen(GENERIC_DATA, 5, seq_id++, "testing 1234", 20);
    ecpri_send(&sock, msg);
  }
  ecpri_close(&sock);  
}