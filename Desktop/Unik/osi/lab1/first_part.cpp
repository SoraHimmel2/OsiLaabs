#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

  pid_t process_id = getpid();
  cout << "Process id -> " << process_id << endl;
  // cout << "Parent id -> " << getppid() << endl;

  for (int i = 0; i < argc; i++) {
    if (i > 4)
      break;
    printf("%s\n", argv[i]);
    sleep(2);
  }

  if (process_id == 0) {
    exit(EXIT_SUCCESS);
  } else

  {
    exit(EXIT_FAILURE);
  }
}
