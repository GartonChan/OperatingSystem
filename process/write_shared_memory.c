#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    /* the size (in bytes) of shared memory object */
    // 共享内存对象的大小SIZE
    const int SIZE = 4096;
    /* name of the shared memory object */
    // 共享内存对象的名称
    const char *name = "OS";
    /* strings written to shared memory */
    // 写入的字符串信息
    const char *message_0 = "Hello";
    const char *message_1 = "World!";
    /* shared memory file descriptor */
    // 共享内存对象的文件描述符
    int shm_fd;
    /* pointer to shared memory obect */
    // 指向共享内存对象的指针
    void *ptr;
    /* create the shared memory object */
    // 创建共享内存对象(映射到内存空间后指向)
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */
    // 调整(缩小为SIZE)共享内存对象大小
    ftruncate(shm_fd, SIZE);
    /* memory map the shared memory object */
    // 将共享内存对象映射到内存空间中
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    /* write to the shared memory object */
    // 向共享内存对象写入信息
    sprintf(ptr,"%s",message_0);
    ptr += strlen(message_0);
    sprintf(ptr,"%s",message_1);
    ptr += strlen(message_1);
    return 0;
}
