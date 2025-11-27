/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:45:40 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:45:41 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_MALLOC "malloc error\n"
# define ERR_FORK	"fork error\n"
# define ERR_PIPE	"pipe error\n"

# define EXT_MALLOC 1
# define EXT_FORK	1
# define EXT_PIPE	1

# define INPUT		1 	//"<"
# define HEREDOC	2	//"<<"
# define TRUNCATE	3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

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
# include <linux/limits.h>
# include <signal.h>

extern pid_t	g_signal_pid;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd_param;
	int				infile;
	int				outfile;
	bool			skip_cmd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*env;
	int		pip[2];
	int		exit_code;
	bool	sq;
}				t_data;

//parse
bool	parseline(t_data *data, char *line);
bool	token_list(t_data *data, t_token **head_token, char *line);

//parse--quote
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);

//parse--token
t_token	*create_new_token(t_data *data, char *str, int type);
void	add_new_token_back(t_token **head_token, t_token *new);
bool	add_token_node(t_data *data, t_token **head_token, char *str, int type);
bool	add_token(t_data *data, char **line, t_token **head_token);
bool	add_special(t_data *data, char **line, t_token **head_token, int type);
//parse--token--utils
void	cpy_str(char *str, char *line, int len);
int		get_token_lenth(char *line, int *quote);
bool	is_space(char c);
int		is_special(char *line);

//parse--dollar-replace(+1)
int		exist_in_env(char *line, int *i, t_data *data);
int		add_dollar(char *line, int *index, char **str, t_data *data);
int		replace_dollar(char **line, t_data *data);
//parse--dollar-env
int		ft_search(char *str, char c);
char	*get_dollar_word(char *line, int size);
char	*get_elem_env(t_list *env, char *key);
int		add_char(char *c, char **str, int *index);

//check--syntax
bool	check_syntax(t_data *data);
//parse--command
void	print_cmd_list(t_cmd *head);
bool	create_new_command(t_cmd **new);
bool	add_command_node(t_cmd **head_cmd);
bool	get_in_out_file(t_token *tmp, t_data *data);
bool	fill_fd(t_token *curr_token, t_data *data);
bool	add_command(t_token *curr_token, t_data *data);
bool	create_list_cmd(t_data *data);
//parse--command-fill fd
int		open_file(t_data *data, char *filename, int type);
bool	get_in(t_token *curr_token, t_cmd *cmd, t_data *data);
bool	get_out(t_token *curr_token, t_cmd *cmd, t_data *data);

//parse--command-fill cmd param
char	**get_param(t_data *data, t_token *token);

//execution
int		here_doc(char *word, t_data *data);
void	execute_cmd(t_data *data, t_cmd *cmd, int *pip);
int		len_cmd(t_data *data);
void	wait_all(t_data *data);
void	exec(t_data *data);
void	redirect_io(t_data *data, t_cmd *cmd, int *pip);
void	built(t_data *data, t_cmd *cmd, int *pip);
void	child_process(t_data *data, t_cmd *cmd, int *pip);
void	parent_process(t_data *data, t_cmd *cmd, int *pip);
bool	cmd_exist(char **path, t_data *data, char *cmd);
//builtin
void	launch_builtin(t_data *data, t_cmd *cmd);
void	exec_builtin(int save_stdout, t_data *data, t_cmd *cmd);
bool	is_builtin(char *cmd);

int		ft_echo(char **cmd);
int		ft_env(t_list *env, char **cmd_param);
bool	export(char	*str, t_list **env);
int		ft_export(char **cmd, t_list **env);
void	update_env_value(t_list *tmp_env, char *tmp_str, int position);

char	*is_home_exist(t_data *data);
char	*is_oldpwd_exist(t_data *data);
int		cd_home(t_data *data, char **cmd_param);
int		cd_oldpwd(t_data *data, char **cmd_param);
void	update_oldpwd(t_data *data);
void	update_cwd(t_data *data, char *path);
void	dir_not_found(char *param1, char *param2);
int		ft_cd(t_data *data, char **cmd_param);

void	ft_exit(t_data *data, char **cmd_param);
int		ft_pwd(void);
void	unset(char *str, t_list **env);
int		ft_unset(char **str, t_list **env);

//path
char	*find_path(t_data *data, char *cmd, t_list *env);
char	*create_path(t_list *env, int len);
char	*cmd_not_found(char *cmd);
void	strslashjoin(char *path_return, char *cmd, char *path_in_env, int *i);
void	absolute_path(char **path, char *cmd, t_data *data);
bool	is_dir(char **path, char *cmd, t_data *data);
// free
void	free_all(t_data *data, char *err, int ext);
int		free_list(t_list **env);
void	free_token_list(t_token **head_token);

//utils
int		append_exit_code(t_data *data, char **str);
bool	print_error(char *str);
int		count_param(char **cmd_param);
bool	make_env2(t_data *data);
char	*ft_strjoin_char(char *s, char c);

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

//replace
bool	handle_dollar_digit(char *line, int *i, t_data *data);
bool	handle_dollar_quote(char *line, int *i, t_data *data, bool dq);
bool	handle_dollar_var(char *line, int *i, char **str, t_data *data);
void	check_special_char(char **value);

//utils_export
int		export_append(t_list **list, char *str);
bool	valid_identifier(char *cmd);

//quote_utils
char	*add_quote_special_char(char *str);

//debug
void	print_token_list(t_token *head);
void	print_cmd_list(t_cmd *head);

#endif