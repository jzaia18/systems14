#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define DEBUGGING 1 // Set to or as appropriate

char is_done = 1;

int create_sem(char *arg ) {
  int n = atoi(arg);
  if ( n <= 0 )
    return -1;
  int s = semget(420, 1, IPC_CREAT | IPC_EXCL);
  if ( s == -1)
    printf("Semaphore already exists.\n");
  else {
    printf("Semaphore created: %d\n", s);
    semctl(s, 0, SETVAL, n);
  }
  return s;
}

void view_sem() {
  int s = semctl(420, 0, GETVAL); //TODO
  printf("Current");
}

void remove_sem() {

}


int main(int argc, char* argv[]) {

  while (!is_done) {
    if (!strcmp(argv[0], "-c"))
      create_sem(argv[1]);
    else if (!strcmp(argv[0], "-v"))
      view_sem();
    else if (!strcmp(argv[0], "-r"))
      remove_sem();
  }

  return 0;
}
