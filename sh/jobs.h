void init()
{
        glb.terminal = STDIN_FILENO;
        glb.interactive = isatty(glb.terminal);
        if (glb.interactive)
        {
                while (tcgetpgrp(glb.terminal) != (glb.pgid = getpgrp()))
                        kill (- glb.pgid, SIGTTIN);
                signal(SIGINT, SIG_IGN);
                signal(SIGQUIT, SIG_IGN);
                signal(SIGTSTP, SIG_IGN);
                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);
                signal(SIGCHLD, SIG_IGN);
                glb.pgid = getpid();
                if (setpgid(glb.pgid, glb.pgid) < 0)
                {
                        perror ( " setpgid()" );
                        exit (1);
                }
                tcsetpgrp(glb.terminal, glb.pgid);
                tcgetattr(glb.terminal, &glb.tmodes);
        }
}

int initjob(pid_t pid, int fg)
{
        if (glb.interactive)
        {
                pid = getpid();
                setpgid(pid, glb.pgid);
                if (fg)
                        tcsetpgrp(glb.terminal, glb.pgid);
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
                signal(SIGCHLD, SIG_DFL);
        }
        else
                return 1;
        return 0;
}

