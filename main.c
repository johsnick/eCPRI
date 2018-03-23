#include "ecpri.h"

int main (){
  ecpri_socket sock;
  ecpri_init("127.0.0.1", "1234", &sock);
  ecpri_msg msg = ecpri_msg_gen(GENERIC_DATA, 5, 2, "test", 4);
  ecpri_send(&sock, msg);
  ecpri_close(&sock);
}
