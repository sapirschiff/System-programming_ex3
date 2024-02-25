#include <string.h>
#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    char* data; // String data
    struct Node* next; // Pointer to the next node
} Node;

// StrList structure representing the linked list
typedef struct _StrList{
    Node* head; // Pointer to the first node in the list
    int size; // Number of elements in the list
} StrList;

// Function to allocate a new empty StrList
StrList* StrList_alloc() {
    StrList* newList = (StrList*)malloc(sizeof(StrList));
    if (newList != NULL) {
        newList->head = NULL;
        newList->size = 0;
    }
    return newList;
}

// Function to free the memory and resources allocated to StrList
void StrList_free(StrList* list) {
    if (list == NULL)
        return;

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

// Function to return the number of elements in the StrList
size_t StrList_size(const StrList* list) {
    return list->size;
}

// function to create a new node with a given data
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    //strcpy(newNode->data, data);
    newNode->data = strdup(data); // Copy the string data
    newNode->next = NULL; // Set next pointer to NULL
    return newNode;
}

// Function to insert an element at the end of the StrList
void StrList_insertLast(StrList* list, const char* data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Function to insert an element at a given index in the StrList
void StrList_insertAt(StrList* list, const char* data, int index) {
    if (index < 0 || index > (int)list->size) {
        // Invalid index, do nothing
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    //strcpy(newNode->data, data);
    newNode->data = strdup(data); // Duplicate the string
    newNode->next = NULL;

    if (index == 0) {
        // Insert at the beginning
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        int i = 0;
        while (i < index - 1) {
            current = current->next;
            i++;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

// Function to return the data stored in the first node of the StrList
char* StrList_firstData(const StrList* list) {
    if (list->head == NULL) {
        // List is empty
        return NULL;
    }
    return list->head->data;
}

// Function to print the StrList to the standard output
void StrList_print(const StrList* list) {
    Node* current = list->head;
    while (current != NULL) {
        if(current->next != NULL){
            printf("%s ", current->data);
            current = current->next;
        }
        else{   // This is just for removing the last space
            printf("%s", current->data);
            current = current->next;
        }

    }
}

// Function to print the word at the given index to the standard output
void StrList_printAt(const StrList* list, int index) {
    if (index < 0 || (int)index >= list->size) {
        // Index out of bounds
        printf("Index out of bounds");
        return;
    }

    Node* current = list->head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    printf("%s", current->data);
}

// Function to return the total number of characters in all strings stored in the list
int StrList_printLen(const StrList* list) {
    int totalLen = 0;
    const Node* current = list->head;
    while (current != NULL) {
        totalLen += strlen(current->data);
        current = current->next;
    }
    return totalLen;
}

// Function to count the number of times a string exists in the list
int StrList_count(StrList* list, const char* data) {
    int count = 0;
    const Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0)
            count++;
        current = current->next;
    }
    return count;
}

// Function to remove all occurrences of a string in the list
void StrList_remove(StrList* list, const char* data) {
    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Function to remove the string at a given index
void StrList_removeAt(StrList* list, int index) {
    if (index < 0 || (int)index >= list->size)
        return;

    Node* current = list->head;
    Node* prev = NULL;
    int i = 0;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    if (current != NULL) {
        if (prev == NULL) {
            list->head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current->data);
        free(current);
        list->size--;
    }
}

// Function to check if two StrLists have the same elements
int StrList_isEqual(const StrList* list1, const StrList* list2) {
    if (list1->size != list2->size)
        return 0;

    Node* current1 = list1->head;
    Node* current2 = list2->head;

    while (current1 != NULL && current2 != NULL) {
        if (strcmp(current1->data, current2->data) != 0)
            return 0;
        current1 = current1->next;
        current2 = current2->next;
    }

    return 1;
}

// Function to clone the given StrList
StrList* StrList_clone(const StrList* list) {
    StrList* newList = StrList_alloc();
    if (list == NULL)
        return NULL;

    const Node* current = list->head;
    while (current != NULL) {
        StrList_insertLast(newList, current->data);
        current = current->next;
    }

    return newList;
}

// Function to reverse the given StrList
void StrList_reverse(StrList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Function to sort the given list in lexicographical order
void StrList_sort(StrList* list) {
    // Convert the list to an array of strings
    char** arr = (char**)malloc(list->size * sizeof(char*));
    if (arr == NULL)
        return; // In case of memory allocation failed

    Node* current = list->head;
    int i = 0;
    while (current != NULL) {
        arr[i++] = strdup(current->data);   // Allocate memory and copy string
        current = current->next;
    }

    // Sort the array of strings
    qsort(arr, list->size, sizeof(char*), compareStrings);

    // Update the list with the sorted elements
    current = list->head;
    i = 0;
    while (current != NULL) {
        strcpy(current->data, arr[i++]);
        current = current->next;
    }
    // Free the temporary array
    for (i = 0; i < list->size; ++i) {
        free(arr[i]);
    }
    free(arr);
}

// Function to check if the given list is sorted in lexicographical order
int StrList_isSorted(StrList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        // List is empty or has only one element, it is considered sorted
        return 1;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            // Current node's data is greater than the next node's data, list is not sorted
            return 0;
        }
        current = current->next;
    }

    // If we reach here, all elements are sorted
    return 1;
}
