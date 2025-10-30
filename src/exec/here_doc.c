#include "minishell.h"

static bool	read_in_stdin(char *word, t_data *data, int fd)
{
	char	*buf;

	while (1)
	{
		buf = NULL;
		buf = readline("heredoc> ");
		if (!buf)
		{
			print_error("warning: here_document deliminated by EOF ");
			print_error("(wanted '");
			print_error("')\n");
			break ;
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break;
		if (!replace_dollar(&buf, data))
			free(data);                    //后面要修改为free_all
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	here_doc(char *word, t_data *data)
{
	int	fd;

	//创建名为.heredoc.tmp的临时文件，保存输入的内容。0644：文件权限（rw-r--r--） 
	// |按位或 创建+只写+清空内容
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(word, data, fd))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
