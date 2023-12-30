#include "bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex		*data;

	data = (t_pipex *)malloc(sizeof(t_pipex));
	if(!data)
		return (0);
	data->heredoc = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		data->heredoc = 1;
	if (data->heredoc == 1)
		heredoc(data, av, env, ac);
	else
		init_data(data, av, env, ac);
	return (0);
}
