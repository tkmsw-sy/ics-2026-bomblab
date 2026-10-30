
./bomb:     file format elf64-x86-64


Disassembly of section .init:

Disassembly of section .plt:

Disassembly of section .plt.sec:

Disassembly of section .text:

0000000000402050 <p1_compute>:
  402050:	endbr64
  402054:	push   %rbp
  402055:	mov    %rdi,%rax
  402058:	mov    %rdi,%rdx
  40205b:	mov    %edi,%esi
  40205d:	shr    $0x20,%rax
  402061:	mov    %edi,%r8d
  402064:	shr    $0x10,%rdx
  402068:	mov    %eax,%edi
  40206a:	mov    %rsp,%rbp
  40206d:	call   402040 <p1_step2>
  402072:	mov    %rdx,%rsi
  402075:	mov    %r8d,%edi
  402078:	mov    %eax,%ecx
  40207a:	call   402020 <p1_step0>
  40207f:	mov    %ecx,%esi
  402081:	mov    %eax,%edi
  402083:	call   402030 <p1_step1>
  402088:	pop    %rbp
  402089:	ret

Disassembly of section .fini:
