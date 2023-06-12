#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "set.h"


char *get_arg(char input[], int *i);
set *string_to_set(char str[]);
int *get_numbers(char  input[], int *i);
void error_message(int i);
void skip_spaces(int *i, char *input);
int check_commas(int *i, char *input);

set *SETA, *SETB, *SETC, *SETD, *SETE, *SETF;

int main() {
    char input[MAX_LEN];
    char *command;
    char *arg1, *arg2, *arg3;
    int j, *nums,i,k;
    set *temp;

    SETA = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    SETB = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    SETC = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    SETD = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    SETE = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    SETF = (set*)calloc(NUM_OF_BYTES,SIZE_OF_BYTE);

        printf("\nSelect a command from the followings:\n"
               "1. read_set <set_name>, <values_seperated_by_commas>\n"
               "2. print_set <set_name>\n"
               "3. union_set <first_set_name>, <second_set_name>, <result_set_name>\n"
               "4. intersect_set <first_set_name>, <second_set_name>, <result_set_name>\n"
               "5. sub_set <first_set_name>, <second_set_name>, <result_set_name>\n"
               "6. symdiff <first_set_name>, <second_set_name>, <result_set_name>\n"
               "7. stop\n");

    while(1) {
        printf("\nEnter a command: \n");
        fgets(input, MAX_LEN, stdin);
        k=0;
        printf("The command you've entered: \n");
        while(input[k] != EOF && input[k] != '\n') {
            printf("%c", input[k]);
            k++;
        }
        if(input[k] == '\n')
            k++;
        printf("\n");
        i=0;
        arg1 = (char *)malloc(MAX_LEN*sizeof(char));
        arg2 = (char *)malloc(MAX_LEN*sizeof(char));
        arg3 = (char *)malloc(MAX_LEN*sizeof(char));

        skip_spaces(&i, input);
        command = get_arg(input,&i);
        skip_spaces(&i,input);
		if(input[i] == ','){
			error_message(9);
			skip_spaces(&i, input);
		}

            if (strcmp(command, "read_set") == 0) {
                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;
                skip_spaces(&i, input);
                nums = get_numbers(input, &i);
                skip_spaces(&i, input);
                if(nums == NULL)
                    continue;

                if (k != i){
                    error_message(6);
                    continue;
                }

                for (j = 0; j < MAX_LEN; j++) {
                    if (*(nums + j) == -1)
                        break;
                    if ((*(nums + j) < 0) || *(nums + j) > 127) {
                        error_message(3);
                        continue;
                    }
                }

                temp = string_to_set(arg1);
                if (temp != NULL) {
                    read_set(temp, nums);
                    printf("Command read_set is done!\n");
                }

            } else if (strcmp(command, "print_set") == 0) {
                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i,input);
                if(k != i){
                    error_message(6);
                    continue;
                }

                skip_spaces(&i,input);
                temp = string_to_set(arg1);
                if (temp != NULL) {
                    print_set(temp);
                    printf("\nCommand print_set is done!\n");
                }

            } else if (strcmp(command, "union_set") == 0) {
                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i, input);
                arg2 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i, input);
                arg3 = get_arg(input, &i);
                skip_spaces(&i, input);

                if(k != i) {
                    error_message(6);
                    continue;
                }

                if (!(string_to_set(arg1) == NULL
                      || string_to_set(arg2) == NULL
                      || string_to_set(arg3) == NULL)) {
                    union_set(string_to_set(arg1), string_to_set(arg2), string_to_set(arg3));
                    printf("Command union_set is done!\n");
                }

            } else if (strcmp(command, "intersect_set") == 0) {
                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i, input);
                arg2 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i, input);
                arg3 = get_arg(input, &i);
                skip_spaces(&i, input);
                if (k != i){
                    error_message(6);
                    continue;
                }

                if (!(string_to_set(arg1) == NULL
                      || string_to_set(arg2) == NULL
                      || string_to_set(arg3) == NULL)) {
                    intersect_set(string_to_set(arg1), string_to_set(arg2), string_to_set(arg3));
                    printf("Command intersect_set is done!\n");
                }

            } else if (strcmp(command, "sub_set") == 0) {

                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i,input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i,input);
                arg2 = get_arg(input, &i);
                skip_spaces(&i,input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i, input);
                arg3 = get_arg(input, &i);
                skip_spaces(&i,input);
                if (k != i){
                    error_message(6);
                    continue;
                }
                if (!(string_to_set(arg1) == NULL
                      || string_to_set(arg2) == NULL
                      || string_to_set(arg3) == NULL)) {
                    sub_set(string_to_set(arg1), string_to_set(arg2), string_to_set(arg3));
                    printf("Command sub_set is done!\n");
                }
            } else if (strcmp(command, "symdiff_set") == 0) {

                skip_spaces(&i,input);
                arg1 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i,input);
                arg2 = get_arg(input, &i);
                skip_spaces(&i, input);
                if(check_commas(&i, input))
                    continue;

                skip_spaces(&i,input);
                arg3 = get_arg(input, &i);
                skip_spaces(&i, input);
                if (k != i){
                    error_message(6);
                    continue;
                }

                if (!(string_to_set(arg1) == NULL
                      || string_to_set(arg2) == NULL
                      || string_to_set(arg3) == NULL)) {
                    symdiff_set(string_to_set(arg1), string_to_set(arg2), string_to_set(arg3));
                    printf("Command symdiff is done!\n");
                }
            } else if (strcmp(command, "stop") == 0) {
                printf("Stopping program\n");
                break;
            } else {
                error_message(1);
            }
        }
    free(arg1);
    free(arg2);
    free(arg3);
    return 0;
}

