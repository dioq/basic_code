# 操作 Mach-O 文件

## lipo

查看MachO文件包含的架构
lipo -info [macho]

分析出指定架构
lipo –thin [arch] [macho] –output [outfile]

合并多种架构
lipo -create [macho1] [macho1] -output [outfile]

## otool

-f print the fat headers
-a print the archive header
-h print the mach header
-l print the load commands
-L print shared libraries used
-D print shared library id name
-t print the text section (disassemble with -v)
-p <routine name>  start dissassemble from routine name
-s <segname> <sectname> print contents of section
-d print the data section
-o print the Objective-C segment
-r print the relocation entries
-S print the table of contents of a library
-T print the table of contents of a dynamic shared library
-M print the module table of a dynamic shared library
-R print the reference table of a dynamic shared library
-I print the indirect symbol table
-H print the two-level hints table
-G print the data in code table
-v print verbosely (symbolically) when possible
-V print disassembled operands symbolically
-c print argument strings of a core file
-X print no leading addresses or headers
-m don't use archive(member) syntax
-B force Thumb disassembly (ARM objects only)
-q use llvm's disassembler (the default)
-Q use otool(1)'s disassembler
-mcpu=arg use `arg' as the cpu for disassembly
-j print opcode bytes
-P print the info plist section as strings
-C print linker optimization hints
--version print the version of /usr/bin/otool /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/share/man/man1/otool-classic.1
