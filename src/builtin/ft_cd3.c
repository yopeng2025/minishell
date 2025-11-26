#include "minishell.h"

static t_list	*find_pwd_var(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	if (!ft_strncmp(tmp->str, "PWD=", 4))
		return (tmp);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->str, "PWD=", 4))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ensure_oldpwd_exists(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->str, "OLDPWD=", 7))
		return ;
	tmp = tmp->next;
	while (tmp != *env)
	{
		if (!ft_strncmp(tmp->str, "OLDPWD=", 7))
			return ;
		tmp = tmp->next;
	}
	export("OLDPWD=", env);
}

static void	update_oldpwd_from_pwd(t_data *data, const char *pwd_str)
{
	char	*new_oldpwd;

	if (!pwd_str)
		return ;
	new_oldpwd = ft_strjoin("OLD", pwd_str);
	if (!new_oldpwd)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	export(new_oldpwd, &data->env);
	free(new_oldpwd);
}

void	update_oldpwd(t_data *data)
{
	t_list	*pwd_node;

	pwd_node = find_pwd_var(data->env);
	ensure_oldpwd_exists(&data->env);
	if (pwd_node)
		update_oldpwd_from_pwd(data, pwd_node->str);
}
