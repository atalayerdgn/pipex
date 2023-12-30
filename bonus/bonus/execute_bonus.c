#include "bonus.h"

void	execute(t_pipex *data, char **env)
{
	int	i;
	pid_t	pid;
	int	j;

	j = 0;
	i = 0;
	while (data->cmds[i])
	{
		printf("%s\n%s\n",data->paths[i],data->cmds[i]);
		pid = fork();
		if (pid == -1)
			perror("pid");
		else if (pid == 0)
		{
			if (i == 0)
			{
				dup2(data->infile, 0);
				close(data->fd[i][0]);
				dup2(data->fd[i][1], 1);
				close(data->fd[i][1]);
			}
			else if (i > 0 && data->cmds[i + 1])
			{
				close(data->fd[i - 1][1]);
				close(data->fd[i][0]);
				dup2(data->fd[i - 1][0], 0);
				dup2(data->fd[i][1], 1);
			}
			else if (i > 0 && !data->cmds[i + 1])
			{
				close(data->fd[i - 1][1]);
				dup2(data->fd[i - 1][0], 0);
				close(data->fd[i - 1][0]);
				dup2(data->outfile,1);
			}
			if(execve(data->paths[i], ft_split(data->cmds[i], ' '), env) == -1)// argümana koyulacak ve fonksiyon bölünecek
				return (free_struct(data), perror("execve"));
		}
		while(j < data->commandcounter)
		{
			waitpid(-1, NULL, 0);
			j++;
		}
		i++;
	}
}
