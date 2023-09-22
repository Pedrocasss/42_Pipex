/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:26:51 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/22 18:16:45 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	static t_cmd	*cmds;
	static t_cmd	*head;
	static t_env	env;
	int				i;

	i = 1;
	if (!*envp)
		return (0);
	if (argc < 5)
	{
		write(2, "Please, at least:\
		./pipex <here_doc> <LIMITER> <cmd1> ... <cmdn> outfile.\n", 82);
		exit (1);
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
	if (env.here_doc)
		unlink(argv[1]);
	exit(0);
}
