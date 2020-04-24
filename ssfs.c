#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>


static  const  char *dirpath = "/home/sun/Documents";
char key[100] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";

void encript(char* c) {
    if(strcmp(c, ".") == 0 || strcmp(c, "..")) return;
    for(int i=0; i<strlen(c); i++) {
        for(int j=0; j<strlen(c); j++) {
            if(c[i] == key[j]) {
                c[i] = key[(j+10) % 87];
                return;
            }
        }
    }
}

void decript(char* c) {
    if(strcmp(c, ".") == 0 || strcmp(c, "..")) return;
    for(int i=0; i<strlen(c); i++) {
        for(int j=0; j<strlen(c); j++) {
            if(c[i] == key[j]) {
                c[i] = key[(j+77) % 87];
                return;
            }
        }
    }
}

static  int  xmp_getattr(const char *path, struct stat *stbuf) {
    int res;
    char filepath[1000];
    char filename[1000];

    sprintf(filename, "%s", path);
    encript(filename);

    sprintf(filepath,"%s%s", pathdir, filename);
    res = lstat(fpath, stbuf);

    if(res == -1) return -errno;
    return 0;
}


static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
	char fpath[1000];
	char fname[1000];
	if(strcmp(path,"/") == 0) {
		path = dirpath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fname,"%s",path);
		encript(fname);
		sprintf(fpath, "%s%s", dirpath, fname);
	} 
	int res = 0;

	DIR *dp;
	struct dirent *de;
	(void) offset;
	(void) fi;
	
	dp = opendir(fpath);
	if(dp == NULL) return -errno;

	while((de=readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));

		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		res = (filler(buf, de->d_name, &st, 0));

		if(res!=0) break;
	}
	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	char fpath[1000];
	if(strcmp(path,"/") == 0) {
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	
	int res = 0;
	int fd = 0 ;
	(void) fi;
	fd = open(fpath, O_RDONLY);
	
	if(fd == -1) return -errno;
	res = pread(fd, buf, size, offset);

	if(res == -1) res = -errno;

  	close(fd);
	return res;
}

static  struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
	.readdir = xmp_readdir,
	.read = xmp_read,
};

int main (int argc, char* argv[]){
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
