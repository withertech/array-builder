#include <stdint.h>
#include <stddef.h>
#include <malloc.h>

#define item_t(T) T*
#define array_t(T) T*

typedef struct {
    void* data;
	size_t type_size;
    uint32_t count;
} array_builder_t;

array_builder_t* array_builder_new(size_t type_size);
void array_builder_push(array_builder_t* self, item_t(void) item);
uint32_t array_builder_build(array_builder_t* self, array_t(void)* result);
void array_builder_clear(array_builder_t* self);
void array_builder_destroy(array_builder_t* self);
void array_destroy(array_t(void) array);