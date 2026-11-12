#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int disable_nagle(){
  if(argc < 2) {
    perror("less arguments called");
    return -1;
  }

  setsockopt(argv);
  return 0;
}
