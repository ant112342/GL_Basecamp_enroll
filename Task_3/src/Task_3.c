/*
 ============================================================================
 Name        : Task_3.c
 Author      : Anton Kotsiubailo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void dostat(char*, char*);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char*);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
int cmp(const void * a, const void * b);

int main(void)
{
	int 	MAXDIR = 10000;
	int 	totalBlock = 0;
	int 	iStart = 0;
	int 	iEnd = 0;
	char 	path[MAXDIR];
	char 	fileName[255][255];
	struct 	stat info;

	getcwd(path, MAXDIR);

	DIR *dir = opendir(path);
	if (dir)
	{

		struct dirent *direntp;
		while ((direntp = readdir(dir)) != NULL)
		{
			strcpy(fileName[iEnd++], direntp->d_name);
			stat(direntp->d_name, &info);
			totalBlock += (info.st_blocks / 2);
		}

		closedir(dir);

		qsort(fileName, iEnd, sizeof(fileName[0]), cmp);
		printf("total %d\n", totalBlock);

		for (iStart = 0; iStart < iEnd; iStart++)
		{
			dostat(fileName[iStart], path);
		}
	}
	else
	{
		printf("Error opening directory");
	}
	return 0;
}

void dostat(char *filename, char *dirname)
{
	struct stat info;
	char* way_to_file = malloc((strlen(filename) + strlen(dirname) + 2)*sizeof(*way_to_file));
	strcpy(way_to_file, dirname);
	strcpy(way_to_file + strlen(dirname), "/\0");
	strcpy(way_to_file + strlen(way_to_file), filename);

	if (stat(way_to_file, &info) == -1)
	{
		printf("Error %s\n", way_to_file);
		perror(filename);
	}
	else
		show_file_info(filename, &info);
	free(way_to_file);
}

void show_file_info(char *filename, struct stat *info_p)
{
	char modestr[12];
	mode_to_letters(info_p->st_mode, modestr);
	printf("%s ", modestr);
	printf("%4d ", 	(int)info_p->st_nlink);
	printf("%-8s ",	 uid_to_name(info_p->st_uid));
	printf("%-8s ",  gid_to_name(info_p->st_gid));
	printf("%8ld ", (long)info_p->st_size);
	printf("%.12s ", 4 + ctime(&(info_p->st_mtime)));
	printf("%s\n",   filename);
}

void mode_to_letters(int mode, char *str)
{
	strcpy(str, "----------");
	if (S_ISDIR(mode))
		str[0] = 'd';
	if (S_ISCHR(mode))
		str[0] = 'c';
	if (S_ISBLK(mode))
		str[0] = 'b';
	if (S_ISFIFO(mode))
		str[0] = 'p';
	if (S_ISSOCK(mode))
		str[0] = 's';
	if (S_ISLNK(mode))
		str[0] = 'l';
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if (mode & S_IXUSR)
		str[3] = 'x';
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if (mode & S_IXGRP)
		str[6] = 'x';
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	if (mode & S_IXOTH)
		str[9] = 'x';
}

char *uid_to_name(uid_t uid)
{
	struct passwd *getwuid(), *pw_ptr;
	static char numstr[10];

	if ((pw_ptr = getpwuid(uid)) == NULL)
	{
		sprintf(numstr, "%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

char *gid_to_name(gid_t gid)
{
	struct group *getgrgid(gid_t), *grp_ptr;
	static char numstr[10];

	if ((grp_ptr = getgrgid(gid)) == NULL)
	{
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}

int cmp(const void * a, const void * b)
{
	return strcmp((char*)a, (char*)b);
}

