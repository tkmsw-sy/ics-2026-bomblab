
./bomb:     file format elf64-x86-64


Disassembly of section .init:

Disassembly of section .plt:

Disassembly of section .plt.sec:

Disassembly of section .text:

0000000000402290 <phase_03>:
  402290:	endbr64
  402294:	push   %rbp
  402295:	mov    %rsp,%rbp
  402298:	push   %r12
  40229a:	mov    %rsi,%r12
  40229d:	mov    $0x2,%esi
  4022a2:	push   %rbx
  4022a3:	mov    %rdi,%rbx
  4022a6:	sub    $0x10,%rsp
  4022aa:	call   402c60 <valid_u32_fields>
  4022af:	test   %al,%al
  4022b1:	jne    4022c0 <phase_03+0x30>
  4022b3:	xor    %eax,%eax
  4022b5:	add    $0x10,%rsp
  4022b9:	pop    %rbx
  4022ba:	pop    %r12
  4022bc:	pop    %rbp
  4022bd:	ret
  4022be:	xchg   %ax,%ax
  4022c0:	xor    %eax,%eax
  4022c2:	lea    -0x14(%rbp),%rcx
  4022c6:	lea    -0x18(%rbp),%rdx
  4022ca:	mov    $0x403186,%esi
  4022cf:	mov    %rbx,%rdi
  4022d2:	call   4011e0 <__isoc99_sscanf@plt>
  4022d7:	cmp    $0x2,%eax
  4022da:	jne    4022b3 <phase_03+0x23>
  4022dc:	mov    %r12d,%edi
  4022df:	xor    %eax,%eax
  4022e1:	and    $0x7,%edi
  4022e4:	cmp    %edi,-0x18(%rbp)
  4022e7:	jne    4022b5 <phase_03+0x25>
  4022e9:	mov    %r12,%rax
  4022ec:	mov    %r12,%rsi
  4022ef:	shr    $0x3,%rax
  4022f3:	shr    $0x20,%rsi
  4022f7:	xor    %eax,%esi
  4022f9:	call   402230 <p3_dispatch>
  4022fe:	cmp    %eax,-0x14(%rbp)
  402301:	sete   %al
  402304:	jmp    4022b5 <phase_03+0x25>

Disassembly of section .fini:
