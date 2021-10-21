#include "./string_handle.h"

char * to_upper(char *str){
    // 先保留最初的地址。因为等会str指向的位置会变来变去的。
    char *dest = str;
    // 如果还不是空字符
    while (*str != '\0')
    {
        // 如果是小写字母
        if (*str >= 'a' && *str <= 'z')
        {
            // 变为大写字母。小写和大写字母的ASCII值有个固定的差值
            *str -= 'a' - 'A';
        }

        // 遍历下一个字符
        str++;
    }
    // 返回字符串
    return dest;
}
