# POSIX标准(可移植操作系统接口)
    Portable Operating System Interface.
    由电气和电子工程师协会(Institute of Electrical and Eletronics Engineers,IEEE)最初是为了提高Unix环境下应用程序的可移植性而开发的标准.
    但并不局限于Unix, 连Windows NT都支持.

# 通信管道
    管道 Pipes
        Unix命令行环境中,管道常用于一个命令的输出作为另一个命令的输入的情况.
            ls | grep '^a'  -> ls出非a字符的文件名
        
        Ordinary pipes允许两个进程以标准的生产者-消费者方式通信,生产者对管道一端(写端)进行写操作,消费者从另一端(读端)进行读操作.因此 Ordinary pipes是单向的,只允许单向通信.
            两端分别用描述字fd[0] (读端) 和fd[1] (写端)描述.
            两端固定任务:读 / 写
            父进程 和 子进程之间 是两条管道, 关闭是为了区分,哪边入哪边出
        
        Named pipes 命名管道, 提供更强大的通信工具.双向, 不需要亲子关系. 一旦建立,可以几个进程用它来通信.

        socket