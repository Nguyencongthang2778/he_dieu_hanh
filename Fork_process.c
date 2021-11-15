#include <stdio.h>

int main(){
    Pid_t pid;
    /* fork another process */
    pid = fork();
    if (pid < 0){/* error occurred */
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid == 0){/* child process */
    execlp("/bin/ls", "ls", NULL);
    }
    else {/*parent process  wait until child complete*/
        printf ("Child complete");
        exit(0);
    }
}