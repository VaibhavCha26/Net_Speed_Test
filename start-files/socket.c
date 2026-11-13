#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

/* macros */ 
#define USR 1
#define ROOT 0

void socket_handling();
void data_handling(char* file,int flags,char* buffer);

/* escalation options and their available sockets for calling basically */
typedef enum sockets_options{
  usr_exp
}socket_options;

// here we define the sockets individually.
struct usr_exp{
  char usr_exp_buffer[1024*32]; 
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

// ex --> [name] usr video file location
int main(int argc,char* argv[]){
  switch(argc){
    case 5 : break;
    default : perror("Missed something - refer to docs: "); exit(1);
  }


}

void socket_handling(domain){
  int socket_called = socket(,);

}

void data_handling(char* file,int flags,char* buffer)
{
  if(file == NULL){
    perror("location not defined");
    exit(1);
  }

  int file_fd = open(file,flags);
  if(file_fd == -1){
    perror("opening error");
    exit(1);
  }

  ssize_t size_read = 0;
  ssize_t total_read = 0;

  if( (size_read = read(file_fd,
                        buffer,sizeof(buffer) - 1 )) > 0 ) {
    total_read += size_read;
  }
  else {
    if(total_read > sizeof(buffer - 1)){
      // debug info T-T 
      buffer[sizeof(buffer)] = '\0';
      total_read = 0;
    }
    buffer[total_read] = '\0';
  }
}
