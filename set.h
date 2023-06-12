#define NUM_OF_BYTES 16
#define SIZE_OF_BYTE 8
#define NUM_OF_BITS 128
#define MAX_LEN 512

typedef struct set{
    char bits[NUM_OF_BYTES];
} set;

void read_set(set *s, int *numbers);

void print_set(set *s);

void union_set(set *s1, set *s2, set *s3);

void intersect_set(set *s1, set *s2, set *s3);

void sub_set(set *s1, set *s2, set *s3);

void symdiff_set(set *s1, set *s2, set *s3);

