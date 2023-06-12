#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int bit_is_on(set *s, int num);
void set_bit_on(set *s, int num);


/**
 * Add the values in the list to the set.
 * Each number appears only once in the set.
 * The numbers are positive integers and <= 127.
 * @param s The set
 * @param numbers The list of numbers
 */
void read_set(set *s, int *numbers){
    int i;
    sub_set(s,s,s);
    for (i = 0; *(numbers + i) != -1; i++) {
        if (!bit_is_on(s, *(numbers + i)))
            set_bit_on(s, *(numbers + i));
    }
}

/**
 * Prints the numbers in the set.
 * Maximum number of numbers in a row is 16.
 * @param s The set to be printed
 */
void print_set(set *s){
    int i, count =0;
    for(i=0; i<NUM_OF_BITS; i++){
        if(bit_is_on(s,i)){
            printf("%d ", i);
            count ++;
            if(count%16 == 0)
                printf("\n");
        }
    }
    if(count == 0)
        printf("The set is empty");
}

/**
 * Assign the union of the two sets to the third set.
 * The union is all of the numbers that are in the first set or in the second.
 * @param s1 The first set.
 * @param s2 The second set.
 * @param result The set to be the union set.
 */
void union_set(set *s1, set *s2, set *result){
    int i;

    set *tmp_result = (set *) calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    for(i=0; i<NUM_OF_BYTES; i++)
        tmp_result->bits[i] &= 0;

    for(i=0; i<NUM_OF_BITS; i++){
        if(bit_is_on(s1,i) && !bit_is_on(tmp_result,i)){
            set_bit_on(tmp_result,i);
        }
        if(bit_is_on(s2,i) && !bit_is_on(tmp_result,i)){
            set_bit_on(tmp_result,i);
        }
    }

    for(i=0; i<NUM_OF_BYTES; i++)
        result->bits[i] = tmp_result->bits[i];
    free(tmp_result);
}

/**
 * Assign the intersect of the two sets to the third set.
 * The intersect is all of the numbers that are in both sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @param result The set to be the intersect set.
 */
void intersect_set(set *s1, set *s2, set *result){
    int i;
    set *tmp_result = (set *) calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    for(i=0; i<NUM_OF_BYTES; i++)
        tmp_result->bits[i] &= 0;

    for(i=0; i<NUM_OF_BITS; i++){
        if(bit_is_on(s1,i) && bit_is_on(s2,i) &&!bit_is_on(tmp_result,i)){
            set_bit_on(tmp_result,i);
        }
    }

    for(i=0; i<NUM_OF_BYTES; i++)
        result->bits[i] = tmp_result->bits[i];
    free(tmp_result);
}

/**
 * Assign the subtraction of the second set from the first set to the third set.
 * Subtraction is the numbers that are in the first set but not in the second.
 * @param s1 The first set.
 * @param s2 The second set.
 * @param result The set to be the subtraction set.
 */
void sub_set(set *s1, set *s2, set *result){
    int i;
    set *tmp_result = (set *) calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    for(i=0; i<NUM_OF_BYTES; i++)
        tmp_result->bits[i] &= 0;

    for(i=0; i<NUM_OF_BITS; i++) {
        if (bit_is_on(s1, i) && !bit_is_on(s2, i) && !bit_is_on(tmp_result, i)) {
            set_bit_on(tmp_result, i);
        }
    }
    for(i=0; i<NUM_OF_BYTES; i++)
        result->bits[i] = tmp_result->bits[i];
    free(tmp_result);
}

/**
 * Assign the symmetric difference of both sets to the third set.
 * Symmetric difference is the numbers that are in only one of the sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @param result The set to be the symmetric difference set.
 */
void symdiff_set(set *s1, set *s2, set *result){
    int i;
    set *tmp_result = (set *) calloc(NUM_OF_BYTES,SIZE_OF_BYTE);
    for(i=0; i<NUM_OF_BYTES; i++)
        tmp_result->bits[i] &= 0;

    for(i=0; i<NUM_OF_BITS; i++){
        if(bit_is_on(s1,i) && !bit_is_on(s2,i) && !bit_is_on(tmp_result,i)){
            set_bit_on(tmp_result,i);
        }

        if(bit_is_on(s2,i) && !bit_is_on(s1,i) && !bit_is_on(tmp_result,i)){
            set_bit_on(tmp_result,i);
        }
    }
    for(i=0; i<NUM_OF_BYTES; i++)
        result->bits[i] = tmp_result->bits[i];
    free(tmp_result);
}

/**
 * Check if the set contains the number.
 * @param s The set to be checked.
 * @param num The number to be searched for.
 * @return 0 if the set doesn't contains the number.
 */
int bit_is_on(set *s, int num){
    return (s->bits[num/SIZE_OF_BYTE] & (1<<num%SIZE_OF_BYTE)) != 0;
}

/**
 * Add number to the set.
 * @param s The set to be added.
 * @param num The number to add.
 */
void set_bit_on(set *s, int num){
    s->bits[num/ SIZE_OF_BYTE] |= 1 << num % SIZE_OF_BYTE;
}

/*
 * read_set SETA, 1,2,-1
read_set SETB,3,4,-1
union_set SETA,SETB,SETA
 */
