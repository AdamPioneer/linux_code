#ifndef __QSH_LIST_H__
#define __QSH_LIST_H__

#include <stdio.h>

/**/
typedef struct list
{
	struct list *prev;
	struct list *next;		
} LIST;

/**/
typedef struct slist
{
	struct slist *next;
} SLIST;

#define struct_num_offset(type, number)  ( (unsigned int ) (&((type *)0)->number) )

static inline void list_init(struct list *list)
{
	list->prev = list;
	list->next = list;
}

static inline int list_empty(struct list *list)
{
	return list->next == list;
}

static inline void list_add(struct list *list, struct list *node)
{
	list->next->prev = node;
	node->next = list->next;
	list->next = node;
	node->prev = list;
}

static inline void list_insert(struct list *list, struct list *node)
{
	list->prev->next = node;
	node->prev = list->prev;
	list->prev = node;
	node->next = list;
}

static inline void list_del(struct list *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}
static inline void list_replace(struct list *old, struct list *new)
{
	new->next = old->next;
	new->prev->next = new;
	new->prev = old->prev;
	new->prev->next = new;
}

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif /* __QSH_LIST_H__*/
