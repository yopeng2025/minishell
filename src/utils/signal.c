#include "minishell.h"

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);		//清空当前输入行，用“”替代
	rl_on_new_line();			//标记进入新行状态
	if (g_signal_pid == 0)
		rl_redisplay();			//在新行重新显示提示符 minishell>
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 20);
	exit(11);
}

static void	handle_sigabrt(int code)
{
	(void)code;
	wirte(2, "abort\n", 7);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint); //按下Ctrl+C（发送SIGINT）调用handle_sigint()
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}