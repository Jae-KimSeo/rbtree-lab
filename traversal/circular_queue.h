#ifndef CIRCULAR_QUEUE_H
# define CIRCULAR_QUEUE_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../src/rbtree.h"
typedef enum	e_bool
{
	FALSE,
	TRUE
}	t_bool;


//typedef node_t t_data;
typedef struct ArrayQueueNodeType
{
	t_data	element; //문자 자료
}	ArrayQueueNode;

typedef struct ArrayQueueType
{
  int				maxElementCount; //최대 노드 개수
  int				currentElementCount; //현재 노드 개수
  ArrayQueueNode	*pElement; //노드 저장을위한 배열 포인터
  int				front; //제일 처음부분(삭제 연산(dequeue) 발생)
  int				rear; //제일 뒷부분(삽입 연산(enqueue) 발생)
} ArrayQueue;

ArrayQueue	*createArrayQueue(int maxElementCount);

t_bool		enqueue(ArrayQueue *queue, t_data data);
t_data		peek(ArrayQueue *queue);
t_data		dequeue(ArrayQueue *queue);
t_bool		is_empty(ArrayQueue *queue);
t_bool		is_full(ArrayQueue *queue);

void		display_queue(ArrayQueue *queue);
void		delete_queue(ArrayQueue *queue);

#endif
