
用ptrace 远程调用 mmap 在 目标进程中开辟一块空间，然后把 待注入的 动态库 so 写入这块空间。
接着便可以调用 so 库里的 函数了.   so 库里的函数 只要能拿到 目标进程的其他函数地址，也可以
把这个地址转化成 函数指针，然后调用这个函数