#define BUFF_SIZE 0x1000
typedef struct shared {
        char greyed[BUFF_SIZE];
        char resized[BUFF_SIZE];
        char sobeled[BUFF_SIZE];
        char asciied[BUFF_SIZE];
} shared_t;

static shared_t * const shared = (shared_t*)0x80020000;
