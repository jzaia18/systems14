#include <errno.h>
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
#define KEY 420

int create_sem(char *arg ) {
  int n = atoi(arg);
  if ( n <= 0 )
    return -1;
  int s = semget(KEY, 1, IPC_CREAT | IPC_EXCL);
  if ( s == -1 )
    printf("Semaphore already exists.\n");
  else {
    printf("Semaphore created: %d\n", s);
    semctl(s, 0, SETVAL, n);
  }
  return s;
}

void view_sem() {
  int s = semget(KEY, 1, IPC_CREAT);
  printf("current value: %d\n", semctl(s, 0, GETVAL));
  printf("%s\n", strerror(errno));
}

void remove_sem() {

}

int main(int argc, char* argv[]) {

  if (!strcmp(argv[1], "-c"))
    create_sem(argv[2]);
  else if (!strcmp(argv[1], "-v"))
    view_sem();
  else if (!strcmp(argv[1], "-r"))
    remove_sem();

  return 0;
}
