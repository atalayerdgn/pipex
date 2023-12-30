#include "pipex.h"

void	close_fds(t_pipex *data)
{
	unsigned long i = 0;
	while((i < sizeof(data->fd) / sizeof(int)))
	{
		close(data->fd[i]);
		i++;
	}
}
void	execute_infile(t_pipex *data,char **env,char *cmd)
{
	pid_t	pid;
	pid = fork();
	if (pid == -1)
		perror("pid");
	else if(pid == 0)
	{
		close(data->fd[0]);
		data->opened = open(data->infile,O_RDWR | O_CREAT,0666);
		if(data->opened == -1)
			perror("file");
		data->splitted_cmd = ft_split(cmd,' ');
		if (!data->splitted_cmd)
			return(free_all(data));
		get_path(data->splitted_cmd,env,data);
		if(!data->path)
			return(free_all(data));
		dup2(data->opened,0);
		dup2(data->fd[1],1);
		data->execstat = execve(data->path,data->splitted_cmd,env);
	}
}

void	execute_outfile(t_pipex *data,char **env,char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("pid");
	else if(pid == 0)
	{
		close(data->fd[1]);
		data->opened = open(data->outfile,O_RDWR | O_CREAT,0666);
		if(data->opened == -1)
			perror("file");
		data->splitted_cmd = ft_split(cmd,' ');
		if (!data->splitted_cmd)
			return(free_all(data));
		get_path(data->splitted_cmd,env,data);
		if(!data->path)
			return(free_all(data));
		dup2(data->fd[0],0);
		dup2(data->opened,1);
		data->execstat = execve(data->path,data->splitted_cmd,env);
	}
	close_fds(data);
}
