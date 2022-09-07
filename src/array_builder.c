#include <stdio.h>
#include <string.h>
#include "array_builder.h"

array_builder_t* array_builder_new(size_t type_size)
{
	array_builder_t* self = malloc(sizeof(array_builder_t));
	self->data = NULL;
	self->type_size = type_size;
	self->count = 0;
}

static uint8_t is_pow2(uint32_t num)
{
	return !(num & (num - 1));
}

void array_builder_push(array_builder_t* self, item_t(void) item)
{
	if (self->count < 2 || is_pow2(self->count))
	{
		uint32_t new_capacity;
		if (self->count)
		{
			new_capacity = self->count * 2;
		}
		else
		{
			new_capacity = 1;
		}

		void* new_data = malloc(new_capacity * self->type_size);
		if (self->data != NULL) memcpy(new_data, self->data, self->count * self->type_size);
		free(self->data);

		self->data = new_data;
	}
	self->count++;

	void* copy_destination = self->data + ((self->count - 1) * self->type_size);
	memcpy(copy_destination, item, self->type_size);
}

void array_destroy(array_t(void) array) {
    free(array);
}

void array_builder_destroy(array_builder_t* self)
{
	free(self);
}

void array_builder_clear(array_builder_t* self) {
    free(self->data);

    self->data = NULL;
    self->count = 0;
}

uint32_t array_builder_build(array_builder_t* self, array_t(void)* result)
{
	void* array = malloc(self->count * self->type_size);
	memcpy(array, self->data, self->count * self->type_size);

	*result = array;
	return self->count;
}
