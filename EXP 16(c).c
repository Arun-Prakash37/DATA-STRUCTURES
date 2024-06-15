#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int hash1(char *str, int size) {
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash = ((hash << 5) - hash) + str[i];
    }
    return hash % size;
}

int hash2(char *str, int size) {
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash = ((hash << 3) + str[i]);
    }
    return hash % size;
}

void insert(char **table, char *str, int size) {
    int index1 = hash1(str, size);
    int index2 = hash2(str, size);
    int i = 0;
    while (table[(index1 + i * index2) % size]!= NULL) {
        i++;
    }
    table[(index1 + i * index2) % size] = strdup(str);
}

void print_table(char **table, int size) {
    for (int i = 0; i < size; i++) {
        if (table[i]!= NULL) {
            printf("Index %d: %s\n", i, table[i]);
        } else {
            printf("Index %d: NULL\n", i);
        }
    }
}

int main() {
    int size, num_keys;
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    printf("Enter the number of keys to insert: ");
    scanf("%d", &num_keys);

    char **table = (char **)calloc(size, sizeof(char *));
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
        if (table[i]!= NULL) {
            free(table[i]);
        }
    }
    free(table);

    return 0;
}