/**
 * Gets the next argument.
 * @param input The input.
 * @param i The current place in the input.
 * @return String of the argument.
 */
char *get_arg(char input[], int *i){
    int j=0;
    char *result = (char *)calloc(sizeof(char),MAX_LEN);
    while(input[*i] != EOF && isspace(input[*i]) == 0 && input[*i] != ',' && *i <MAX_LEN) {
        *(result + j) = input[*i];
        j++;
        (*i)++;
    }
    *(result+j) = '\0';
    return result;
}

/**
 * Gets list of numbers.
 * @param input The input.
 * @param i The current place in the input.
 * @return Pointer to a list of numbers.
 */
int *get_numbers(char input[], int *i){
    char *num = " ";
    int j=0;
    int *result = (int *)calloc(MAX_LEN,sizeof(int));
    while(strcmp(num, "") != 0) {
        skip_spaces(i,input);
        num = get_arg(input,i);

        if(strcmp(num,"A") >= 0){
            error_message(4);
            return NULL;
        }

        if(strchr(num,'.') != NULL){
            error_message(4);
            return NULL;
        }

        skip_spaces(i,input);
        *(result + j) =atoi(num);
        j++;
        if(atoi(num) == -1 )
            break;
        if(check_commas(i, input))
            return NULL;
    }

    (*i)--;
    if(*(result+j-1) != -1) {
        error_message(2);
        return NULL;
    }
    return result;
}

/**
 * Converting string with name of the set to the correlated set.
 * @param str The name of the set.
 * @return Set with this name.
 */
set *string_to_set(char str[]){
    if(strcmp(str, "SETA") == 0)
        return SETA;
    else if(strcmp(str, "SETB") == 0)
        return SETB;
    else if(strcmp(str, "SETC") == 0)
        return SETC;
    else if(strcmp(str, "SETD") == 0)
        return SETD;
    else if(strcmp(str, "SETE") == 0)
        return SETE;
    else if(strcmp(str, "SETF") == 0)
        return SETF;
    else if(strcmp(str, "") == 0) {
        error_message(5);
        return NULL;
    }else {
        error_message(0);
        return NULL;
    }
}

/**
 * Skips all of the spaces.
 * @param i Index in the input.
 * @param input The input.
 */
void skip_spaces(int *i, char *input){
    while(isspace(input[*i]) != 0)
        (*i)++;
}

/**
 * Checks possible errors with commas.
 * @param i Index in the input.
 * @param input The input.
 * @return 0 if no errors were found, and 1 if there was an error.
 */
int check_commas(int *i, char *input){
    if(input[*i] == ',')
        (*i)++;
    else{
        error_message(8);
        return 1;
    }
    skip_spaces(i,input);
    if(input[*i] == ',') {
        error_message(7);
        return 1;
    }

    return 0;
}

/**
 * Prints error message according to the number of the error.
 * @param i The number of the error.
 */
void error_message(int i){
    switch(i){
        case 0:
            printf("Undefined set name\n");
            break;
        case 1:
            printf("Undefined command name\n");
            break;
        case 2:
            printf("List of set members is not terminated correctly.\n");
            break;
        case 3:
            printf("Invalid set member - value out of range\n");
            break;
        case 4:
            printf("Invalid set member - not an integer\n");
            break;
        case 5:
            printf("Missing parameter\n");
            break;
        case 6:
            printf("Extraneous text after end of command\n");
            break;
        case 7:
            printf("Multiple consecutive commas\n");
            break;
        case 8:
            printf("Missing comma\n");
            break;
	case 9:
            printf("Illegal comma\n");
            break;
    }
}

