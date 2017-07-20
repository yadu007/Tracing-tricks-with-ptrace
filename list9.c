data = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
printf("data = %d\n", data);
data = 245;
ptrace(PTRACE_POKEDATA, pid, addr, data);
ptrace(PTRACE_CONT, pid, 0, 0); 
wait(&status);
