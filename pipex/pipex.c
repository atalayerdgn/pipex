#include "pipex.h"
void	free_all(t_pipex *data)
{
	free(data->infile);
	free(data->outfile);
	ft_free(data->splitted_cmd);
	free(data->path);
}
static	void set_values(t_pipex *data,char *s1,char *s2)
{
	data->infile = ft_strdup(s1);
	data->outfile = ft_strdup(s2);
}
int	main(int ac, char **av, char **env)
{
	t_pipex data;
	if (ac != 5)
		return(write(1,"Usage infile < cmd1 | cmd2 > outfile", 37));
	set_values(&data,av[1],av[ac - 1]);
	if(pipe(data.fd) == -1)
		perror("pipe");
	execute_infile(&data,env,av[2]);
	waitpid(-1,NULL,0);
	if(data.execstat == -1)
	{
		free_all(&data);
		return 0;
	}
	execute_outfile(&data,env,av[3]);
	waitpid(-1,NULL,0);
	if(data.execstat == -1)
	{
		free_all(&data);
		return 0;
	}
	free(data.infile);
	free(data.outfile);
}
