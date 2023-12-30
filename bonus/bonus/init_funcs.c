#include "bonus.h"

void	init_cmds(t_pipex *data, char **av, int ac)
{
	int	i;
	int	j;

	data->commandcounter = 0;
	i = 0;
	j = 2;
	data->cmds = (char **)malloc(sizeof(char *) * (ac - 2));
	if(!data->cmds)
		return (free_struct(data));
	while(j <= ac - 2)
	{
		data->cmds[i] = (char *)malloc(sizeof(char) * (ft_strlen(av[j]) + 1));
		if (!data->cmds[i])
			return (free_struct(data));
		data->cmds[i] = ft_strdup(av[j]);
		i++;
		j++;
		data->commandcounter++;
	}
	data->cmds[i] = 0;
}
void	init_paths(t_pipex *data, char **env, int ac)
{
	int	i;

	i = 0;
	data->paths = (char **)malloc(sizeof(char *)  * (ac - 2));
	if(!data->paths)
		return (free_struct(data)) ;
	while(data->cmds[i])
	{
		data->paths[i] = get_path(data->cmds[i], env);
		if(!data->paths[i])
			return (free_struct(data));
		i++;
	}
	data->paths[i] = 0;
}

void	set_infile_outfile(t_pipex *data, char *infile, char *outfile)
{
	int	i;

	i = 0;
	data->fd = (int **)malloc(sizeof(int *) * (data->commandcounter));
	if(!data->fd)
		return;
	while(i < data->commandcounter)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if(!data->fd[i])
			return (free_struct(data));
		if(pipe(data->fd[i]) == -1)
			perror("pipe");
		i++;
	}
	data->infile = open(infile, O_RDWR | O_CREAT, 0777);
	if (data->infile < 0)
		return	(free_struct(data));
	data->outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->outfile < 0)
		return (free_struct(data));
}

void	init_data(t_pipex *data, char **av, char **env, int ac)
{
	init_cmds(data, av, ac);
	init_paths(data, env, ac);
	set_infile_outfile(data, av[1], av[ac - 1]);
	execute(data, env);
}
