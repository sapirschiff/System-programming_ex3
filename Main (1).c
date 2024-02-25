#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main() {
    int option;
    int index;
    char input[300];    // Assuming a maximum word length of 200 characters
    StrList* list;

    while (1) {
        scanf(" %d", &option);

        switch (option) {
            case 1:
                list = StrList_alloc();
                int num_words;
                char *token;
                scanf(" %d", &num_words);

                while (getchar() != '\n');  // waits for user to input enter
                // Read the entire line of input to accommodate multiple words with spaces:
                fgets(input, sizeof(input), stdin);

                // Newline is also included, so we will replace it with null terminater
                int len = strlen(input);
                if (input[len - 1] == '\n') {
                    input[len - 1] = '\0'; 
                }

                // Extract individual words from the input line, validate word length, and insert:
                token = strtok(input, " "); // Get first word (or NULL if none)

                while (token != NULL) {
                    // Insert the word at the end of the list using StrList_insertLast:
                    StrList_insertLast(list, token);
                    // Get the next word:
                    token = strtok(NULL, " ");
                }
                break;

            case 2:
                scanf("%d %s", &index, input);
                StrList_insertAt(list, input, index);
                break;
            case 3:
                StrList_print(list);
                printf("\n");
                break;
            case 4:
                printf("%zu\n", StrList_size(list));
                break;

            case 5:
                scanf("%d", &index);
                StrList_printAt(list, index);
                printf("\n");
                break;

            case 6:
                printf("%d\n", StrList_printLen(list));
                break;

            case 7:
                scanf("%s", input);
                printf("%d\n", StrList_count(list, input));
                break;

            case 8:
                scanf("%s", input);
                StrList_remove(list, input);
                break;

            case 9:
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;

            case 10:
                StrList_reverse(list);
                break;

            case 11:
                StrList_free(list);
                list = StrList_alloc(); // Allocate new memory
                break;

            case 12:
                StrList_sort(list);
                break;

            case 13:
                if (StrList_isSorted(list)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;

            case 0:
                StrList_free(list);
                exit(0);
            default:
                printf("Invalid option!\n");
        }
    }
    return 0;
}
