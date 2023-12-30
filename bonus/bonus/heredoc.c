#include "bonus.h"
void	init_cmds_heredoc(t_pipex *data, char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	data->cmds = (char **)malloc(sizeof(char *) * (ac - 3));
	if (!data->cmds)
		return;
	while (i < ac - 4)
	{
		j = 0;
		data->cmds[i] = (char *)malloc(sizeof(char) * ft_strlen(av[i + 3]) + 1);
		if (!data->cmds[i])
			return;
		data->cmds[i] = ft_strdup(av[i + 3]);
		i++;
		data->commandcounter++;
	}
	data->cmds[i] = 0;
}

void	init_paths_heredoc(t_pipex *data, char **env)
{
	int	i;

	i = 0;
	data->paths = (char **)malloc(sizeof(char *) * data->commandcounter);
	if (!data->paths)
		return;
	while (i < data->commandcounter)
	{
		data->paths[i] = get_path(data->cmds[i], env);
		i++;
	}
	data->paths[i] = 0;
}

void	init_heredoc_data(t_pipex *data, char **av, char **env, int ac)
{
	data->limiter = ft_strdup(av[2]);
	init_cmds_heredoc(data, av, ac);
	init_paths_heredoc(data, env);
	data->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	data->infile = 0;
	data->fd = 0;
}

void	heredoc(t_pipex *data, char **av, char **env, int ac)
{
	init_heredoc_data(data, av, env, ac);
	execute_heredoc(data, env);
}
