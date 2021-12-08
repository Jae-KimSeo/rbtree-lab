#include "./circular_queue.h"

ArrayQueue *createArrayQueue(int maxElementCount)
{
	ArrayQueue *queue;

	queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	if (queue == 0)
		return (NULL);
	queue->maxElementCount = maxElementCount;
	queue->currentElementCount = 0;
	queue->pElement = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode) * maxElementCount);
	if (queue->pElement == 0)
	{
		free(queue);
		return (NULL);
	}
	queue->front = 0;
	queue->rear = 0;
	return (queue);
}

t_bool enqueue(ArrayQueue *queue, t_data data)
{
	if (is_full(queue) == TRUE)
		return (FALSE);
	if (is_empty(queue) == FALSE)
		queue->rear = (queue->rear + 1) % queue->maxElementCount;
	//memcpy(&queue->pElement[queue->rear].element, &data, sizeof(t_data));
	queue->pElement[queue->rear].element = data;
	queue->currentElementCount++;
	return (TRUE);
}

t_data peek(ArrayQueue *queue)
{
	t_data	ret;
	
	bzero(&ret, sizeof(t_data));
	if (is_empty(queue))
		return (ret);
	ret = queue->pElement[queue->front].element;
	return (ret);
}

t_data dequeue(ArrayQueue *queue)
{
	t_data	ret;

	ret = peek(queue);
	if (is_empty(queue))
		return (ret);
	bzero(&(queue->pElement[queue->front].element), sizeof(t_data));
	queue->front = (queue->front + 1) % queue->maxElementCount;
	if (queue->currentElementCount == 1)
		queue->rear = (queue->rear + 1) % queue->maxElementCount;
	queue->currentElementCount--;
	return (ret);
}

t_bool is_empty(ArrayQueue *queue)
{
	if (queue->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

t_bool is_full(ArrayQueue *queue)
{
	if (queue->maxElementCount == queue->currentElementCount)
		return (TRUE);
	return (FALSE);
}

//void	display_queue(ArrayQueue *queue)
//{
//	printf("----------Queue----------\n"); 
//	for (int i = 0; i < queue->currentElementCount; i++)
//		printf("queue[%d] = %c\n", (queue->front + i) % queue->maxElementCount, queue->pElement[(queue->front + i) % queue->maxElementCount].element);
//	printf("Front: %d %c\n", queue->front, queue->pElement[queue->front].element);
//	printf("rear: %d %c\n", queue->rear, queue->pElement[queue->rear].element);
//}

void	clear_queue(ArrayQueue *queue)
{
	for (int i = 0; i < queue->currentElementCount; i++)
		dequeue(queue);
}

void	delete_queue(ArrayQueue *queue)
{
	clear_queue(queue);
	free(queue->pElement);
	free(queue);
}
