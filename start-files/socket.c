#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

/* macros */ 
#define USR 1
#define ROOT 0

/* escalation options and their available sockets for calling basically */
typedef enum usr_sockets_options{
  usr_exp
}socket_options;

typedef enum root_sockets_options{
  root_exp
}root_sockets_options;


// here we define the sockets individually.
struct usr_exp{
  char usr_exp_buffer[1024*32]; 
};

struct root_exp{
  char root_exp_buffer[1024*36];
};


/* Definitions */ 
typedef struct socket_metadata{
  //enum sockets_options sockets_available;
  int escalation;
  void* file_location;
  int socket_type;
}socket_metadata;



//struct socket_calls socket_calling(char* argv[], int* data_fd){
//  enum sockets_options sockets_available;
// switch (*argv[1]) { case ROOT : 
//      return (struct socket_calls){
//        .escalation =  0,
//        .fd = *data_fd,
//      };
//    
//    case USR : 
//      return (struct socket_calls){
//        .escalation = 1,
//        .fd = *data_fd,
//
//};
//    
//
//    default : break; // change this later;
//  };
//};

int socket_handling(struct socket_metadata);
int data_handling(char* file,int flags,char* buffer);




// ex --> [name] esc socket_type file_location
int main(int argc,char* argv[]){
  struct socket_metadata curr_sock_meta;

  curr_sock_meta.file_location = argv[3];
  curr_sock_meta.escalation = *argv[1];
  curr_sock_meta.socket_type = *argv[2];

  switch(argc){
    case 5 : break;
    default : perror("Missed something - refer to docs: "); exit(1);
  }
  

  socket_handling(curr_sock_meta);

}



int socket_handling(struct socket_metadata curr_sock_meta){
  switch (curr_sock_meta.escalation) {
    case 0 : {

      switch (curr_sock_meta.socket_type) {

        case 0 : {
          struct usr_exp usr_exp;
        }

        default : exit(1);
      }
      
    }


    case 1 : {

      switch (curr_sock_meta.socket_type) {

        case 0 : {
          struct root_exp root_exp;
        }

        default : exit(1);
      }
    }

    default : exit(1); // later bruh
  }


  return 0;
}



int data_handling(char* file,int flags,char* buffer)
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
