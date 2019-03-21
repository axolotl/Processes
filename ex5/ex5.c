// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MSGSIZE 16

char *msg1 = "hello world #1";
char *msg2 = "hello world #2";
char *msg3 = "hello world #3";

int main(void)
{
    // initialize pipe array
    int fd[2];

    // initalize pipe
    pipe(fd);

    // for process
    int rc = fork();

    // handle fork error
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    // handle child
    else if (rc == 0)
    {
        write(fd[1], msg1, strlen(msg1));
        write(fd[1], msg1, strlen(msg2));
        write(fd[1], msg1, strlen(msg3));
    }
    // handle parent
    else
    {
        wait(NULL);
        char inbuf[1024];
        int bytes_read = read(fd[0], inbuf, (strlen(msg1) * 3));
        printf("%s\n", inbuf);
    }

    return 0;
}
