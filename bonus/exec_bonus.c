/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:33:57 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/22 14:59:00 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process_pipe(t_env *env, t_cmd *cmd)
{
	int	pid;

	cmd->fd_in = env->files[0];
	while (cmd)
	{
		if (pipe(cmd->fd) == -1)
			perror("Error creating a pipe");
		pid = fork();
		if (pid == -1)
			perror("Error creating a fork");
		if (pid == 0)
			execute_command(cmd, env);
		if (cmd->next)
			cmd->next->fd_in = dup(cmd->fd[0]);
		close(cmd->fd_in);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd = cmd->next;
	}
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else
		dup2(env->files[1], STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	execve(cmd->path, cmd->args, env->envpath);
	if (execve(cmd->path, cmd->args, env->envpath) == -1) 
	{
		perror(cmd->args[0]);
		clean_all(cmd);
		exit(0);
	}
}

void	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free (array);
}

void	clean_all(t_cmd *cmds)
{
	t_cmd	*temp;

	while (cmds)
	{
		free_array((void *)cmds->args);
		free(cmds->path);
		temp = cmds;
		cmds = cmds->next;
		free(temp);
	}
}
