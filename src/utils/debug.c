#include "minishell.h"

void	print_token_list(t_token *head)
{
	t_token *cur;
	int i;

	if (!head)
	{
		printf("=== Token List is EMPTY ===\n");
		return ;
	}

	printf("=== Token List (circular) ===\n");
	cur = head;
	i = 0;
	do
	{
		printf("Token %d: str='%s', type=%d, prev=%p, next=%p\n",
			i,
			cur->str ? cur->str : "NULL",
			cur->type,
			(void *)cur->prev,
			(void *)cur->next);
		cur = cur->next;
		i++;
	} while (cur != head);  // ✅ 循环回到起点就停止
	printf("============================\n");
}

void	print_cmd_list(t_cmd *head)
{
	t_cmd *cur;

	cur = head;
	if (!head)
	{
		printf("=== Cmd List is EMPTY ===\n");
		return ;
	}
	printf("=== Cmd List (circular) ===\n");
	int i = 0;
	do
	{
		printf("[%d] fd_in=%d fd_out=%d skip:%d\n",
			i, cur->infile, cur->outfile, cur->skip_cmd);
		printf("cmd[%d]:", i);
		if (cur->cmd_param)
		{
			for (int j=0; cur->cmd_param[j]; j++)
				printf(" '%s'", cur->cmd_param[j]);
			printf("\n");
		}
		else
			printf(" NULL\n");
		cur = cur->next;
		i++;
	} while (cur != head);  // ✅ 循环回到起点就停止
	printf("============================\n");
}