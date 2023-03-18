#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simple Task Manger app. Tasks only support being ONE WORD LONG. So, inserting "Review Quiz 1" will return an error. Try inserting "review-quiz-1" instead. */
/* Exiting the app (exit) deletes everything. */

#define MAX_TASKS 10
#define MAX_TASK_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_TASK_NAME_LENGTH];
} task;

task task_list[MAX_TASKS];
int num_tasks = 0;

void add_task(char *name) {
    if (num_tasks >= MAX_TASKS) {
        printf("Error: Maximum number of tasks reached.\n");
        return;
    }
    
    task new_task;
    new_task.id = num_tasks + 1;
    strcpy(new_task.name, name);
    task_list[num_tasks++] = new_task;
    
    printf("Task '%s' added with ID %d.\n", name, new_task.id);
}

void remove_task(int id) {
    for (int i = 0; i < num_tasks; i++) {
        if (task_list[i].id == id) {
            printf("Task '%s' with ID %d removed.\n", task_list[i].name, task_list[i].id);
            num_tasks--;
            for (int j = i; j < num_tasks; j++) {
                task_list[j] = task_list[j+1];
            }
            return;
        }
    }
    
    printf("Error: Task with ID %d not found.\n", id);
}

void list_tasks() {
    if (num_tasks == 0) {
        printf("No tasks found.\n");
        return;
    }
    
    printf("Task List:\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("  %d. %s\n", task_list[i].id, task_list[i].name);
    }
}

int main() {
    char command[10];
    int id;
    char name[MAX_TASK_NAME_LENGTH];
    
    while (1) {
        printf("Enter a command (add/remove/list/exit): ");
        scanf("%s", command);
        
        if (strcmp(command, "add") == 0) {
            printf("Enter a task name: ");
            scanf("%s", name);
            add_task(name);
        }
        else if (strcmp(command, "remove") == 0) {
            printf("Enter a task ID: ");
            scanf("%d", &id);
            remove_task(id);
        }
        else if (strcmp(command, "list") == 0) {
            list_tasks();
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("Error: Invalid command.\n");
        }
    }
    
    return 0;
}
