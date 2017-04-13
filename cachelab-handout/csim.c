#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "cachelab.h"

#define CLIMIT 32

const char* help_msg = "Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\nOptions:\n-h         Print this help message.\n-v         Optional verbose flag.\n-s <num>   Number of set index bits.\n-E <num>   Number of lines per set.\n-b <num>   Number of block offset bits.\n-t <file>  Trace file.\n\nExamples:\nlinux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\nlinux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n";

struct parameters_t {
    int verbose;
    int s;
    int E;
    int b;
    char trace_file[CLIMIT];
};

struct output_t {
    int hits;  /* number of  hits */
    int misses; /* number of misses */
    int evictions; /* number of evictions */
};

struct output_t summery;

void init_summery()
{
    summery . hits = 0;
    summery . misses = 0;
    summery . evictions = 0;
}

struct parameters_t* parameters;

int init_parameters() {
    parameters = malloc(sizeof(struct parameters_t));
    if (! parameters) {
        return -1;
    }
    parameters -> verbose = -1;
    parameters -> s = -1;
    parameters -> E = -1;
    parameters -> b = -1;
    return 0;
}

void destroy_parameters() {
    free(parameters);
}

int check_params()
{
    if (parameters -> s < 0 || 
        parameters -> E < 0 || 
        parameters -> b < 0) {
        return -1;
    }
    return 1;
}

int is_digit(char c) {
    if (c >= '0' && c <= '9') {
        return 0;
    }
    return 1;
}

int ctoi(const char* c)
{
    if (! c) {
        return -1;
    }
    int i = 0;
    int r = 0;
    while (c[i] != '\0') {
        if (0 != is_digit(c[i]))
            return -1;
        r = r * 10 + (c[i++] - '0');
    }
    return r;
}

int set_parameters(int argc, char** argv)
{
    assert(parameters);
    if (0 == strcmp(argv[1], "-h")) {
        printf("%s\n", help_msg);
        return -1;
    }
    
    if (0 == strcmp(argv[1], "-v")) {
        parameters -> verbose = 1;
    }

    int i = parameters -> verbose == 1 ? 2 : 1;

    if (0 == strcmp(argv[i++], "-s")) {
        parameters -> s = ctoi(argv[i++]);
     } else {
        printf("%s\n", help_msg);
        return -1;
     }

     if (0 == strcmp(argv[i++], "-E")) {
         parameters -> E = ctoi(argv[i++]);
     } else {
        printf("%s\n", help_msg);
        return -1;
     }

     if (0 == strcmp(argv[i++], "-b")) {
         parameters -> b = ctoi(argv[i++]);
     } else {
        printf("%s\n", help_msg);
        return -1;
     }

     if (0 == strcmp(argv[i++], "-t")) {
         if (strlen(argv[i]) >= CLIMIT) {
             return -1;
         }
         strcpy(parameters -> trace_file, argv[i]);
     } else {
        printf("%s\n", help_msg);
        return -1;
     }

    return 0;
}

void print_params()
{
    printf ("verbose : %d\n", parameters->verbose);
    printf ("s : %d\n", parameters -> s);
    printf ("E : %d\n", parameters -> E);
    printf ("b : %d\n", parameters -> b);
    printf ("trace_file %s\n", parameters -> trace_file);
}

struct data_t {
    char data;
    char dirty;
};

struct block_t {
    struct data_t* data;
    int length;
};

struct block_t* build_block() {
    assert(parameters);
    struct block_t* b = malloc(sizeof(struct block_t));
    if (! b) { return NULL; }
    b -> length = (1 << parameters -> b);
    b -> data = malloc(sizeof(struct data_t) * b -> length);
    if (!b -> data) {
        free(b);
        return NULL;
    }
    for (int i = 0; i < b -> length; ++i) {
        b -> data[i].dirty = 0;
    }
    return b;
}

void destroy_block(struct block_t* b) {
    free(b->data);
    free(b);
}

struct line_t {
    struct block_t* block;
    uint8_t valid;
    uint64_t tag;
};

struct line_t* build_line() 
{
    assert(parameters);
    struct line_t* line = malloc(sizeof(struct line_t));
    if (! line ) { return NULL; }
    line -> valid  = 0;
    line -> tag = 0;
    line -> block = build_block();
    if (! line -> block) {
        free(line);
        return NULL;
    }
    return line;
}

void destroy_line(struct line_t* line)
{
    destroy_block(line -> block);
    free(line);
}

struct set_t {
    struct line_t** line;
    int length;
};

void destroy_set(struct set_t* s, int l)
{
    for (int i = 0; i < l; ++i) {
        destroy_line(s->line[i]);
    }
    free(s);
}


struct set_t* build_set()
{
    assert(parameters);
    struct set_t* set = malloc(sizeof(struct set_t));
    if (! set) { return NULL; }
    set -> length = parameters -> E;
    set -> line = malloc(sizeof(struct line_t *) * (set -> length));
    if (! set -> line) { 
        free(set);
        return NULL;
    }
    for (int i = 0; i < set -> length; ++i) {
        set -> line [i] = build_line();
        if (! set -> line [i]) { 
            destroy_set(set, i);
            return NULL; 
        }
    }
    return set;
}

struct cache_t {
    struct set_t** set;
    int length;
};

struct cache_t* cache;

void destroy_cache(struct cache_t* c, int l)
{
    for (int i = 0; i < l; ++i) {
        destroy_set(c->set[i], c->set[i] -> length);
    }
    free(c);
}


