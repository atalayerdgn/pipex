#include "pipex.h"

void	ft_free(char **str)
{
	int	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
char	 *find_path(char **env)
{
	int	i = 0;
	while(ft_strncmp(env[i],"PATH=",5) != 0)
		i++;
	return(ft_substr(env[i],5,ft_strlen(env[i])));
}
void	get_path(char **cmd,char **env,t_pipex *data)
{
	data->path = find_path(env);
	data->splitted_path = ft_split(data->path,':');
	if(!data->splitted_path)
	{
		free_all(data);
		return;
	}
	char *sub;
	int	i;
	
	i = 0;
	while(data->splitted_path[i])
	{
		free(data->path);
		sub = ft_strjoin(data->splitted_path[i],"/");
		data->path = ft_strjoin(sub,*cmd);
		if(!access(data->path,F_OK))
			break;
		i++;
		free(sub);
	}
	free(sub);
	ft_free(data->splitted_path);
}
