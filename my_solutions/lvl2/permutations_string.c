#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void sort(char *s)
{
	int i = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] > s[i+1])
		{
			swap(&s[i], &s[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}
void	permutations(char *in, int n, char *out, int depth, char *used)
{
	if(depth == n)
	{
		puts(out);
		return ;
	}
	int i = 0;
	while (i < n)
	{
		if (!used[i])
		{
			used[i] = 1;								//MARK
			out[depth] = in[i];							//STORE
			permutations(in, n, out, depth + 1, used);	//BACKTRACK
			used[i] = 0;								//ERASE
		}
		i++;
	}
}

int main(int ac, char **av) /// malloc checks and all that jazz..
{
	if (ac != 2)
		return (0);
	
	char *str = av[1];
	int n = ft_strlen(str);
	char *out = malloc(sizeof(char) * (n + 1));
	char *used = malloc(sizeof(char) * (n + 1));
	sort(str); //SORT BEFORE RUNNIN IT
	permutations(str, n, out, 0, used);
	free(used);
	free(out);
}