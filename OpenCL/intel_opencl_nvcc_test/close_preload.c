#include <stdlib.h>
#include <stdio.h>

extern int __close(int __fd);

int close(int fd) {
  if (fd == fileno(stdin)) {
    printf("close() is called on stdin!\n");
    abort();
  }
  return __close(fd);
}
