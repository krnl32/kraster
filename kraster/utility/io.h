#ifndef KRASTER_IO_H
#define KRASTER_IO_H

#include <stddef.h>

char *kraster_io_read_file(const char *path, size_t *out_size);

#endif
