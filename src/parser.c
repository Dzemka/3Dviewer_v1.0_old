// Включить Zen Mode: Ctrl + K   Z
// Замена в файлах: Ctrl + Shift + H
// Обрезать пробелы в конце: Ctrl + K   Ctrl + X
// Переименовать переменную: F2
// Показать определение: Alt + F12
// Перейти к определению: F12
// Форматировать выделенную область: Ctrl + K   Ctrl + F
// Форматировать документ: Shift + Alt + F
// Выделить все вхождения текущего слова: Ctrl + F2
// Выделить все вхождения текущего выделения: Ctrl + Shift + L
// Выделить текущую строку: Ctrl + L
// Поместить курсор в конец каждой выделенной строки: Shift + Alt + I
// Перейти на строку: Ctrl + G
// Глобальный перенос по словам: Alt + Z
// Показать список горячих клавиш: Ctrl + K   Ctrl + S
// Открыть настройки пользователя: Ctrl +

// gcc -g -std=c11 -o App main.c
// gcc $( pkg-config --cflags gtk4 ) -o My2App main.c $( pkg-config --libs gtk4 )

// valgrind --tool=memcheck ./App
// valgrind --track-origins=yes ./App
// valgrind --leak-check=full ./App

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

char **ft_split(char const *s, const char c);
t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **alst, t_list *new);
void ft_lstclear(t_list **lst, void (*del)(void *));

typedef struct s_point
{
	double x;
	double y;
	double z;
} t_point;

int parser(int argc, char **argv, t_viewer *viewer)
{
	FILE *file = NULL;
	ssize_t read;
	char *line = NULL;
	size_t len = 0;
	char **tmp;
	t_point *point;
	t_list *points = NULL;
	t_list *planes = NULL;
	unsigned int i = 0;

	file = fopen("Camera.obj", "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return (-1);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		// if (line == NULL)
		// {
		// 	printf("Ошибка выделения памяти гетлайном !\n");
		// 	return (-1);
		// }
		if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ')
		{
			tmp = ft_split(line, ' ');
			free(line);
			line = NULL;

			if (tmp == NULL)
			{
				printf("Ошибка выделения памяти сплитом !\n");
				return (-1);
			}

			i = 0;
			while (tmp[i] != NULL)
			{
				i++;
			}

			// можно улучшить логику и разрезать строку на слова только если после пробега всех пробелов символ равен 'v' или 'f', а следущий символ - пробел (пробельный)
			if (strcmp(tmp[0], "v") == 0)
			{
				if (i < 4)
				{
					printf("Недостаточно координат точки !\n");
					i = 0;
					while (tmp[i])
					{
						free(tmp[i]);
						i++;
					}
					free(tmp);
					return (-1);
				}
				point = (t_point *)(malloc(sizeof(t_point)));
				if (point == NULL)
				{
					printf("Ошибка выделения памяти для точки !\n");
					i = 0;
					while (tmp[i])
					{
						free(tmp[i]);
						i++;
					}
					free(tmp);
					return (-1);
				}
				// printf("Ошибка !\n");
				// point->x = 1.0;
				point->x = atof(tmp[1]);
				// printf("Ошибка !\n");
				point->y = atof(tmp[2]);
				point->z = atof(tmp[3]);
				t_list *tmp_point = ft_lstnew((void *)(point));
				if (tmp_point == NULL)
				{
					printf("Ошибка выделения памяти для элемента списка точек !\n");
					i = 0;
					while (tmp[i])
					{
						free(tmp[i]);
						i++;
					}
					free(tmp);
					return (-1);
				}
				ft_lstadd_back(&points, tmp_point);
			}
			else if (strcmp(tmp[0], "f") == 0)
			{
				if (i < 4)
				{
					printf("Недостаточно точек грани !\n");
					i = 0;
					while (tmp[i])
					{
						free(tmp[i]);
						i++;
					}
					free(tmp);
					return (-1);
				}
				int *plane = (int *)(malloc(sizeof(int) * (i - 1)));
				unsigned j = 1;
				i = 0;
				while (tmp[j] != NULL)
				{
					printf("%s\n", tmp[j]);
					plane[i] = atoi(tmp[j]);
					printf("%d\n", plane[i]);
					i++;
					j++;
				}
				t_list *tmp_plane = ft_lstnew((void *)(plane));
				if (tmp_plane == NULL)
				{
					printf("Ошибка выделения памяти для элемента списка граней !\n");
					i = 0;
					while (tmp[i])
					{
						free(tmp[i]);
						i++;
					}
					free(tmp);
					return (-1);
				}
				ft_lstadd_back(&planes, tmp_plane);
			}

			i = 0;
			while (tmp[i])
			{
				free(tmp[i]);
				i++;
			}
			free(tmp);
			tmp = NULL;
		}
	}
	free(line);
	int g;

	int *s;
	while (planes)
	{
		g = -1;
		s = (int *)(planes->content);
		while (s[++g])
		{
			printf("%d\n", s[g]);
		}
		planes = planes->next;
	}
	fclose(file);
	ft_lstclear(&points, *free);
	ft_lstclear(&planes, *free);
	printf("Hi\n");

	return 0;
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t res;

	if (src == NULL)
		return ((size_t)NULL);
	i = 0;
	res = 0;
	while (src[res])
		res++;
	if (dstsize < 1)
		return (res);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (res);
}

static int split_compare(const char c, char s)
{
	if (c == s)
		return (1);
	else
		return (0);
}

char **ft_clear_splitted(char **split)
{
	unsigned int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static unsigned int ft_get_nb_strs(char const *s, const char c)
{
	unsigned int i;
	unsigned int str_count;

	if (!s[0])
		return (0);
	i = 0;
	str_count = 0;
	while (s[i])
	{
		if (split_compare(c, s[i]))
			if (i > 0 && !split_compare(c, s[i - 1]))
				str_count++;
		i++;
	}
	if (!split_compare(c, s[i - 1]))
		str_count++;
	return (str_count);
}

static void ft_get_next_str(char **next_str, unsigned int *next_str_len,
							const char c)
{
	unsigned int i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && split_compare(c, **next_str))
		(*next_str)++;
	while ((*next_str)[i])
	{
		if (split_compare(c, (*next_str)[i]))
			return;
		(*next_str_len)++;
		i++;
	}
}

char **ft_split(char const *s, const char c)
{
	char **split;
	char *next_str;
	unsigned int next_str_len;
	unsigned int str_nbr;
	unsigned int i;

	str_nbr = ft_get_nb_strs(s, c);
	split = (char **)malloc(sizeof(char *) * (str_nbr + 1));
	if (!split)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < str_nbr)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		split[i] = malloc(sizeof(char) * (next_str_len + 1));
		if (!split[i])
			ft_clear_splitted(split);
		ft_strlcpy(split[i], next_str, next_str_len + 1);
		i++;
	}
	split[i] = NULL;
	return (split);
}

void ft_lstadd_back(t_list **alst, t_list *new)
{
	// t_list *temp;

	// temp = *alst;
	if (!(*alst))
		(*alst) = new;
	else
	{
		while ((*alst)->next)
			(*alst) = (*alst)->next;
		(*alst)->next = new;
	}
}

t_list *ft_lstnew(void *content)
{
	t_list *new;

	new = NULL;
	new = malloc(sizeof(t_list));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		if (del != NULL && lst->content != NULL)
			(del)(lst->content);
		free(lst);
		lst = NULL;
	}
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *current;
	t_list *next;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			ft_lstdelone(current, (del));
			current = next;
		}
		*lst = NULL;
	}
}
