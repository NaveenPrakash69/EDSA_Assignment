/*
NAME : M.NAVEEN PRAKASH
BATCH: 05
ROLL NO : ME24B1029
ELEMENTARY DATASTRUCTURE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue structure for flow requests
typedef struct QueueNode {
    char component[20];
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, const char* component) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strcpy(newNode->component, component);
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

char* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    char* component = strdup(temp->component);
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return component;
}

// Stack structure for emergency adjustments
typedef struct StackNode {
    char component[20];
    struct StackNode* next;
} StackNode;

void push(StackNode** top, const char* component) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    strcpy(newNode->component, component);
    newNode->next = *top;
    *top = newNode;
}

char* pop(StackNode** top) {
    if (*top == NULL) return NULL;
    StackNode* temp = *top;
    char* component = strdup(temp->component);
    *top = (*top)->next;
    free(temp);
    return component;
}

void flowEmergencyDemo() {
    printf("\n=== Part A: Flow and Emergency Management ===\n");
    Queue* flowQueue = createQueue();
    StackNode* criticalStack = NULL;

    // Enqueue 6 flow requests
    char* requests[] = {"Turbine", "Gate", "Spillway", "Reservoir", "Pump", "Valve"};
    for (int i = 0; i < 6; i++) {
        enqueue(flowQueue, requests[i]);
        printf("Enqueued: %s\n", requests[i]);
    }

    // Dequeue and push to stack
    printf("\nProcessing queue to stack:\n");
    while (flowQueue->front != NULL) {
        char* request = dequeue(flowQueue);
        printf("Dequeued: %s -> Pushing to stack\n", request);
        push(&criticalStack, request);
        free(request);
    }

    // Pop from stack to show adjustment order
    printf("\nEmergency adjustment order (LIFO):\n");
    while (criticalStack != NULL) {
        char* adjustment = pop(&criticalStack);
        printf("Adjusting: %s\n", adjustment);
        free(adjustment);
    }
    free(flowQueue);

    // Creativity Bonus
    printf("\nLIFO is ideal for emergency adjustments because the most recent issue (last in) is often the most critical and needs immediate attention. For "
          "example, a 'Valve' failure requires last-minute pressure adjustments to prevent system damage.\n");
}

void powerLogDemo() {
    printf("\n=== Part B: Power Output Log ===\n");
    char* powerLog[5] = {NULL};
    int count = 0;

    // Log power output
    for (int i = 1; i <= 7; i++) {
        char powStr[10];
        snprintf(powStr, sizeof(powStr), "Pow%d", i);
        if (count == 5) {
            printf("Log full! Transmitting oldest: %s\n", powerLog[0]);
            free(powerLog[0]);
            // Shift elements
            for (int j = 0; j < 4; j++) {
                powerLog[j] = powerLog[j+1];
            }
            count--;
        }
        powerLog[count] = strdup(powStr);
        count++;
        printf("Logged: %s | Current log: [", powStr);
        for (int j = 0; j < count; j++) {
            printf("%s%s", powerLog[j], j < count-1 ? ", " : "");
        }
        printf("]\n");
    }

    // Cleanup
    for (int i = 0; i < count; i++) {
        free(powerLog[i]);
    }

    // Creativity Bonus
    printf("\nThe oldest power data is transmitted to the central grid control for load balancing during peak demand periods. This historical data helps predict "
          "consumption patterns and optimize power distribution.\n");
}

// Singly Linked List for worn components
typedef struct SLLNode {
    char component[20];
    struct SLLNode* next;
} SLLNode;

// Doubly Linked List for repaired components
typedef struct DLLNode {
    char component[20];
    struct DLLNode* prev;
    struct DLLNode* next;
} DLLNode;

void componentTrackerDemo() {
    printf("\n=== Part C: Worn Component Tracker ===\n");
    SLLNode* wornList = NULL;
    DLLNode* repairedList = NULL;

    // Add to worn list (SLL)
    void addToWornList(const char* component) {
        SLLNode* newNode = (SLLNode*)malloc(sizeof(SLLNode));
        strcpy(newNode->component, component);
        newNode->next = wornList;
        wornList = newNode;
        printf("Added to worn list: %s\n", component);
    }

    // Repair component (move from SLL to DLL)
    void repairComponent(const char* component) {
        SLLNode* curr = wornList;
        SLLNode* prev = NULL;
        
        // Find component in SLL
        while (curr != NULL && strcmp(curr->component, component) != 0) {
            prev = curr;
            curr = curr->next;
        }
        
        if (curr == NULL) {
            printf("Component %s not found in worn list!\n", component);
            return;
        }
        
        // Remove from SLL
        if (prev == NULL) {
            wornList = curr->next;
        } else {
            prev->next = curr->next;
        }
        
        // Add to DLL
        DLLNode* newNode = (DLLNode*)malloc(sizeof(DLLNode));
        strcpy(newNode->component, curr->component);
        newNode->next = repairedList;
        newNode->prev = NULL;
        if (repairedList != NULL) {
            repairedList->prev = newNode;
        }
        repairedList = newNode;
        printf("Repaired and moved to repaired list: %s\n", curr->component);
        free(curr);
    }

    // Traverse SLL forward
    void traverseWornList() {
        printf("Worn components (forward): ");
        SLLNode* current = wornList;
        while (current != NULL) {
            printf("%s -> ", current->component);
            current = current->next;
        }
        printf("NULL\n");
    }

    // Traverse DLL forward
    void traverseRepairedListForward() {
        printf("Repaired components (forward): ");
        DLLNode* current = repairedList;
        while (current != NULL) {
            printf("%s -> ", current->component);
            current = current->next;
        }
        printf("NULL\n");
    }

    // Traverse DLL backward
    void traverseRepairedListBackward() {
        if (repairedList == NULL) return;
        
        // Find tail
        DLLNode* current = repairedList;
        while (current->next != NULL) {
            current = current->next;
        }
        
        printf("Repaired components (backward): ");
        while (current != NULL) {
            printf("%s -> ", current->component);
            current = current->prev;
        }
        printf("NULL\n");
    }

    // Example usage
    addToWornList("Turbine");
    addToWornList("Pump");
    traverseWornList();
    repairComponent("Turbine");
    traverseWornList();
    traverseRepairedListForward();
    traverseRepairedListBackward();

    // Cleanup
    while (wornList != NULL) {
        SLLNode* temp = wornList;
        wornList = wornList->next;
        free(temp);
    }
    
    while (repairedList != NULL) {
        DLLNode* temp = repairedList;
        repairedList = repairedList->next;
        free(temp);
    }

    // Creativity Bonus
    printf("\nThe turbine blades showed wear from sediment abrasion in fast-moving water. They were polished using robotic maintenance arms with diamond-"
          "coated abrasives, restoring their hydrodynamic efficiency.\n");
}

// Circular Linked List for priority components
typedef struct CLLNode {
    char component[20];
    struct CLLNode* next;
} CLLNode;

void priorityTuningDemo() {
    printf("\n=== Part D: Priority Tuning ===\n");
    CLLNode* priorityList = NULL;

    // Add to circular list
    void addToPriorityList(const char* component) {
        CLLNode* newNode = (CLLNode*)malloc(sizeof(CLLNode));
        strcpy(newNode->component, component);
        if (priorityList == NULL) {
            newNode->next = newNode;
            priorityList = newNode;
        } else {
            newNode->next = priorityList->next;
            priorityList->next = newNode;
            priorityList = newNode;
        }
        printf("Added to priority list: %s\n", component);
    }

    // Traverse circular list n times
    void traversePriorityList(int cycles) {
        if (priorityList == NULL) {
            printf("Priority list is empty!\n");
            return;
        }
        
        printf("Traversing priority list (%d cycles):\n", cycles);
        CLLNode* current = priorityList;
        int count = 0;
        int elements = 0;
        
        // First count elements
        do {
            elements++;
            current = current->next;
        } while (current != priorityList);
        
        for (int i = 0; i < cycles * elements; i++) {
            current = current->next;
            printf("%s -> ", current->component);
            if ((i+1) % elements == 0) printf("\n");
        }
    }

    // Example usage
    addToPriorityList("Gate");
    addToPriorityList("Spillway");
    traversePriorityList(2);

    // Cleanup
    if (priorityList != NULL) {
        CLLNode* temp = priorityList->next;
        while (temp != priorityList) {
            CLLNode* next = temp->next;
            free(temp);
            temp = next;
        }
        free(priorityList);
    }

    // Creativity Bonus
    printf("\nThe spillway was upgraded with smart pressure sensors that automatically adjust gate openings based on real-time water flow data, improving "
          "flood control response times by 40%%.\n");
}

// Main function
int main() {
    flowEmergencyDemo();
    powerLogDemo();
    componentTrackerDemo();
    priorityTuningDemo();
    return 0;
}
