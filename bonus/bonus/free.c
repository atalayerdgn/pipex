#include "bonus.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	free_all(char **s1, char **s2)
{
	if (!s1 && s2)
	{
		ft_free(s2);
		s2 = NULL;
	}
	else if (!s2 && s1)
	{
		ft_free(s1);
		s1 = NULL;
	}
	else
	{
		ft_free(s1);
		ft_free(s2);
		s1 = NULL;
		s2 = NULL;
	}
}

void	free_fds(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
void	free_struct(t_pipex *data)
{
	if (data->heredoc == 1)
	{
		free (data->limiter);
		free_all(data->cmds, data->paths);
		data->outfile = 0;
		data->commandcounter = 0;
	}
	else
	{
		free_all(data->cmds, data->paths);
		free_fds(data->fd);
		data->outfile = 0;
		data->infile = 0;
		data->commandcounter = 0;
	}
}
