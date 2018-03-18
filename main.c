#include "ecpri.h"

int main (){
  ecpri_socket sock;
  ecpri_init("127.0.0.1", "5000", &sock);
  ecpri_msg msg = ecpri_msg_gen(IQ_DATA, 1, 1, "test", 5);
  ecpri_send(&sock, msg);
}