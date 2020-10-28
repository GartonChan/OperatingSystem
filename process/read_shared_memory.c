#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
    /* the size (in bytes) of shared memory object */
    // 共享内存对象的大小SIZE
    const int SIZE= 4096;
    /* name of the shared memory object */
    // 共享内存对象的名称
    const char *name = "OS";
    /* shared memory file descriptor */
    // 共享内存文件描述符
    int shm_fd;  
    /* pointer to shared memory obect */
    // 指向共享内存对象的指针
    void *ptr;
    /* open the shared memory object */
    // 打开共享内存对象
    shm_fd = shm_open(name, O_RDONLY, 0666);
    /* memory map the shared memory object */
    // 映射到内存
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    /* read from the shared memory object */
    // 从共享内存对象中读取
    printf("%s",(char *)ptr);
    /* remove the shared memory object */
    // 移除共享内存对象
    shm_unlink(name);
    return 0;
}