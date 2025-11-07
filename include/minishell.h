#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_MALLOC "malloc error\n"
# define EXT_MALLOC 1

# define INPUT		1 	//"<"
# define HEREDOC	2	//"<<"
# define TRUNCATE	3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

# define INT_MAX	2147483647
# define PATH_MAX	4096

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>

extern pid_t	g_signal_pid;

typedef struct	s_token
{
	char	*str;
	int		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{
	char	**cmd_param;
	int		infile;
	int		outfile;
	bool	skip_cmd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct	s_data
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*env;
	int		pip[2];
	int     exit_code;
	bool	sq;
}				t_data;

//parse
bool	parseline(t_data *data, char *line);
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
bool	create_list_token(t_token **head_token, char *line);
int		add_dollar(char *line, int *index, char **str, t_data *data);
int		replace_dollar(char **line, t_data *data);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_dollar_word(char *line, int size);
char	*get_elem_env(t_list *env, char *key);
int		add_char(char *c, char **str, t_data *data, int *index);

//token
void	print_token_list(t_token *head);
t_token	*create_new_token(char *str, int type);
void	add_new_back(t_token **head_token, t_token *new);
void	cpy_str(char *str, char *line , int len);
bool	is_quote(char c);
int		get_token_lenth(char **line);
bool	add_token_node(t_token **head_token, char *str, int type);
bool	add_token(char **line, t_token **head_token);
bool	is_space(char c);
int		is_special(char *line);
bool	add_special_token(char **line, t_token **head_token, int type);
bool	create_list_token(t_token **head_token, char *line);

//command
void	print_cmd_list(t_cmd *head);
bool	create_new_command(t_cmd **new);
bool	add_command_node(t_cmd **head_cmd);
bool	add_command(t_token *curr_token, t_data *data);
bool	create_list_cmd(t_data *data);

//fill command
int		open_file(t_data *data, char *filename, int type);
bool	get_in(t_token *curr_token, t_cmd *cmd, t_data *data);
bool	get_out(t_token *curr_token, t_cmd *cmd, t_data *data);
bool	get_infile(t_token *curr_token, t_cmd *cmd, t_data *data);
bool	get_outfile(t_token *curr_token, t_cmd *cmd, t_data *data);
bool	fill_command(t_token *curr_token, t_data *data);

//cmd param
char	**get_param(t_data *data, t_token *token);

// free
void	free_all(t_data *data, char *err, int ext);
int		free_list(t_list **env);
void	free_token_list(t_token **head_token);

//utils
bool	print_error(char *str);

//utils_list
size_t	len_list(t_list *list);
int		append(t_list **list, char *str);
int		ft_search(char *str, char c);

//utils_array
char	**list_to_array(t_list *env);
void	swap_array(char **str1, char **str2);
void	sort_array(char **array, t_list *env);

//free
int		free_list(t_list **env);
void	free_all(t_data *data, char *err, int ext);
void	free_token_list(t_token **head_token);
void	free_cmd_list(t_cmd **head_cmd);
void	free_array(char **array);
void	signals(void);

//execution
int		here_doc(char *word, t_data *data);
void	exec(t_data *data);
void	launch_builtin(t_data *data, t_cmd *cmd);
bool	cmd_exist(char **path, t_data *data, char *cmd);

//builtin
int		ft_echo(char **cmd);
int		ft_env(t_list *env);
bool	is_builtin(char *cmd);
bool	export(char	*str, t_list **env);
int		ft_export(char **cmd, t_list **env);
int		ft_cd(t_data *data, char **cmd_param);
int		ft_exit(t_data *data, char **cmd_param);
int		ft_pwd(void);
int		ft_unset(char **str, t_list **env);


//path
char	*find_path(t_data *data, char *cmd, t_list *env);
char	*create_path(t_list *env, int len);
char	*cmd_not_found(char *cmd);
void	strslashjoin(char *path_return, char *cmd, char *path_in_env, int *i);
void	absolute_path(char **path, char *cmd, t_data *data);
bool	is_dir(char **path, char *cmd, t_data *data);

#endif