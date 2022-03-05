#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
  
void func(char *input) {
  pid_t pid;
  int status;
  pid_t ret;
  char *const args[3] = {"any_exe", input, NULL};
  char **env;
  extern char **environ;
 
  /* ... Sanitize arguments ... */
 
  pid = fork();
  if (pid == -1) {
    /* Handle error */
  } else if (pid != 0) {
    while ((ret = waitpid(pid, &status, 0)) == -1) {
      if (errno != EINTR) {
        /* Handle error */
        break;
      }
    }
    if ((ret == 0) ||
        !(WIFEXITED(status) && !WEXITSTATUS(status))) {
      /* Report unexpected child status */
    }
  } else {
    /* ... Initialize env as a sanitized copy of environ ... */
    if (execve("/usr/bin/any_cmd", args, env) == -1) {
      /* Handle error */
      _Exit(127);
    }
  }
}

typedef struct node{
    char c;
    struct node *prev, *next;
}Node;



int main(){
    int T = 0, N = 0;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        scanf("%d", &N);
        for(int j = 0; j < N; j++){
            char c = 0;
            scanf("%c", &c);
            switch (c)
            {
            case 'B':
                
                break;
            
            default:
                break;
            }
        }
    }
    return 0;
}