struct cache_t* build_cache()
{
    assert(parameters);
    struct cache_t* cache = malloc(sizeof(struct cache_t));
    if (! cache) { return NULL; }
    cache -> length = (1 << parameters -> s);
    cache -> set = malloc(sizeof(struct set_t *) * (cache -> length));
    if (! cache -> set) {
        free (cache);
        return NULL;
    }
    for (int i = 0; i < cache -> length; ++i) {
        cache -> set [i] = build_set();
        if (! cache -> set [i]) { 
            destroy_cache(cache, i);
            return NULL; 
        }
    }
    return cache;
}

uint64_t ones(int n)
{
    uint64_t d = 0xffffffffffffffff;
    d <<= n;
    return ~d;
}

int get_set_id(uint64_t addr)
{
    addr >>= parameters -> b;
    assert(parameters -> s < 64);
    return (addr & ones(parameters -> s));
}

int get_byte_id(uint64_t addr)
{
    assert(parameters -> b < 64);
    return (addr & ones(parameters -> b));
}

uint64_t get_tag(uint64_t addr)
{
    addr >>= (parameters -> b + parameters -> s);
    assert(64 >= (parameters -> b + parameters -> s));
    return (addr & ones(64 - (parameters -> b + parameters -> s)));
}

struct line_t* move_end(struct set_t* set, int i)
{
    struct line_t* l = set->line[i];
    for (int j = i; j < set -> length - 1; ++j) {
        set -> line[j] = set -> line[j + 1];
    }
    set->line[set->length - 1] = l;
    return l;
}

struct line_t* evict(struct set_t* set)
{
    assert(set);
    if (set -> line[0]->valid == 1) {
        ++summery . evictions;
        if (parameters -> verbose == 1) {
            printf("eviction ");
        }
    }
    return move_end(set, 0);
}

void process_memory_load(int set_id, int byte_id, int n_bytes, uint64_t tag)
{
    assert(cache -> length > set_id);
    struct set_t* set = cache->set[set_id];
    assert(set);
    for (int i = 0; i < set -> length; ++i) {
        struct line_t* line = set -> line[i];
        assert(line);
        if (line -> valid == 1 && line -> tag == tag) {
            move_end(set, i);
            ++ summery . hits;
            if (parameters -> verbose == 1) {
                printf("hit ");
            }
            return ;
        }
    }
    ++summery . misses;
    if (parameters -> verbose == 1) {
        printf("miss ");
    }
    struct line_t* line = evict(set);
    assert(line);
    line -> valid = 1;
    line -> tag = tag;
}

void process_memory_store(int set_id, int byte_id, int n_bytes, uint64_t tag)
{
    assert(cache -> length > set_id);
    struct set_t* set = cache->set[set_id];
    assert(set);
    for (int i = 0; i < set -> length; ++i) {
        struct line_t* line = set -> line[i];
        assert(line);
        if (line -> valid == 1 && line -> tag == tag) {
            move_end(set, i);
            ++ summery . hits;
            if (parameters -> verbose == 1) {
                printf("hit ");
            }
            return ;
        }
    }
    ++summery . misses;
    if (parameters -> verbose == 1) {
        printf("miss ");
    }
    struct line_t* line = evict(set);
    assert(line);
    line -> valid = 1;
    line -> tag = tag;
}

void process_memory_modify(int set_id, int byte_id, int n_bytes, uint64_t tag)
{
    process_memory_load(set_id, byte_id, n_bytes, tag);
    process_memory_store(set_id, byte_id, n_bytes, tag);
}

void process_memory_op(char mode, int S, int B, int n_bytes, uint64_t T)
{
    if ('L' == mode) {
        process_memory_load(S, B, n_bytes, T);
    } else if ('S' == mode) {
        process_memory_store(S, B, n_bytes, T);
    } else {
        assert('M' == mode);
        process_memory_modify(S, B, n_bytes, T);
    }
    if (parameters -> verbose == 1) {
        printf("\n");
    }
}

int process_input(const char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    char mode = 'x';
    long long unsigned int addr = 0;
    int size = 0;
    int r = 0;
    while ((r = fscanf(fp, "%c%llX,%d\n", &mode, &addr, &size)) != EOF) {
        if (3 != r) {
            continue;
        }
        if (mode == 'I') {
            continue;
        }
        assert(mode == 'L' || mode == 'S' || mode == 'M');
        int S = get_set_id(addr);
        int B = get_byte_id(addr);
        int T = get_tag(addr);
        if (parameters -> verbose == 1) {
            printf ("%c %llx,%d ", mode, addr, size);
        }
        process_memory_op(mode, S, B, size, T);
    }

    if (ferror(fp))
        puts("I/O error when reading");
    else if (feof(fp))
        //puts("End of file reached successfully");
    fclose(fp);
    return 0;
}

int main(int argc, char** argv)
{
    init_summery();
    if (-1 == init_parameters()) {
        printf("ERROR : init params.\n");
        return 1;
    }
    if (-1 == set_parameters(argc, argv)) {
        printf("ERROR : command line.\n");
        destroy_parameters();
        return 1;
    }
    if (-1 == check_params()) {
        printf("ERROR: check params.\n");
        destroy_parameters();
        return 1;
    }
    //print_params();

    cache = build_cache();
    if (! cache) {
        printf("ERROR: failed to build cache.\n");
        return 1;
    }
    process_input(parameters -> trace_file);

    printSummary(summery . hits, summery . misses, summery . evictions);
    destroy_parameters();
    destroy_cache(cache, cache -> length);
    return 0;
}
