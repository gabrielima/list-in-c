#include <stdio.h>
#include <stdlib.h>

void* lst_create()
{
	void *aux  = (void *) malloc (2 * sizeof(void *));
	
	*(void **)aux  = NULL;
	*(void **)(aux + sizeof(void *)) = NULL;
	
	return aux;
}

size_t lst_size(void *lst)
{
	size_t count = 0;
	void *aux = lst;

	LOOP:
		if(*(void **)aux)
		{
			count++;
			aux = *(void **)aux;
			goto LOOP;
		}

	return count;
}

void lst_append(void* lst, int v)
{
	void *head = lst;
	void *tail = lst + sizeof(void *); 
	void *aux  = (void *) malloc (sizeof(void *) + sizeof(int));
	
	*(void **)aux = NULL;
	*(int*)(aux + sizeof(void *)) = v;

	if(*(void **)head == NULL)
		*(void **)head = *(void **)tail = aux;

	else
	{
		*(void **)(*(void **)tail) = aux;
		*(void **)tail = aux;
	}

	return;
}

int lst_insert(void *lst, size_t pos, int v)
{
	if(pos > lst_size(lst) || pos <= 0)
		return 0;

	void *no = lst;
	void *aux  = (void *) malloc (sizeof(void *) + sizeof(int));
	int count = 1;

	LOOP:
		if(count < pos)
		{
			count++;
			no = *(void **)no;
			goto LOOP;
		}


	*(void **)aux = *(void **)no;
	*(int*)(aux + sizeof(void *)) = v;
	*(void **)no = aux;

	return 1;
}

int lst_get(void *lst, size_t pos, int *v)
{
	if(pos > lst_size(lst) || pos <= 0)	
		return 0;

	void *aux = lst;
	int count = 1;

	LOOP:
		if(count <= pos)
		{
			count++;
			aux = *(void **)aux;
			goto LOOP;
		}

	*v = *(int*)(aux + sizeof(void *));

	return 1;
}

int lst_remove(void *lst, size_t pos)
{
	int size = lst_size(lst), count = 1;

	if(pos > size || pos <= 0)
		return 0;

	void *remov;
	void *aux = lst;
	void *tail = lst + sizeof(void *);

	LOOP:
		if(count < pos)
		{
			count++;
			aux = *(void **)aux;
			goto LOOP;
		}

	if(pos == size)
		*(void **)tail = aux;
	
	remov = *(void **)aux;
	*(void **)aux = *(void **)remov;

	free(remov);

	return 1;
}

void lst_destroy(void *lst)
{
	int count = lst_size(lst);

	LOOP:
		if(count)
		{
			lst_remove(lst, count--);
			goto LOOP;
		}

	free(lst);

	return;
}

int main ()
{
	void* lst;
	int v;

	lst = lst_create();
	lst_insert(lst, 1, 11);
	lst_append(lst, 11);
	lst_append(lst, 5);
	lst_insert(lst, 2, 8);
	lst_insert(lst, 1, 7);
	lst_insert(lst, 10, 2);

	if (lst_get(lst, 3, &v) == 1) 
		printf("v: %d\n", v); 
	if (lst_get(lst, 6, &v) == 1) 
		printf("v: %d\n", v); 
	
	lst_destroy(lst);

	return 0;
}
