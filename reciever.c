#include "ecpri.h"

void recieve(ecpri_message * msg) {
  printf("Message#:\t%d\n", msg->payload.iq.seq_id);

  free(msg);
}

int main(){
  ecpri_listen("1234", recieve);
}