#ifndef _SYS_H
#define _SYS_H

#include<linux/sched.h>

extern int sys_fork(); // 创建进程(kernel/system_call.s)
extern int sys_execve(); // 执行程序(kernel/system_call.s)
extern int sys_pause(); // 暂停进程运行(kernel/sched.c)
extern int stub_syscall();
extern int serial_debugstr(char *str);
extern int sys_kill(int pid, int sig); // 终止进程(kernel/exit.c)
extern int sys_sigaction(int signum, struct sigaction *action, struct sigaction *old_action);
extern int sys_sgetmask(void);
extern int sys_ssetmask(int newmask);
// Just for debug use
extern int tty_read(int channel, char *buf, int nr);
extern int _user_tty_write(int channel, char *buf, int nr);
extern int sys_alarm(long seconds); // 设置报警 (kernel/sched.c)
extern int sys_sleep(long seconds);

// 目前除了少数syscall之外其余的syscall均为stub状态
fn_ptr sys_call_table[] = {
    tty_read, // 0
    stub_syscall,
    sys_fork,
    _user_tty_write, // 3
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    sys_sleep, // 10
    sys_execve,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall, // 20
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    sys_pause,
    stub_syscall, // 30
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    sys_kill,
    stub_syscall,
    stub_syscall,
    stub_syscall, // 40
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall, // 50
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall, // 60
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    stub_syscall,
    sys_sigaction,
    sys_sgetmask,
    sys_ssetmask,
    stub_syscall,
    stub_syscall,
    serial_debugstr,
};

#endif
