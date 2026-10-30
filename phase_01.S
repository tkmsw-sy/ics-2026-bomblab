
./bomb:     file format elf64-x86-64


Disassembly of section .init:

Disassembly of section .plt:

Disassembly of section .plt.sec:

Disassembly of section .text:

0000000000402090 <phase_01>:
  402090:	endbr64
  402094:	push   %rbp
  402095:	mov    %rsp,%rbp
  402098:	push   %r12
  40209a:	mov    %rsi,%r12
  40209d:	mov    $0x1,%esi
  4020a2:	push   %rbx
  4020a3:	mov    %rdi,%rbx
  4020a6:	sub    $0x10,%rsp
  4020aa:	call   402c60 <valid_u32_fields>
  4020af:	test   %al,%al
  4020b1:	jne    4020c0 <phase_01+0x30>
  4020b3:	add    $0x10,%rsp
  4020b7:	xor    %eax,%eax
  4020b9:	pop    %rbx
  4020ba:	pop    %r12
  4020bc:	pop    %rbp
  4020bd:	ret
  4020be:	xchg   %ax,%ax
  4020c0:	xor    %eax,%eax
  4020c2:	lea    -0x14(%rbp),%rdx
  4020c6:	mov    $0x403189,%esi
  4020cb:	mov    %rbx,%rdi
  4020ce:	call   4011e0 <__isoc99_sscanf@plt>
  4020d3:	cmp    $0x1,%eax
  4020d6:	jne    4020b3 <phase_01+0x23>
  4020d8:	mov    %r12,%rdi
  4020db:	call   402050 <p1_compute>
  4020e0:	cmp    %eax,-0x14(%rbp)
  4020e3:	sete   %al
  4020e6:	add    $0x10,%rsp
  4020ea:	pop    %rbx
  4020eb:	pop    %r12
  4020ed:	pop    %rbp
  4020ee:	ret

Disassembly of section .fini:
