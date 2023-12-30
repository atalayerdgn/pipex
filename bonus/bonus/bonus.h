#ifndef BONUS_H
#define BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		**fd;
	int		outfile;
	int		infile;
	int		heredoc; // heredoc eklenecek
	char	*limiter;
	int		commandcounter;
	char	**cmds;
	char	**paths;
}					t_pipex;

void	init_cmds(t_pipex *data, char **av, int ac);
void	init_paths(t_pipex *data, char **env, int ac);
void	init_data(t_pipex *data, char **av, char **env, int ac);
char	*find_path(char **env);
char	*get_path2(char **s1, char **s2);
char	*get_path(char	*cmd,char **env);
void	set_infile_outfile(t_pipex *data, char *infile, char *outfile);
void	execute(t_pipex *data, char **env);
void	ft_free(char **str);
void	free_all(char **s1, char **s2);
void	free_struct(t_pipex *data);
void	execute1(t_pipex *data, char **env, int *fd);
void	execute2(t_pipex *data, char **env, int *fd);
void	absolute_heredoc1(t_pipex *data, char **env);
void	heredoc(t_pipex *data, char **av, char **env, int ac);
void	init_heredoc_data(t_pipex *data, char **av, char **env, int ac);
void	init_paths_heredoc(t_pipex *data, char **env);
void	init_cmds_heredoc(t_pipex *data, char **av, int ac);
void	execute_heredoc(t_pipex *data, char **env);
#endif
