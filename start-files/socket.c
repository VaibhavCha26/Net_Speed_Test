#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/* macros */ 
#define USR 1
#define ROOT 0


/* escalation options and their available sockets for calling basically */
typedef enum sockets_options{
  usr_exp
}socket_options;

// here we define the sockets individually.
struct usr_exp{
  
};
struct root_exp{};

/* Definitions */ 
typedef struct socket_calls{
  //enum sockets_options sockets_available;
  int escalation;
  int fd;
  union {
    struct usr_exp usr_exp;
    struct root_exp root_exp;
  }data;

}socket_calls;



struct socket_calls socket_calling(int argc,char* argv[]){
  enum sockets_options sockets_available;

  switch (*argv[1]) {
    case ROOT : 
      return (struct socket_calls){
        .escalation = 1
      };
    
    case USR : 
      return (struct socket_calls){};
    

    default : break; // change this later;
  };
};

int main(int argc,char* argv[]){
}
