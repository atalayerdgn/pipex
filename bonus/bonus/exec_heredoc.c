#include "bonus.h"
void	execute1(t_pipex *data, char **env, int *fd)
{
	pid_t	pid;
	char	**cmd;

	cmd = ft_split(data->cmds[0], ' ');
	if(!cmd)
		return (free_all(cmd, NULL));
	pid = fork();
	if (pid == -1)
		perror("pid");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if (execve(data->paths[0], cmd, env) == -1)
			perror("execve");
	}
	waitpid(-1, NULL, 0);
}
void	execute2(t_pipex *data, char **env, int *fd)
{
	pid_t	pid;
	char	**cmd;

	cmd = ft_split(data->cmds[1], ' ');
	if(!cmd)
		return (free_all(cmd, NULL));
	pid = fork();
	if (pid == -1)
		perror("pid");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(data->outfile, 1);
		if (execve(data->paths[1], cmd, env) == -1)
			perror("execve");
	}
	exit(EXIT_SUCCESS);
}

void	absolute_heredoc(t_pipex *data, char **env)
{
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe");
	execute1(data, env, fd);
	execute2(data, env, fd);
}

void	execute_heredoc(t_pipex *data, char **env)
{
	char	*line;
	int		i;
	int		dupl;

	i = 1;
	dupl = dup(STDIN_FILENO);
	while(i)
	{
		line = get_next_line(dupl);
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0 && \
		ft_strncmp(data->limiter, line, ft_strlen(line - 1)) == 0)
			break;
		free(line);
		i++;
	}
	absolute_heredoc(data, env);
}
