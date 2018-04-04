#include "ecpri.h"

void recieve(ecpri_message * msg) {
  // printf("hit\n");
  // printf("size of msg: %d\n", msg->header.size);
  // printf("DATA: %s\n", msg->payload.iq.data);
  free(msg);
}

int main(){
  ecpri_listen("127.0.0.1", "1234", recieve);
}