#include "minishell.h"

static bool	read_in_stdin(char *word, t_data *data, int fd)
{
	char	*buf;
	char	*word2;

	word2 = ft_strdup(word);
	if (!word2)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!replace_dollar(&word2, data))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			print_error("warning: here_document deliminated by EOF ");
			print_error("(wanted '");
			print_error(word);
			print_error("')\n");
			break ;
		}
		if (!replace_dollar(&buf, data))
		{
			free(word2);
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		}
		if (!ft_strncmp(word2, buf, INT_MAX))
		{
			free(buf);
			break;
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(word2);
	close(fd);
	return (true);
}

int	here_doc(char *word, t_data *data)
{
	int	fd;

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
 