/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:50:41 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/22 17:52:15 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	static t_cmd	*cmds;
	static t_cmd	*head;
	static t_env	env;
	int				i;

	i = 1;
	if (!*envp)
		return (0);
	if (argc != 5)
	{
		write(2, "Incorrect number of arguments, try:\
		./pipex infile <cmd1> <cmd2> outfile.\n", 75);
		exit(1);
	}
	env.envpath = envp;
	handle_args(argc, argv, &env, &cmds);
	head = *env.cmds;
	process_pipe(&env, cmds);
	while (++i < argc - 1)
		waitpid(-1, NULL, 0);
	close(env.files[0]);
	close(env.files[1]);
	clean_all(head);
	exit(0);
}
