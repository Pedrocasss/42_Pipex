/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:09:32 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/20 20:27:18 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				fd[2];
	int				fd_in;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	t_cmd	**cmds;
	char	*outfile;
	char	*infile;
	char	**envpath;
	int		files[2];
}				t_env;

// some libft functions
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//free stuff
void	free_array(void **array);
void	clean_all(t_cmd *cmds);

//env
void	setup_environment(int argc, char **argv, t_env *env);
int		path_line(char **paths);
char	*find_path(char **path_environment, char *cmd);
t_cmd	**parse_cmd_list(t_cmd **head, char **argv, t_env *env);
void	handle_args(int argc, char **argv, t_env *env, t_cmd **commands);

//to exec
void	process_pipe(t_env *env, t_cmd *cmd);
void	execute_command(t_cmd *cmd, t_env *env);

#endif