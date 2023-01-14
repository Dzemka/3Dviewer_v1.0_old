#include "../viewer3D.h"

void ft_lstadd_back(t_list **alst, t_list *new) {
  t_list *temp;
  temp = *alst;
  if (!*alst)
    *alst = new;
  else {
    while (temp->next) temp = temp->next;
    temp->next = new;
  }
}

t_list *ft_lstnew(void *content) {
  t_list *new;

  new = NULL;
  new = malloc(sizeof(t_list));
  if (new) {
    new->content = content;
    new->next = NULL;
  }
  return (new);
}

void ft_lstdelone(t_list *lst, void (*del)(void *)) {
  if (lst != NULL) {
    if (del != NULL && lst->content != NULL) del(lst->content);
    free(lst);
    lst = NULL;
  }
}

void ft_lstclear(t_list **lst, void (*del)(void *)) {
  t_list *current;
  t_list *next;

  if (lst && *lst) {
    current = *lst;
    while (current) {
      next = current->next;
      ft_lstdelone(current, (del));
      current = next;
    }
    *lst = NULL;
  }
}

size_t ft_lstsize(t_list *lst) {
  size_t count_elem;

  count_elem = 0;
  while (lst != NULL) {
    count_elem++;
    lst = lst->next;
  }
  return (count_elem);
}
