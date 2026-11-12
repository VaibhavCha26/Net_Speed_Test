#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/* macros */ 
#define USR 1
#define ROOT 0


/* sockets*/
typedef enum usr_sockets{
  usr_exp
}usr_sockets;

typedef enum root_sockets{
  root_exp
}root_sockets;

// here 
struct usr_exp{};
struct root_exp{};

/* Definitions */ 
typedef struct socket_calls{

  union {
    struct usr_exp usr_exp;
    struct root_exp root_exp;
  }data;

}read_struct;

struct socket_calls socket_calling(int argc,char* argv[]){
  enum usr_sockets usr;
  enum root_sockets root;

  switch (*argv[1]) {
    case ROOT : 
      return (struct usr_sockets_called{});
    
    case USR : 
      return (struct root_sockets_called);
    

    default : break;
  };
};

int main(int argc,char* argv[]){
}
