/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:15 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/16 14:59:14 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_token
{

}	t_token;

typedef struct	s_cmd
{


}	t_cmd;

typedef struct	s_data
{
t_token	*token;
t_cmd	*cmd;
//t_env	*env;
}	t_data;

#endif