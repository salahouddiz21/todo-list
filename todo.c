#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *task;
    int completed;
    char priority;
} Task;

Task *tasks = NULL;
int length = 0;

void addTask(const char *task, char priority) {
    tasks = (Task *)realloc(tasks, (length + 1) * sizeof(Task));
    tasks[length].task = (char *)malloc(strlen(task) + 1);
    tasks[length].completed = 0;
    tasks[length].priority = priority;

    strcpy(tasks[length].task, task);

    length++;
    printf("Tâche ajoutée\n");
}

void listTask() {
    for (int i = 0; i < length; i++) {
        printf("%d. %s - Priorité : %c\n", i + 1, tasks[i].task, tasks[i].priority);
    }
}

void deleteTask(int index) {
    if (index <= length && index > 0) {
        index = index - 1;

        free(tasks[index].task);

        for (int i = index; i < length - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        length--;
        tasks = (Task *)realloc(tasks, (length * sizeof(Task)));
    } else {
        printf("Indice invalide\n");
    }
}

void editeTask(int index, const char *task) {
    if (index <= length && index > 0) {
        index = index - 1;

        char *editedTask = (char *)realloc(tasks[index].task, strlen(task) + 1);

        if (editedTask != NULL) {
            tasks[index].task = editedTask;
            strcpy(tasks[index].task, task);
            printf("Tâche mise à jour avec succès");

        } else {
            printf("Échec d'allocation mémoire");
        }

    } else {
        printf("Indice invalide\n");
    }
}

int main() {
    int choice;
    int indexInput;
    int running = 1;

    char taskInput[100];
    char priorityInput;
    char buffer[100];

    printf("------- TodoList App ------- \n");
    printf("1. Ajouter une tâche\n");
    printf("2. Lister toutes les tâches\n");
    printf("3. Supprimer une tâche\n");
    printf("4. Modifier une tâche\n");
    printf("5. Quitter\n");

    while (running) {
        printf("Entrez votre choix (1, 2, 3, 4, 5) : ");
        if (scanf("%d", &choice) != 1) {
        
            while (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n');
            printf("Choix invalide\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Entrez la tâche : ");
                getchar();
                fgets(taskInput, sizeof(taskInput), stdin);
                taskInput[strcspn(taskInput, "\n")] = '\0';

                printf("Entrez la priorité (L pour Low, M pour Medium, H pour Heigh) : ");
                scanf(" %c", &priorityInput);

                addTask(taskInput, priorityInput);
                break;

            case 2:
                listTask();
                break;

            case 3:
                printf("Entrez l'indice de la tâche à supprimer : ");
                scanf("%d", &indexInput);
                deleteTask(indexInput);
                break;

            case 4:
                printf("Entrez l'indice de la tâche à modifier : ");
                scanf("%d", &indexInput);
                printf("Entrez la nouvelle tâche : ");
                getchar();
                fgets(taskInput, sizeof(taskInput), stdin);
                taskInput[strcspn(taskInput, "\n")] = '\0';
                editeTask(indexInput, taskInput);
                break;

            case 5:
                running = 0;
                break;

            default:
                printf("Choix invalide\n");
                break;
        }
    }
    free(tasks);

    return 0;
}
