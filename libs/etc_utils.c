#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char MIME_TYPES[][] =
{
{ "html", "text/html" },
{ "htm", "text/html" },
{ "txt", "text/plain" },
{ "jpg", "image/jpeg" },
{ "jpeg", "image/jpeg" },
{ "png", "image/png" },
{ "svg", "image/svg+xml" },
{ "json", "application/json" },
{ "", "application/octet-stream" } };

const char* get_file_extension(const char *file_name)
{
	const char *dot = strrchr(file_name, '.');

	if (!dot || dot == file_name)
	{
		return "";
	}

	return dot + 1;
}

const char* get_mime_type(const char *file_ext)
{
	for (size_t i = 0; i < sizeof(MIME_TYPES); i++)
	{
		if (strcasecmp(file_ext, MIME_TYPES[i][0]) == 0)
		{
			return MIME_TYPES[i][1];
		}
	}

	return MIME_TYPES[0][1];

	/*if (strcasecmp(file_ext, "html") == 0 || strcasecmp(file_ext, "htm") == 0)
	 {
	 return "text/html";
	 }

	 else if (strcasecmp(file_ext, "txt") == 0)
	 {
	 return "text/plain";
	 }

	 else if (strcasecmp(file_ext, "jpg") == 0 || strcasecmp(file_ext, "jpeg") == 0)
	 {
	 return "image/jpeg";
	 }

	 else if (strcasecmp(file_ext, "png") == 0)
	 {
	 return "image/png";
	 }*/

	return "application/octet-stream";
}

bool compare_case_insensitive(const char *comp1, const char *comp2)
{
	while (*comp1 && *comp2)
	{
		if (tolower((unsigned char) *comp1) != tolower((unsigned char) *comp2))
		{
			return false;
		}

		comp1++;
		comp2++;
	}

	return *comp1 == *comp2;
}

char* decode_url(const char *url)
{
	size_t decoded_len = 0;
	size_t src_len = strlen(url);
	char *decoded = malloc(src_len + 1);

	for (size_t i = 0; i < src_len; i++)
	{
		if (url[i] == '%' && i + 2 < src_len)
		{
			int hex_val;
			sscanf(url + i + 1, "%2x", &hex_val);
			decoded[decoded_len++] = hex_val;
			i += 2;
		}
		else
		{
			decoded[decoded_len++] = url[i];
		}
	}

	decoded[decoded_len] = '\0';
	return decoded;
}

/*char* get_file_case_insensitive(const char *file_name)
 {
 DIR *dir = opendir(".");
 struct dirent *entry;
 char *found_file_name = NULL;

 if (dir == NULL)
 {
 perror("opendir");
 return NULL;
 }

 while ((entry = readdir(dir)) != NULL)
 {
 if (case_insensitive_compare(entry->d_name, file_name))
 {
 found_file_name = entry->d_name;
 break;
 }
 }

 closedir(dir);
 return found_file_name;
 }*/

