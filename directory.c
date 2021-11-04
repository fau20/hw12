#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  DIR * d;
  struct dirent *dent;
  char buffer[100];
  if(argc > 1) {
    d = opendir(argv[1]);
    if (errno != 0) {
      printf("Error: %s\n", strerror(errno));
    }
  }
  else {
    printf("Enter directory: \n");
    read(STDIN_FILENO, buffer, sizeof(buffer));
    d = opendir(argv[1]);
    if (errno) {
      printf("Error: %s\n", strerror(errno));
    }
  }
  d = opendir("./");

  unsigned long size = 0;
  printf("Statistics for directory: \n");
  struct stat sb;
  struct dirent * entry;
  entry = readdir(d);
  printf("Directories:\n");
  while(entry!= NULL) {
    if(entry->d_type == 4) {
      printf("%s\n",entry->d_name);
    }
    entry = readdir(d);
  }

  rewinddir(d);
  entry = readdir(d);
  printf("Files:\n");
  while(entry!= NULL) {
    if(entry->d_type == 8) {
      stat(entry->d_name, &sb);
      size += sb.st_size;
      printf("%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  printf("Total Directory Size: %lu Bytes\n", size);
  closedir(d);

  return 0;
}
