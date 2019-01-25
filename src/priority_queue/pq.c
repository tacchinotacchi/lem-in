#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "priority_queue.h"

int 	ft_lencmp(void *str1, void *str2);

int main()
{
	char	*array[] = {
		"12345", "1234567", "1234", "12345678", "12", "1123456", "1"};
	t_pq	pq;
	char	**pop;

	init_pq(&pq, sizeof(char*));
	add_pq(&pq, &array[0], ft_lencmp);
	add_pq(&pq, &array[1], ft_lencmp);
	add_pq(&pq, &array[2], ft_lencmp);
	add_pq(&pq, &array[3], ft_lencmp);
	add_pq(&pq, &array[4], ft_lencmp);
	add_pq(&pq, &array[5], ft_lencmp);
	add_pq(&pq, &array[6], ft_lencmp);
	while(!check_empty_pq(&pq))
	{
		pop = pop_pq(&pq, ft_lencmp);
		printf("pop:%s\n", *pop);
		free(pop);
	}
	printf("size:%d || used_size:%d\n", pq.size, pq.used_size);
	destroy_pq(&pq);
	return (0);
}

int ft_lencmp(void *str1, void *str2)
{
	size_t a;
	size_t b;

	if (str1 != NULL)
		a = ft_strlen(*(char**)str1);
	else
		a = 0;
	if (str2 != NULL)
		b = ft_strlen(*(char**)str2);
	else
		b = 0;
	return (a - b);
}
