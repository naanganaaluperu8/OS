#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
int main(){
	struct stat s;
	stat("stat.c",&s);
	printf("Size: %lu\n",s.st_size);
	printf("Inode: %lu\n",s.st_ino);
	printf("Mode: %u\n",s.st_mode & 0777);
	printf("UID: %u\n",s.st_uid);
	printf("GID: %u\n",s.st_gid);
	printf("access Time: %s",ctime(&s.st_atime));
	printf("Modification Time: %s",ctime(&s.st_mtime));
	return 0;
}
