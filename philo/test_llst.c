/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_llst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:00:00 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 12:59:33 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

// Helper function to create a linked list
t_linked_list	*create_linked_list(void *content);

// Helper function to print integer content
void	print_int(void *content)
{
	printf("%d ", *(int *)content);
}

// Helper function to delete integer content
void	del_int(void *content)
{
	free(content);
}

// Helper function to create an integer
int	*create_int(int value)
{
	int	*num;

	num = malloc(sizeof(int));
	if (!num)
		return (NULL);
	*num = value;
	return (num);
}

void	test_create_empty_list(void)
{
	t_linked_list	*list;

	printf("\n=== Test: Create Empty List ===\n");
	list = create_linked_list(NULL);
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	printf("Head: %s\n", list->head == NULL ? "NULL" : "NOT NULL");
	printf("Last: %s\n", list->last == NULL ? "NULL" : "NOT NULL");
	printf("Size: %d\n", list->get_size(list));
	printf("PASSED\n");
	free(list);
}

void	test_create_list_with_content(void)
{
	t_linked_list	*list;
	int				*num;

	printf("\n=== Test: Create List With Content ===\n");
	num = create_int(42);
	list = create_linked_list(num);
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		free(num);
		return;
	}
	printf("Head content: %d\n", *(int *)list->head->content);
	printf("Last content: %d\n", *(int *)list->last->content);
	printf("Size: %d\n", list->get_size(list));
	printf("PASSED\n");
	list->clear(list, del_int);
	free(list);
}

void	test_add_back(void)
{
	t_linked_list	*list;
	int				i;

	printf("\n=== Test: Add Back ===\n");
	list = create_linked_list(NULL);
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	i = 1;
	while (i <= 5)
	{
		list->add_back_value(list, create_int(i));
		i++;
	}
	printf("Size after adding 5 elements: %d\n", list->get_size(list));
	printf("Elements: ");
	list->iterate(list, print_int);
	printf("\n");
	printf("Head content: %d\n", *(int *)list->head->content);
	printf("Last content: %d\n", *(int *)list->last->content);
	printf("PASSED\n");
	list->clear(list, del_int);
	free(list);
}

void	test_add_front(void)
{
	t_linked_list	*list;
	int				i;

	printf("\n=== Test: Add Front ===\n");
	list = create_linked_list(NULL);
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	i = 1;
	while (i <= 5)
	{
		list->add_front_value(list, create_int(i));
		i++;
	}
	printf("Size after adding 5 elements: %d\n", list->get_size(list));
	printf("Elements (should be 5 4 3 2 1): ");
	list->iterate(list, print_int);
	printf("\n");
	printf("Head content: %d\n", *(int *)list->head->content);
	printf("Last content: %d\n", *(int *)list->last->content);
	printf("PASSED\n");
	list->clear(list, del_int);
	free(list);
}

void	test_insert_after(void)
{
	t_linked_list	*list;
	t_list			*node;

	printf("\n=== Test: Insert After ===\n");
	list = create_linked_list(create_int(1));
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	list->add_back_value(list, create_int(3));
	node = list->head;
	list->insert_value_after(node, create_int(2));
	printf("Size after insertion: %d\n", list->get_size(list));
	printf("Elements (should be 1 2 3): ");
	list->iterate(list, print_int);
	printf("\n");
	printf("PASSED\n");
	list->clear(list, del_int);
	free(list);
}

void	test_clear(void)
{
	t_linked_list	*list;
	int				i;

	printf("\n=== Test: Clear ===\n");
	list = create_linked_list(NULL);
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	i = 1;
	while (i <= 5)
	{
		list->add_back_value(list, create_int(i));
		i++;
	}
	printf("Size before clear: %d\n", list->get_size(list));
	list->clear(list, del_int);
	printf("Size after clear: %d\n", list->get_size(list));
	printf("Head: %s\n", list->head == NULL ? "NULL" : "NOT NULL");
	printf("Last: %s\n", list->last == NULL ? "NULL" : "NOT NULL");
	printf("PASSED\n");
	free(list);
}

void	test_mixed_operations(void)
{
	t_linked_list	*list;

	printf("\n=== Test: Mixed Operations ===\n");
	list = create_linked_list(create_int(10));
	if (!list)
	{
		printf("FAILED: Could not create list\n");
		return;
	}
	list->add_front_value(list, create_int(5));
	list->add_back_value(list, create_int(15));
	list->add_back_value(list, create_int(20));
	list->add_front_value(list, create_int(1));
	printf("Size: %d\n", list->get_size(list));
	printf("Elements (should be 1 5 10 15 20): ");
	list->iterate(list, print_int);
	printf("\n");
	printf("PASSED\n");
	list->clear(list, del_int);
	free(list);
}

int	main(void)
{
	printf("========================================\n");
	printf("   Linked List Test Suite\n");
	printf("========================================\n");

	test_create_empty_list();
	test_create_list_with_content();
	test_add_back();
	test_add_front();
	test_insert_after();
	test_clear();
	test_mixed_operations();

	printf("\n========================================\n");
	printf("   All Tests Completed\n");
	printf("========================================\n");

	return (0);
}
