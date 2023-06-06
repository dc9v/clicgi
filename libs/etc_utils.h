#include <stdbool.h>

#ifndef ETC_UTILS_H
#define ETC_UTILS_H

const char* get_file_extenstion(const char *filename);
const char* get_mime_type(const char *file_ext);
bool compare_case_insensitive(const char *comp1, const char *comp2);
char* decode_url(const char *url);

#endif
