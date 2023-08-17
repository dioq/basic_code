#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include "register.h"

#define PAGESIZE 0x1000
#define PAGE_START(addr) ((addr) & (~(PAGESIZE - 1)))

void log_matchine_code(void *vaddr, unsigned long len)
{
    unsigned char *machine_codes = (unsigned char *)vaddr;
    for (unsigned long i = 0; i < len; i++)
    {
        printf("%02x ", (int)machine_codes[i]);
        if ((i + 1) % 4 == 0)
        {
            puts("");
        }
    }
}


// 函数指针用于保留原来的执行流程
int (*old_c_test_func)(int i);

// 新函数
int new_c_test_func(int i)
{
    int origin_ret = old_c_test_func(i);
    printf("原来的参数:%d,返回值:%d\n", i, origin_ret);
    return i * 10;
}

// 计算模块在进程中的虚拟地址(即so加载到进程后的首地址)
unsigned long get_module_vaddr(char *module)
{
    char mapfile[0x20] = {0};
    pid_t pid = getpid();
    sprintf(mapfile, "/proc/%d/maps", pid);
    FILE *fd = fopen(mapfile, "r");
    if (!fd)
    {
        printf("open %s error!\n", mapfile);
        fclose(fd);
        return 0;
    }
    char buf[0x400] = {0};
    // 按行依次读取文件所有内容
    while (fgets(buf, 0x400, fd) != NULL)
    {
        if (strstr(buf, module) != NULL)
        {
            break;
        }
    }

    unsigned long module_vaddr = strtol(buf, NULL, 16);
    // printf("The process %d's module(%s) base is: 0x%lx\n", pid, module, module_vaddr);
    fclose(fd);

    return module_vaddr;
}

void hook(unsigned long origin_vaddr, unsigned long new_vaddr)
{
    int status;
    unsigned long page_start = PAGE_START(origin_vaddr);
    printf("page start:0x%lx\n", page_start);
    // printf("page end   : %lx\n", page_end);
    status = mprotect((void *)page_start, PAGESIZE, PROT_READ | PROT_WRITE);
    if (status != 0)
    {
        perror("mprotect err");
        return;
    }

    // unsigned long result = 0;
    // unsigned long jmp_vaddr = new_vaddr;
    // printf("jmp_vaddr:0x%lx\n", jmp_vaddr);
    // asm volatile(
    //     "mov x18, %[vaddr]                  \n"
    //     "mov %[result], x18                 \n"
    //     : [result] "=r"(result)
    //     : [vaddr] "r"(jmp_vaddr)
    //     : "x18");

    // printf("result:0x%lx\n", result);
    puts("normal machine instruction(c_test_func) --->");
    log_matchine_code((void *)origin_vaddr, 0x20);

    // 40 02 1F D6
    // D6 1F 02 40             0xD6, 0x1F, 0x02, 0x40
    // 61 24 80 D2             mov x1, #0x123
    // 51 00 00 58             ldr x17, #8
    // 20 02 1f d6             br x17
    // 20 02 3F D6             blr x17
    // C0 03 5F D6             ret
    unsigned char jumpCode[] = {0x51, 0x00, 0x00, 0x58,0x20, 0x02, 0x3f, 0xd6};
    union Register reg = {0};
    reg.val = origin_vaddr;
    memcpy((void *)(jumpCode + 8), reg.bytes, 8);
    unsigned char ret_mathine_code[] = {0xC0, 0x03, 0x5F, 0xD6};
    memcpy((void *)(jumpCode + 16), ret_mathine_code, 8);

    memcpy((void *)origin_vaddr, jumpCode, 24);

    puts("modify machine instruction(c_test_func) --->");
    log_matchine_code((void *)origin_vaddr, 0x20);

    status = mprotect((void *)page_start, PAGESIZE, PROT_READ | PROT_EXEC);
    if (status != 0)
    {
        perror("2 mprotect err");
        return;
    }
}

void sighandler(int signum)
{
    printf("捕获信号 %d,跳出...\n", signum);

    // struct registers reg;
    // reg.x0.val = 0x0;
    // unsigned long jmp_vaddr = 0x0;
    // asm volatile(
    //     "mov %[out_x0], x0                  \n"
    //     "mov %[out_x1], x1                  \n"
    //     "mov %[out_x2], x2                  \n"
    //     "mov %[out_x3], x3                  \n"
    //     "mov %[out_x4], x4                  \n"
    //     "mov %[out_x5], x5                  \n"
    //     "mov %[out_x6], x6                  \n"
    //     "mov %[out_x7], x7                  \n"
    //     "mov %[out_fp], x29                  \n"
    //     "mov %[out_lr], x30                  \n"
    //     "mov %[out_sp], x31                  \n"
    //     // "mov %[out_pc], x32                  \n"
    //     : [out_x0] "=r"(reg.x0.val),
    //       [out_x1] "=r"(reg.x1.val),
    //       [out_x2] "=r"(reg.x2.val),
    //       [out_x3] "=r"(reg.x3.val),
    //       [out_x4] "=r"(reg.x4.val),
    //       [out_x5] "=r"(reg.x5.val),
    //       [out_x6] "=r"(reg.x6.val),
    //       [out_x7] "=r"(reg.x7.val),
    //       [out_fp] "=r"(reg.fp.val),
    //       [out_lr] "=r"(reg.lr.val),
    //       [out_sp] "=r"(reg.sp.val),
    //     //   [out_pc] "=r"(reg.pc.val)
    //     : [jmp_vaddr] "r"(jmp_vaddr)
    //     : );

    // for (int i = 0; i < 34; i++)
    // {
    //     unsigned long val = reg.uregs[i].val;
    //     printf("x[%d] = %lx\n", i, val);
    // }
    // puts("");
    exit(1);
}

void __attribute__((constructor)) dylibInject(void)
{
    signal(SIGSEGV, sighandler);

    printf("Hello, hook was starting ...\n");
    char *module_name = "/data/local/tmp/main";
    unsigned long module_vaddr = get_module_vaddr(module_name);
    printf("%s --> %s vaddr:0x%lx\n", __FUNCTION__, module_name, module_vaddr);

    unsigned long target_func_vaddr = module_vaddr + 0x19C0;

    printf("new_c_test_func vaddr:0x%lx\n", (unsigned long)&new_c_test_func);
    hook(target_func_vaddr, (unsigned long)&new_c_test_func);
}
