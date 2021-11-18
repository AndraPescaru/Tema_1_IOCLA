#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300;

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;

void touch (Dir* parent, char* name) {
	
	File *aux = parent -> head_children_files;
	if(parent -> head_children_files == NULL) {
		parent -> head_children_files = (File*)malloc(sizeof(File));
		parent -> head_children_files -> name = (char*)malloc(20 * sizeof(char));
		strcpy(parent -> head_children_files -> name, name);
		parent -> head_children_files -> parent = parent;
		parent ->  head_children_files -> next = NULL;
	} else {
		int ok = 1;
		File *aux2 = parent -> head_children_files;
		while (parent -> head_children_files && ok) {
			if (!strcmp(parent -> head_children_files -> name, name)) {
				printf("File already exists\n");
				ok = 0;
				parent -> head_children_files = aux;
			} else {
				aux2 = parent -> head_children_files;
				parent -> head_children_files = parent -> head_children_files -> next;
			}
		}
		
		if (ok) {

			File *p = (File*)malloc(sizeof(File));
			p -> name = (char*)malloc(20 * sizeof(char));
			strcpy(p -> name, name);
			p -> parent = parent;
			p -> next = NULL; 
			aux2-> next= p;
			parent -> head_children_files = aux;
		}
	}
	
	
	
}


void mkdir (Dir* parent, char* name) {
	Dir *aux = parent -> head_children_dirs;
	if(parent -> head_children_dirs == NULL) {
		parent -> head_children_dirs = (Dir*)malloc(sizeof(Dir));
		parent -> head_children_dirs -> name = (char*)malloc(20 * sizeof(char));
		strcpy(parent -> head_children_dirs -> name, name);
		parent -> head_children_dirs -> head_children_files = NULL;
		parent -> head_children_dirs -> head_children_dirs = NULL;
		parent -> head_children_dirs -> parent = parent;
		parent ->  head_children_dirs -> next = NULL;
	} else {
		int ok = 1;
		while (parent -> head_children_dirs && ok) {
			if (!strcmp(parent -> head_children_dirs -> name, name)) {
				printf("Directory already exists\n");
				ok = 0;
				parent -> head_children_dirs = aux;
			} else {
				parent -> head_children_dirs = parent -> head_children_dirs -> next;
			}
		}
		
		if (ok) {

			Dir *p = (Dir*)malloc(sizeof(Dir));
			p -> name = (char*)malloc(20 * sizeof(char));
			strcpy(p -> name, name);
			p -> parent = parent;
			p -> next = NULL;
			parent -> head_children_dirs -> next = p;
			parent -> head_children_dirs = aux;
		}
	}
}

void ls (Dir* parent) {
	
	if (parent -> head_children_dirs) {
		Dir *aux = parent -> head_children_dirs;

		while (parent -> head_children_dirs) {
			printf("%s\n", parent -> head_children_dirs -> name);
			parent -> head_children_dirs = parent -> head_children_dirs -> next;
		}	

		parent -> head_children_dirs = aux;
	}

	if (parent -> head_children_files) {
		File *aux1 = parent -> head_children_files;

		while (parent -> head_children_files ) {
			printf("%s\n", parent -> head_children_files -> name);
			parent -> head_children_files = parent -> head_children_files -> next;
		}

		parent -> head_children_files = aux1;
	}

}

void rm (Dir* parent, char* name) {
	
	if (!parent -> head_children_files) {
		printf("Could not find the file\n");
	} else {

		int ok = 1;
		if (parent -> head_children_files -> next == NULL && ok) {
			ok  = 0;
			if (!strcmp(parent -> head_children_files -> name, name)) {
				File *aux = parent -> head_children_files;
				parent -> head_children_files = NULL;
				free(aux -> name);
				free(aux);
			} else {
				printf("Could not find the file\n");
			}
		}

		if (ok) {
			File *aux = parent -> head_children_files;
			File *p = parent -> head_children_files;
			int gasit = 1;
			if (!strcmp(aux -> name, name)) {
				parent -> head_children_files = aux -> next;
				free(p -> name);
				free(p);
				gasit = 0;
			} else {
				aux = aux -> next;
				while (aux && gasit) {
					if (!strcmp(aux -> name, name)) {
						p -> next = aux -> next;
						free(aux -> name);
						free(aux);
						gasit = 0;
					} else {
						aux = aux -> next;
						p = p -> next;
					}
				}
			}
			if (gasit) {
				printf("Could not find the file\n");
			}
		}
		

	}

}

void rmdir (Dir* parent, char* name) {}

void cd(Dir** target, char *name) {}

// char *pwd (Dir* target) {}

void stop (Dir* target) {}

void tree (Dir* target, int level) {}

void mv(Dir* parent, char *oldname, char *newname) {}

int main () {

	Dir *dir = (Dir*)malloc(sizeof(Dir));
	dir -> name = (char*)malloc(20 * sizeof(char));
	strcpy(dir -> name, "home");
	dir -> parent = NULL;
	dir -> head_children_files =  NULL;
	dir -> head_children_dirs = NULL;

	char *comanda = (char*)malloc(20 * sizeof(char));
	char *nume = (char*)malloc(20 * sizeof(char));
	do
	{
		
		scanf("%s", comanda);

		if (!strcmp(comanda, "touch")) {
			

			scanf("%s", nume);

			touch(dir, nume);
		}

		if (!strcmp(comanda, "mkdir")) {
			

			scanf("%s", nume);

			mkdir(dir, nume);
		}

		if (!strcmp(comanda, "ls")) {
		

			ls(dir);
		}

		if (!strcmp(comanda, "rm")) {
			scanf("%s", nume);
			rm(dir, nume);
		}

	} while (strcmp(comanda,"stop") != 0);
	
	return 0;
}
