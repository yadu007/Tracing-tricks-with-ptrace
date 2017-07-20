#include <sys/ptrace.h>
#include <signal.h>
#include <linux/user.h>
#include <sys/types.h>
#include <sys/wait.h>
main()
{
    
    int i = 0, status = 0, pid;
    struct user_regs_struct uregs;

    if ((pid=fork())==0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl("/home/yzcop/child3", "child3", 0);
        printf("execl error...\n");
    } else {
        wait(&status);
        ptrace(PTRACE_CONT, pid, 0, 0);
        sleep(1);
        
        kill(pid, SIGINT);
        wait(&status); 
        ptrace(PTRACE_GETREGS, pid, 0, &uregs);
        printf("rbx = %d\n", uregs.rbx);
        uregs.rbx = 245;
        ptrace(PTRACE_SETREGS, pid, 0, &uregs);
        ptrace(PTRACE_CONT, pid, 0, 0); 
        wait(&status);
        printf("parent: out of wait: %d...\n", WIFSTOPPED(status));
        sleep(100);
    }
}