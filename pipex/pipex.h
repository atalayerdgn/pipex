#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		opened;
	int		fd[2];
	int		execstat;
	char	*path;
	char	**splitted_path;
	char	**splitted_cmd;
}			t_pipex;

void	get_path(char **cmd,char **env,t_pipex *data);
char	*find_path(char **env);
void	execute_infile(t_pipex *data,char **env,char *cmd);
void	execute_outfile(t_pipex *data,char **env,char *cmd);
void	ft_free(char **str);
void	close_fds(t_pipex *data);
void	free_all(t_pipex *data);
#endif
