// mman_client.cpp
// 2018/10/28 Robin.Rowe@CinePaint.org
// Inspired by http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#ifndef _WIN32
#define shm_close close
#define shm_flush(fd) 

int shm_size(int fd)
{	struct stat sb;
	fstat(fd, &sb);
	off_t length = sb.st_size;
	return int(length);
}
#endif

int main(int argc, char **argv) 
{	int oflags=O_RDWR;
	int i;
	char *name = "/mmanjunk";
	int fd = shm_open(name, oflags, 0644 );
	fprintf(stderr,"Shared Mem Descriptor: fd=%d\n", fd);
	assert (fd>0);
	size_t length = shm_size(fd);
	char* p = (char *) mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	printf("Shared Mem Address: %p [0..%llu]\n", p, length-1);
	assert (p);
	printf("%s",p);
	// change 1st byte
	p[0] = 'H' ;
	printf("%s",p);
	shm_flush(fd);
	shm_close(fd);
	return 0;
}

/* Shared Mem Descriptor: fd=1
Shared Mem Address: 0000021930530000 [0..2047]
hello world!!
Hello world!!
*/