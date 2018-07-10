#include <stdio.h>
#include <string.h>
#include <ctype.h>



const char* extensions[] = { ".csv", ".tl5", ".tr9", ".tc9" };
char* delims[] = { ",", "|", "|", "|" };


#define CSV 0
#define TL5 1
#define TR9 2
#define TC9 3
#define NUM_EXTS 4


/** Removes leading whitespace from string */
char* ltrim(char* str)
{
	int i = 0;
	int len = strlen(str);
	while (isspace(str[i]))
		i++;
	memmove(str, &str[i], len-i);
	str[len-i] = 0;
	return str;
}

/** Removes trailing whitespace from string */
char* rtrim(char* str)
{
	int i;
	int len = strlen(str);
	i = len - 1;
	while (isspace(str[i]))
		i--;
	str[++i] = 0;
	return str;
}

/** Removes whitespace on both ends of string */
char* trim(char* str)
{
	return ltrim(rtrim(str));
}



int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("usage: %s input_file output_file\n", argv[0]);
		return 0;
	}


	char* ext = strrchr(argv[1], '.');
	if (!ext) {
		printf("Input file %s is missing an extension!\n", argv[1]);
		return 0;
	}

	int i;
	for (i=0; i<NUM_EXTS; ++i) {
		if (!strcmp(ext, extensions[i]))
			break;
	}
	if (i == NUM_EXTS) {
		printf("Input file %s has an invalid extension!\n", argv[1]);
		return 0;
	}
	char* in_delim = delims[i];   // (i) ? "|" : ",";

	ext = strrchr(argv[2], '.');
	if (!ext) {
		printf("Output file %s is missing an extension!\n", argv[2]);
		return 0;
	}
	for (i=0; i<NUM_EXTS; ++i) {
		if (!strcmp(ext, extensions[i]))
			break;
	}
	if (i == NUM_EXTS) {
		printf("Output file %s has an invalid extension!\n", argv[2]);
		return 0;
	}
	int out_type = i;
	char* out_delim = delims[i];


	FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "w");

	char line[1024] = { 0 };

	char* tok;
	int first;
	int len;
	while (fgets(line, 1024, fin)) {
		first = 1;
		tok = strtok(line, in_delim);
		while (tok) {
			trim(tok);   // I assume there can be no spaces in a csv field

			if (!first)   // only print delimiter after the first field
				fprintf(fout, "%s", out_delim);

			if (out_type == CSV) {
				fprintf(fout, "%s", tok);
			} else if (out_type == TL5) {
				fprintf(fout, "%-.5s", tok);  //print out first 5 characters left justified
			} else if (out_type == TR9) {
				len = strlen(tok);
				if (len > 9)
					memmove(tok, &tok[len-9], 10);  // shift back 9 + \0 to front

				fprintf(fout, "%9s", tok);
			} else {
				// TODO bonus format stuff
				len = strlen(tok);
			}


			//puts(tok);   // debugging just printing tok to console
			tok = strtok(NULL, in_delim);
			first = 0;  // so non-first fields print delimiter first
		}
		fputc('\n', fout);
	}


	fclose(fin);
	fclose(fout);


	return 0;
}
out3.csv
abc,def,ghi,xyzejkleuaoei
mn,opqrs1234567,blah,abcde
blaheoeuo134,hello,goodbye,abe


trunc.tr9
      abc|      def|      ghi|jkleuaoei
       mn|rs1234567|     blah|    abcde
heoeuo134|    hello|  goodbye|      abe


cat out3.csv | ./prog > trunc.tr9

~/Downloads/tutoring/Wyzant/Joseph_M $ ./prog out3.csv trunc.tr9
abc
def
ghi
jkleuaoei
mn
rs1234567
blah
abcde
heoeuo134
hello
goodbye
abe
