#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node {
    char *key;
    struct node *next;
} Node;

int hash(char *str, int size) {
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash = ((hash << 5) - hash) + str[i];
    }
    return hash % size;
}

void insert(Node **table, char *str, int size) {
    int index = hash(str, size);
    if (table[index] == NULL) {
        table[index] = (Node *)malloc(sizeof(Node));
        table[index]->key = strdup(str);
        table[index]->next = NULL;
    } else {
        Node *temp = table[index];
        while (temp->next!= NULL) {
            temp = temp->next;
        }
        temp->next = (Node *)malloc(sizeof(Node));
        temp->next->key = strdup(str);
        temp->next->next = NULL;
    }
}

void print_table(Node **table, int size) {
    for (int i = 0; i < size; i++) {
        Node *temp = table[i];
        printf("Index %d: ", i);
        while (temp!= NULL) {
            printf("%s ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int size, num_keys;
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    printf("Enter the number of keys to insert: ");
    scanf("%d", &num_keys);

    Node **table = (Node **)calloc(size, sizeof(Node *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }

    char str[MAX];
    for (int i = 0; i < num_keys; i++) {
        printf("Enter key %d: ", i + 1);
        scanf("%s", str);
        insert(table, str, size);
    }

    print_table(table, size);

    for (int i = 0; i < size; i++) {
        Node *temp = table[i];
        while (temp!= NULL) {
            Node *next = temp->next;
            free(temp->key);
            free(temp);
            temp = next;
        }
    }
    free(table);

    return
