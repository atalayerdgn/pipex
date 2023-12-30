#include "bonus.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	return (ft_substr(env[i], 5, ft_strlen(env[i])));
}

char	*get_path2(char **s1, char **s2)
{
	int		i;
	char	*j1;
	char	*j2;

	i = 0;
	while (s1[i])
	{
		j1 = ft_strjoin(s1[i], "/");
		if (!j1)
			return (free(j1), NULL);
		j2 = ft_strjoin(j1, s2[0]);
		if (!j2)
			return (free(j1), free(j2), NULL);
		if (!access(j2, F_OK))
			break;
		free(j1);
		free(j2);
		i++;
	}
	return (j2);
}

char	*get_path(char	*cmd,char **env)
{
	char	**splitted_path;
	char	**splitted_cmd;
	char	*absolute_path;
	
	splitted_path = ft_split(find_path(env),':');
	if (!splitted_path)
		return (free_all(splitted_path, NULL), NULL);
	splitted_cmd = ft_split(cmd,' ');
	if (!splitted_cmd)
		return (free_all(splitted_cmd, NULL), NULL);
	absolute_path = get_path2(splitted_path,splitted_cmd);
	if (!absolute_path)
		return (free(absolute_path),free_all(splitted_path,splitted_cmd), NULL);
	free_all(splitted_path, splitted_cmd);
	return (absolute_path);
}
