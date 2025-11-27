#include "minishell.h"

static void	handle_eof(char *word)
{
	print_error("warning: here_document deliminated by EOF ");
	print_error("(wanted '");
	print_error(word);
	print_error("')\n");
}

static bool	process_line(char *buf, char *delimiter, t_data *data, int fd)
{
	if (!replace_dollar(&buf, data))
	{
		free(delimiter);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	if (!ft_strncmp(delimiter, buf, INT_MAX))
	{
		free(buf);
		return (false);
	}
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	free(buf);
	return (true);
}

static char	*prepare_delimiter(char *word, t_data *data)
{
	char	*delimiter;

	delimiter = ft_strdup(word);
	if (!delimiter)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!replace_dollar(&delimiter, data))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (delimiter);
}

static bool	read_in_stdin(char *word, t_data *data, int fd)
{
	char	*buf;
	char	*delimiter;

	delimiter = prepare_delimiter(word, data);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			handle_eof(word);
			break ;
		}
		if (!process_line(buf, delimiter, data, fd))
			break ;
	}
	free(delimiter);
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
