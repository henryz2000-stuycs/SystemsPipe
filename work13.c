#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(){

  //descriptors
  int descriptors_p2c[2];
  int descriptors_c2p[2];

  //pipes
  pipe(descriptors_p2c);
  pipe(descriptors_c2p);

  int f = fork();

  //child
  if (!f){
    int x;

    //read from parent into x
    close(descriptors_p2c[WRITE]);
    read(descriptors_p2c[READ], &x, sizeof(x));

    //math operation
    printf("[child] doing maths on: %d\n", x);
    x *= x;

    //write x to parent
    close(descriptors_c2p[READ]);
    printf("[child] sending: %d\n", x);
    write(descriptors_c2p[WRITE], &x, sizeof(x));
  }

  //parent
  else{
    int x;

    //write f to child
    close(descriptors_p2c[READ]);
    printf("[parent] sending: %d\n", f);
    write(descriptors_p2c[WRITE], &f, sizeof(f));

    //read from child into x
    close(descriptors_c2p[WRITE]);
    read(descriptors_c2p[READ], &x, sizeof(x));
    printf("[parent] received: %d\n", x);
  }
  
  return 0;
}
