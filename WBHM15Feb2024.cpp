#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ADDRESS_LEN 256

struct StackNode
{
    char *url;
    struct StackNode *next;
};

struct Stack
{
    struct StackNode *top;
};

struct QueueNode
{
    char *url;
    struct QueueNode *next;
};

struct Queue
{
    struct QueueNode *front;
    struct QueueNode *rear;
};

bool isEmpty(Stack *stack)
{
    return stack->top == NULL;
}

void push(Stack *stack, char *newUrl)
{

    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (stackNode != NULL)
    {
        stackNode->url = NULL;
        stackNode->next = NULL;
        stackNode->url = newUrl;

        if (stack->top != NULL)
        {
            stackNode->next = stack->top;
        }
        stack->top = stackNode;
    }
    return;
}

char *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        return NULL;
    }
    StackNode *itm = stack->top;
    stack->top = stack->top->next;
    char *poppedUrl = itm->url;
    free(itm);
    return poppedUrl;
}
char *peek(Stack *stack)
{
    return stack->top->url;
}
bool isEmpty(Queue *queue)
{
    return queue->front == NULL;
}
void enqueue(Queue *queue, char *newUrl)
{
    struct QueueNode *queueNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    if (queueNode != NULL)
    {
        queueNode->url = NULL;
        queueNode->next = NULL;

        queueNode->url = newUrl;
        if (queue->rear == NULL)
        {
            queue->front = queueNode;
        }
        else
        {
            queue->rear->next = queueNode;
        }
        queue->rear = queueNode;
    }

    return;
}
char *dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        return NULL;
    }
    QueueNode *itm = queue->front;
    queue->front = queue->front->next;
    char *dequeuedUrl = itm->url;
    free(itm);
    return dequeuedUrl;
}
char *peek(Queue *queue)
{
    return queue->front->url;
}

int main(void)
{
    printf("\nWelcome to the Web Browser History Manager!\n\n");

    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack = NULL;

        stack->top = NULL;

    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    if (queue != NULL)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }

    int choice;
    char *urlStr = (char *)"";
    char inp[MAX_ADDRESS_LEN] = {};
    while (1)
    {
        printf("Menu:\n1. Visit New Web Page\n2. Navigate Backward\n3. Navigate Forward\n4. Display Current Page and History\n5. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        char inp[MAX_ADDRESS_LEN];

        if (choice == 1)
        {
            printf("Enter the URL of the web page: ");
            fseek(stdin, 0, SEEK_END);
            fgets(inp, MAX_ADDRESS_LEN, stdin);
            // fflush(stdin);
            inp[strcspn(inp, "\n")] = '\0';
            // inp[strcspn(inp, "\n")] = 0;
            urlStr = (char *)malloc(sizeof(char) * MAX_ADDRESS_LEN);
            if (urlStr != 0)
            {
                memcpy(urlStr, inp, sizeof(inp));
                push(stack, urlStr);
                // printf("top: %s\n", peek(stack));
                enqueue(queue, urlStr);
            }
            printf("Visited: %s\n\n", urlStr);
        }
        else if (choice == 2)
        {
            char *urlPopped = (char *)"";
            if (!isEmpty(stack))
            {
                urlPopped = pop(stack);
                urlStr = (char *)malloc(sizeof(char) * MAX_ADDRESS_LEN);
                if (urlStr != 0)
                {
                    memcpy(urlStr, urlPopped, strlen(urlPopped) + 1);
                    enqueue(queue, urlStr);
                }
            }
            printf("Previous Page: %s\n\n", urlPopped);
        }
        else if (choice == 3)
        {
            char *urlDequeued = (char *)"";
            if (!isEmpty(queue))
            {
                urlDequeued = dequeue(queue);
                urlStr = (char *)malloc(sizeof(char) * MAX_ADDRESS_LEN);
                if (urlStr != 0)
                {
                    memcpy(urlStr, urlDequeued, strlen(urlDequeued) + 1);
                    push(stack, urlDequeued);
                }
            }

            printf("Next Page: %s\n\n", urlDequeued);
        }
        else if (choice == 4)
        {
            printf("Current Page: %s\n\n", urlStr);

            printf("Backward History:\n");
            int i = 1;
            StackNode *stkPtr = NULL;
            if (stack != NULL)
            {
                stkPtr = stack->top;
            }

            while (stkPtr != NULL)
            {
                printf("%d. %s\n", i, stkPtr->url);
                stkPtr = stkPtr->next;

                i++;
            }
            printf("\n");
            free(stkPtr);
            printf("Forward History: \n");
            int j = 1;
            QueueNode *qPtr = NULL;
            if (queue != NULL)
            {
                qPtr = queue->front;
            }
            while (qPtr != NULL)
            {
                printf("%d. %s\n", j, qPtr->url);
                qPtr = qPtr->next;

                j++;
            }
            printf("\n");

            free(qPtr);
        }
        else if (choice == 5)
        {
            printf("Thank you for using the web browser. Goodbye!\n\n");
            break;
        }
    }

    free(stack);
    free(queue);
    return 0;
}