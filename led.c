/*
 * led: A light version of the ED editior created by Ken Thompson, 
 *	one of the key elements of Unix Systems. 
 *	"The most user-hostile editor ever created"
 *	- Peter H. Salus
 *	
 *	Copyright (C) 2025 Modestino Carbone
 *	All rights reserved.
 *
 *
+++++++++++++++ Makefile +++++++++++++++

all: 		led

led: 		led.c
		$(CC) led.c -o led -ledit

install: 	led
		sudo cp led /usr/local/bin

clean:		
		rm -f led

++++++++++ available commands ++++++++++

 ________________________________________________________
| w <file_name> | select a target file                   |
|---------------|----------------------------------------|
| ,p            | print a file                           |
|---------------|----------------------------------------|
| ,np           | print a file with numbered lines       |
|---------------|----------------------------------------|
| x,yp          | print a file from line x to y          |
|---------------|----------------------------------------|
| x,ynp         | print a numbered file from line x to y |
|---------------|----------------------------------------|
| <number>      | select a line                          |
|---------------|----------------------------------------|
| p             | print the corresponding line           |
|---------------|----------------------------------------|
| a             | append text at the corresponding line  |
|---------------|----------------------------------------|
|_q_____________|_quit___________________________________| 
	
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <editline/readline.h>
#include <sys/stat.h>

// Constant
#define MAX_FILE_LEN 20
// Useless but usefull stucture
typedef enum boolean {False = 0, True = 1} boolean;
// This stucture represents a file access
typedef struct {
	int num_line; 		// The last line read or modified by user
	char file_name[MAX_FILE_LEN];	// The file name.
}file_t;

// This function generates the number of character of a plaintext,
// so that dimension are expressed in byte sizeof(char)
long get_file_size(const char *filename) {

	struct stat st;
	if (stat(filename, &st) == False)
	return st.st_size;   // dimension in byte
	return -1;

}

// This function checks if the user input is composed by only numbers
boolean is_a_number(char *str){
	if (*str == '\0') return False; 
	while (*str != '\0') {
		if ((int)*str<48 || (int)*str>57) return 0;
		str++;
	}
	return True;
}

// This function finds the number of rows
int num_rows(file_t file) {

	FILE *fptr = fopen(file.file_name, "r");
	if (!fptr) {
		printf("?\n");
		return False;
	}
	int line = 1;
	int c;
	while ((c = fgetc(fptr)) != EOF) {
		if (c == '\n') {
		    line++;
		}
	}
	fclose(fptr);
	return line;
}


void file_write(file_t *file){

	FILE *fptr  = fopen(file->file_name, "r");
	if(fptr == NULL){
		char mk[256];
		snprintf(mk, sizeof(mk), "touch %s", file->file_name);
		system(mk);
		// printf("%s was created\n", file.file_name);
		fptr = fopen(file->file_name, "w");
		printf("0\n");
		fclose(fptr);
		file->num_line = 0; 
		return;
	};
	printf("%ld\n", get_file_size(file->file_name));
	fclose(fptr);
	// initialize line bookmark
	file->num_line = 0; 
	return;

}

boolean file_print_range(file_t file, boolean num_flag, int from, int to) {

	int c;
	int line = 1;
	FILE *fptr = fopen(file.file_name, "r");

	if (!fptr) {
		printf("?\n");
		return False;
	}

	// check ranges
	if(from < 0 || to >  num_rows(file)) {
		printf("?\n");
		return False;
	}
	
	if (num_flag)
	printf("%d\t", from);
	
	while ((c = fgetc(fptr)) != EOF) {
	if ((line >= from && line <= to))
	    putchar(c);

		if (c == '\n') {
		    line++;
		    if ( num_flag && (line > from && line <= to))
			printf("%d\t", line);
		}
	}
	printf("\n");
	fclose(fptr);

	return True;

}

boolean file_append_line(file_t *file, char *text){

	FILE *fin;
	int line = 0;
	int c;
	int from = file->num_line;
	// input file
	fin = fopen(file->file_name, "r");
	if (!fin) {
		perror("?\n");
		return False;
	}

	if (get_file_size(file->file_name) != False){

		char tmpname[] = "/tmp/tmpfileXXXXXX";
		int fd = mkstemp(tmpname);
		if (fd == -1) {
			printf("?\n");
			fclose(fin);
			return False;
		}

		FILE *fout = fdopen(fd, "w+");
		if (!fout) {
			printf("?\n");
			close(fd);
			fclose(fin);
			return False;
		}

		while ((c = fgetc(fin)) != EOF) {
			fputc(c, fout);

			if (c == '\n') {
			   line++;
			   if(line == from) {fputs(text, fout); fputc('\n', fout);}
			}
		}

		if (from>line){ fputs(text, fout);  fputc('\n', fout);}
		
		
	    	fclose(fout);
		fclose(fin);

		if (remove(file->file_name) != False) {
			printf("?\n");
			remove(tmpname);
			return False;
	    	}

	    	if (rename(tmpname, file->file_name) != False) {
			printf("?\n");
			remove(tmpname);
			return False;
	    	}

	} else { //if input file is empty

		fclose(fin);
		fin = fopen(file->file_name, "w");
		fputs(text, fin); fputc('\n', fin);
		fclose(fin);

	}


	return True;
}

// TO DO ...
int file_delete_range(){

	return 1;
}

int main(int argc,char **argv){
	
	// Definition of the file pointer
	FILE *fptr;
	// Definition of the file struct
	file_t new_file;
	// Line buffer which extracts command substrings
	char str[MAX_FILE_LEN];
	// Operands for range commands (e.g., 1,2p)
	int op1,op2; 
	// suffix space for  range commands (e.g., in 1,2p suffix = 'p')
	char suffix[3] = {0};  

	// The main argument is expected to be an existing file
	if(argc > 1){

		FILE *fptr  = fopen(argv[1], "r");
		if(fptr != NULL){
			new_file.num_line = 0;
			strcpy(new_file.file_name, argv[1]);
			printf("%ld\n", get_file_size(new_file.file_name));
			fclose(fptr);
		}else{
			printf("%s: No such file or directory\n", argv[1]);

		};
		
	}

	// Main loop which manipulate text
	while(True){

		// User input line 
		char* input_bar = readline("");

		// Quit condition
		if (strcmp(input_bar,"q")==0) {
			free(input_bar);
			return False;

/* =============================== Write-mode =============================== */


		} else if(sscanf(input_bar, "w %s\n", str) == 1) { 
			
			// Definition of append behavior w <file name>
			strcpy(new_file.file_name, str);	
			file_write(&new_file);

		} else if(strcmp(input_bar,"a") == False) {

			// Definition of append behavior 'a'
			char *sub;
			while ((sub = readline("")) != NULL) {
				if (strcmp(sub, ".") == False) { 
					free(sub); 
					break;
				}
				file_append_line(&new_file, sub);
				new_file.num_line++;
				free(sub);
			}

/* =============================== Read-mode =============================== */

		
		} else if(strcmp(input_bar,",p") == False) {

			// Print the entire file content

			int file_len = num_rows(new_file);
			new_file.num_line = file_len;
			file_print_range(new_file, False, 1, file_len);
		
		} else if(strcmp(input_bar,",np") == False) {

			// Print the entire file content with number of lines
			
			int file_len = num_rows(new_file);
			new_file.num_line = file_len;
			file_print_range(new_file, True, 1, file_len);
		
		} else if(strcmp(input_bar,"p") == False) {

			// print the last selected/edited line
			file_print_range(new_file, False, new_file.num_line, new_file.num_line);
		
		} else if(strcmp(input_bar,"np") == False) {

			// print a selected/edited number and it's line
			file_print_range(new_file, True, new_file.num_line, new_file.num_line);

		} else if(is_a_number(input_bar)) { 
			
			// print the line which match to the input number
			new_file.num_line = atoi(input_bar);
			file_print_range(new_file, False, new_file.num_line, new_file.num_line);
		
		} else if (sscanf(input_bar, "%d,%d%2s", &op1, &op2, suffix) >= 2){	

				if (strcmp(suffix, "p") == False) {
					
					file_print_range(new_file, False, op1, op2);

				} else if (strcmp(suffix, "np") == False) {
			
					file_print_range(new_file, True, op1, op2);

				} else {
					printf("?\n");  // unknown suffix
				}

    		} else {	

			// error condition <-- what kind of error, who knows... ;)
			printf("?\n");	
		
		}

		free(input_bar);
	 	
	}
		
}