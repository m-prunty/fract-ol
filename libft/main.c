#include "libft.h"
#include <stdio.h>

int main()
{
	t_list *lst;

	ft_printf("\n%i\n", 20);
	printf("\n%i :",ft_isalpha('a'));
	lst = ft_lstnew("a");
	ft_printf("%s", lst->content);
	return 0;
}
