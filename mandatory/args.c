/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:19:19 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/20 22:28:31 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_environment(int argc, char **argv, t_env *env)
{
	env->infile = argv[1];
	env->outfile = argv[argc - 1];
	env->files[0] = open(env->infile, O_RDONLY);
	env->files[1] = open(env->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (env->files[0] < 0)
	{
		perror("Please...this file dont exist!\n");
		exit (1);
	}
	if (env->files[1] < 0)
	{
		perror("Please...this file dont exist!\n");
		exit(1);
	}
}

int	path_line(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (ft_strncmp(paths[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*find_path(char **path_environment, char *cmd)
{
	char	**paths;
	char	*path_environment_line;
	char	*intermediate;
	char	*final_path;
	int		i;

	i = 0;
	path_environment_line = path_environment[path_line(path_environment)] + 5;
	paths = ft_split(path_environment_line, ':');
	while (paths[i])
	{
		intermediate = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(intermediate, cmd);
		if (access(final_path, F_OK) == 0)
		{
			free(intermediate);
			free_array((void *)paths);
			return (final_path);
		}
		free(intermediate);
		free(final_path);
		i++;
	}
	free_array((void *)paths);
	return (ft_strdup(cmd));
}

t_cmd	**parse_cmd_list(t_cmd **head, char **argv, t_env *env)
{
	int			i;
	t_cmd		*temp;
	t_cmd		*end;

	i = 2;
	end = NULL;
	while (argv[i + 1])
	{
		temp = ft_calloc(1, sizeof(t_cmd));
		if (!temp)
			return (NULL);
		temp->args = ft_split(argv[i], ' ');
		if (env->envpath && *env->envpath)
			temp->path = find_path(env->envpath, temp->args[0]);
		temp->next = NULL;
		if (!(*head))
			*head = temp;
		if (end)
			end->next = temp;
		end = temp;
		i++;
	}
	return (head);
}

void	handle_args(int argc, char **argv, t_env *env, t_cmd **commands)
{
	setup_environment(argc, argv, env);
	env->cmds = parse_cmd_list(commands, argv, env);
	if (!env->cmds)
	{
		close(env->files[0]);
		close(env->files[1]);
		clean_all(*commands);
		exit(0);
	}
}
