/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:51:11 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/22 15:07:15 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_process(char **argv, t_env *env)
{
	char	*str;
	char	*limit;

	env->here_doc = 1;
	write(1, "> ", 2);
	env->files[0] = open(env->infile, O_RDWR | O_CREAT, 0644);
	str = get_next_line(0);
	limit = ft_strjoin(argv[2], "\n");
	while (str)
	{
		write(1, "> ", 2);
		if ((!ft_strncmp(str, limit, ft_strlen(limit))))
			break ;
		ft_putstr_fd(str, env->files[0]);
		free(str);
		str = get_next_line(0);
	}
	if (str)
		free(str);
	free(limit);
	close(env->files[0]);
	env->files[0] = open(env->infile, O_RDONLY);
	env->files[1] = open(env->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
}
