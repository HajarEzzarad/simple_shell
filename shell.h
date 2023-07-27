#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define COMD_NORM 0
#define COMD_OR 1
#define COMD_AND 2
#define COMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;


/**
 * struct lists - singly linked list
 * @num: the number field
 * @s: a string
 * @next: points to the next node
 */
typedef struct lists
{
	int num;
	char *s;
	struct lists *next;
} list_t;

/**
 *struct psinfo - contains pseudo-arguements to pass into a func
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@p: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_n: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@filename: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@histy: the history node
 *@al: the alias node
 *@envr_chang: on if environ was changed
 *@st: the return status of the last exec'd command
 *@comd_buffer: address of pointer to cmd_buf, on if chaining
 *@comd_buffer_type: CMD_type ||, &&, ;
 *@readfiledesc: the fd from which to read line input
 *@histocount: the history line number count
 */
typedef struct psinfo
{
	char *arg;
	char **argv;
	char *p;
	int argc;
	unsigned int line_count;
	int err_n;
	int linecount_flag;
	char *filename;
	list_t *env;
	list_t *histy;
	list_t *al;
	char **environ;
	int envr_chang;
	int st;

	char **comd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int comd_buffer_type; /* CMD_type ||, &&, ; */
	int readfiledesc;
	int histocount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct built - contains a builtin string and related function
 *@type: the builtin command flag
 *@f: the function
 */
typedef struct built
{
	char *type;
	int (*f)(info_t *);
} built_t;

/* shloop.c */
int hshell(info_t *, char **);
int find_built(info_t *);
void find_comd(info_t *);
void f_comd(info_t *);

/* pars.c */
int iscmd(info_t *, char *);
char *dupl_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err.c */
void _errputs(char *);
int _errputchar(char);
int _putfiledesc(char c, int fd);
int _putsfiledesc(char *s, int fd);

/* str.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* str1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* reloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memo.c */
int bfree(void **);

/* atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* err1.c */
int _erroratoi(char *);
void print_err(info_t *, char *);
int print_dec(int, int);
char *conv_number(long int, int, int);
void rm_comments(char *);

/* built.c */
int _myexit(info_t *);
int _mcd(info_t *);
int _mhelp(info_t *);

/* built1.c */
int _history(info_t *);
int _alias(info_t *);

/*getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHand(int);

/* info.c */
void clearinfo(info_t *);
void setinfo(info_t *, char **);
void freeinfo(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _envm(info_t *);
int _setenvm(info_t *);
int _unsetenvm(info_t *);
int pop_env_list(info_t *);

/* getenviron.c */
char **_getenviron(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *gethistoryfile(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* list.c */
list_t *addnode(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* list1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* variables.c */
int ischain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int replace_al(info_t *);
int replace_v(info_t *);
int replace_str(char **, char *);

#endif

