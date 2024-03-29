# 寻址

现代的操作系统要求编写PIC,也就是说在编码指令的时候,不能真的把一个绝对地址放到寄存器里,因为这个地址在每次加载模块的时候是变化的。
为了解决这个问题,实现PIC一般采用PC-relative的编码模式。这是因为,在加载程序的时候,尽管基地址是变化的,但是地址与地址之间的距离是不变的。因此,可以计算目标地址与当前指令地址的差值,而CPU在执行指令的时候,会去寻找当前PC的值与其相加。这样既保证了PIC,也能实现寻址的目的。

## adr

adr    x1, label
    .p2align   2
label:
    .long    0x114514

提供21位来编码 label 与PC的差值,当前PC的+/-1MB范围内的标签

## adrp

ADRP  Rn, label
先计算 label 所在的页,再计算当前PC所在的页,两者相减,得到一个距离。而页大小是4KB,所以这个距离一定是4KB的倍数,从而可以放心地将其除以4KB。
这样的话,可以表示的距离范围,就是1MB再乘以4KB,也就是+/-4G
Rn 存储的值是 label 所在的页的地址

## 取低12位

:lo12:label
低12位就是 label 在 page 内的偏移

## 获取 label 虚拟地址

adrp Rn, label
add  Rn, Rn, :lo12:label
