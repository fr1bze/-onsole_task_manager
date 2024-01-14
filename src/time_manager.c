#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Level
{
    LOW,
    MEDIUM,
    HIGH,
};

enum Status
{
    DEVELOP,
    COMPLETED,
    INCOMPLETED,
    PAUSE,
};

struct Task
{
    char* name;
    time_t deadline;
    char* description;
    enum Level complexity;
    enum Status status;
};

struct TaskManager
{
    struct Task* tasks;
    int tasksCount;
};

void initializeTaskManager(struct TaskManager* manager) {
    manager->tasks = NULL;
    manager->tasksCount = 0;
}

void addTask(struct TaskManager* manager, const struct Task* task) {
    manager->tasks = realloc(manager->tasks, sizeof(struct Task) * (manager->tasksCount + 1));
    manager->tasks[manager->tasksCount] = *task;
    ++manager->tasksCount;
    printf("Task %s added, now it's %d tasks working\n", task->name, manager->tasksCount);
}

void completeTask(struct TaskManager* manager, const struct Task* task) {
    for (int i = 0; i < manager->tasksCount; i++) 
    {
        if (strcmp(task->name, manager->tasks[i].name) == 0 && 
        strcmp(task->description, manager->tasks[i].description) == 0)
        {
            for (int j = i; j < manager->tasksCount - 1; j++) {
                manager->tasks[j] = manager->tasks[j + 1];
            }
            manager->tasksCount--;

            manager->tasks = realloc(manager->tasks, manager->tasksCount * sizeof(struct Task));
            printf("Task %s finished, now there are %d tasks working\n", task->name, manager->tasksCount);
            return;
        }
    }
}

char** getTasksInfo(struct TaskManager* manager)
{
    char** taskInfo = malloc(manager->tasksCount * sizeof(struct Task));

    if (taskInfo == NULL) 
    {
        fprintf(stderr, "Memory alloc error occured");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < manager->tasksCount; ++i) 
    {
        taskInfo[i] = malloc(256);

        if (taskInfo[i] == NULL) 
        {
            fprintf(stderr, "Memory alloc for taskInfo[%s] error occured", i); 
            exit(EXIT_FAILURE);
        }
        else 
        {
            snprintf(taskInfo[i], 256, 
            "Task %d: Name=%s, Deadline=%lld, Description=%s, Complexity=%d, Status=%d",
            i + 1, 
            manager->tasks[i].name, 
            manager->tasks[i].deadline, 
            manager->tasks[i].description, 
            manager->tasks[i].complexity, 
            manager->tasks[i].status
            );
        }
    }

    return taskInfo;
} 

void freeTaskInfo(char** taskInfo, int tasksCount) 
{
    for (int i = 0; i < tasksCount; i++) {
        free(taskInfo[i]);
    }
    free(taskInfo);
}

void freeTaskManager(struct TaskManager* manager)
{
    free(manager->tasks);
    manager->tasksCount = 0;
    printf("Free of memory called\n");
};


int main() {
    struct TaskManager *manager;
    struct tm specificTime1 = {
        .tm_sec = 0,
        .tm_min = 0,
        .tm_hour = 12,    
        .tm_mday = 31,
        .tm_mon = 11,     
        .tm_year = 121,   
        .tm_isdst = -1    
    };
    struct tm specificTime2 = {
        .tm_sec = 0,
        .tm_min = 0,
        .tm_hour = 13,    
        .tm_mday = 31,
        .tm_mon = 11,    
        .tm_year = 123,   
        .tm_isdst = -1    
    };
    initializeTaskManager(manager);
    struct Task task1 = {"Task 1", mktime(&specificTime1), "Description 1", LOW, DEVELOP};
    struct Task task2 = {"Task 2", mktime(&specificTime2), "Description 2", MEDIUM, DEVELOP};

    addTask(manager, &task1);
    addTask(manager, &task2);

    char** taskInfo = getTasksInfo(manager);

    for (int i = 0; i < manager->tasksCount; i++)
    {
        printf("%s\n", taskInfo[i]);
    }
    
    freeTaskInfo(taskInfo, manager->tasksCount);

    completeTask(manager, &task1);
    if (manager->tasksCount != 0) 
    {
        freeTaskManager(manager);
    }

    return 0;
}
