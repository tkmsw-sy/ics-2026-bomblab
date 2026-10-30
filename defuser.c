#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    uint32_t c_low = (uint32_t)challenge;             // 取低32位
    uint32_t c_high = (uint32_t)(challenge >> 32);    // 取高32位
    uint32_t c_mid = (uint32_t)(challenge >> 16);     // 取中间的位（右移16位）

    // 计算第一步
    uint32_t step2_res = (c_low + 0x3ccb) ^ c_high;
    
    // 计算第二步
    uint32_t step0_res = 3 * (c_low - c_mid) + 0xdb47;
    
    // 计算最终结果
    uint32_t final_val = (step2_res ^ 0xa896) + 2 * step0_res;

    // 把结果存进数组
    values[0] = final_val;
    count = 1;
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
// 1. 计算第一个数
    values[0] = (uint32_t)(((challenge >> 37) & 0x3f) ^ 8);

    // 2. 循环计算后面的 5 个数
    for (int i = 1; i < 6; i++) {
        // 从 challenge 中提取 5 位，加上当前的索引 i
        uint32_t part = (uint32_t)(((challenge >> (16 + 2 * i)) & 0x1f) + i);
        // 异或 3 倍的前一个数
        values[i] = part ^ (3 * values[i - 1]);
    }

    // 3. 设置总共输入的整数个数为 6
    count = 6;

    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
 (void)challenge;
// 第一个数：challenge 的低 3 位，作为 switch 下标（and $0x7,%edi）
      uint32_t idx = (uint32_t)(challenge & 7U);
      // 传给 p3_dispatch 的参数：(challenge >> 3) 与 (challenge >> 32) 的低 32 位异或
      uint32_t x = (uint32_t)(challenge >> 3) ^ (uint32_t)(challenge >> 32);
      uint32_t result = 0;

      // 下标按 0x405820 处跳转表的实际内容对应，与 p3_case_N 的名字无关
      switch (idx) {
      case 0: result = x * 5U + 0x40da8U; break;          // p3_case_7
      case 1: result = x * 5U + 0x4c46eU; break;          // p3_case_3
      case 2: result = (x * 2U) ^ 0xd56dU; break;         // p3_case_4
      case 3: result = (x * 2U) ^ 0x163bU; break;         // p3_case_1
      case 4: result = (x ^ 0x3db8U) + (x >> 1); break;   // p3_case_0
      case 5: result = (x ^ 0x20a1U) + (x >> 1); break;   // p3_case_5
      case 6: result = x * 3U + 0x245dU; break;           // p3_case_2
      case 7: result = x * 5U + 0x64b9U; break;           // p3_case_6
      }

      values[0] = idx;
      values[1] = result;
      count = 2;    
    return write_answer(out, cap, values, count);
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;

    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
uint32_t target = (uint32_t)(challenge & 0x7fU);                        // and $0x7f,%edi
      uint32_t k = (uint32_t)(challenge >> 7) ^ (uint32_t)(challenge >> 32);  // shr $7 / shr $0x20 / xor
      uint32_t lo = 0U, hi = 0x7fU;
      uint32_t mids[32];
      int went_left[32];
      int depth = 0;
      uint32_t mid = lo + ((hi - lo) >> 1);
      while (mid != target && depth < 32) {
          mids[depth] = mid;
          went_left[depth] = target < mid;                                    // jb
          if (target < mid) {
              hi = mid - 1U;
          } else {
              lo = mid + 1U;
          }
          depth++;
          mid = lo + ((hi - lo) >> 1);
      }
      uint32_t r = (mid + 0xe7U) ^ k;                                         // 递归终点
      while (depth > 0) {
          depth--;
          uint32_t b = mids[depth] + k;                                       // lea (%rdi,%rcx,1),%ebx
          r = (r * 3U) ^ b ^ (went_left[depth] ? 0x12U : 0xaU);
      }
      values[0] = r;
      count = 1;
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
 static const uint32_t node_value[12] = {
          0x9621U, 0x1223U, 0x5c8aU, 0x22cfU, 0x5e39U, 0x62ceU,
          0x49f6U, 0xd81eU, 0x6cf3U, 0x423bU, 0x4b23U, 0x2431U};
      static const uint32_t node_tag[12] = {
          0x040U, 0x585U, 0xb70U, 0x748U, 0x92fU, 0xa32U,
          0x849U, 0x22cU, 0x477U, 0x13dU, 0x33eU, 0x61cU};
      static const int node_next[12] = {11, 4, 3, -1, 2, 0, 8, 10, 1, 5, 9, 6};
      // p5_heads（0x405b60）中的 8 个链表头，同样换算成结点下标
      static const int heads[8] = {7, 10, 9, 5, 0, 11, 6, 8};

      int node = heads[challenge & 7U];                                       // mov 0x405b60(,%rax,8),%rdx
      uint32_t steps = (uint32_t)(challenge >> 3) & 3U;                       // shr $3; and $3
      uint32_t acc = ((uint32_t)(challenge >> 6) ^ (uint32_t)(challenge >> 32)) ^ 0xf28aU;
      uint32_t tag = 0;
      for (uint32_t i = 0; i <= steps; i++) {
          if (i > 0) {
              node = node_next[node];                                         // mov 0x8(%rdx),%rdx
          }
          acc = acc * 3U + node_value[node];                                  // lea (%rax,%rax,2); add (%rdx)
          tag = node_tag[node];                                               // mov 0x4(%rdx),%esi
          acc ^= tag;
      }
      values[0] = acc;
      values[1] = tag;
      count = 2;
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;

    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
 static const int op_of[8] = {3, 1, 3, 2, 4, 0, 5, 5};
      uint32_t idx[2];
      idx[0] = (uint32_t)(challenge & 7U);                                    // and $0x7,%eax
      idx[1] = (uint32_t)(challenge >> 3) & 7U;                               // and $0x38,%ebx（字节偏移 = 下标 * 8）
      uint32_t x = (uint32_t)(challenge >> 6) ^ (uint32_t)(challenge >> 32);  // shr $6 / shr $0x20 / xor
      for (int step = 0; step < 2; step++) {
          uint32_t r = 0;
          switch (op_of[idx[step]]) {
          case 0: r = (x ^ 0xb6c5U) + (x << 7); break;                        // p6_op_0
          case 1: r = ((x << 5) | (x >> 27)) ^ 0x9d3eU; break;                // p6_op_1：rol 5
          case 2: r = ((x >> 3) ^ x) + 0x85ffU; break;                        // p6_op_2
          case 3: r = (x >> 5) | (x << 27); break;                            // p6_op_3：ror 5
          case 4: r = (x * 4U + 0x2718U) ^ (x * 5U); break;                   // p6_op_4
          case 5: r = (x + 0xe3bfU) ^ (x >> 5); break;                        // p6_op_5
          }
          x = (step == 0) ? (r ^ 0x1a57U) : r;                                // 两次调用之间 xor $0x1a57
      }
      values[0] = x + 0x5c99U;                                                // add $0x5c99,%eax
      count = 1;
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    uint32_t sel = (uint32_t)(context & 3U);                                     // and $0x3,%ecx
      uint32_t c = (uint32_t)(challenge >> 32) ^ (uint32_t)challenge;              // esi
      uint32_t k = (uint32_t)(context >> 32) ^ (uint32_t)context;                  // r8d
      uint32_t salt = (sel * 0xe8e7U) ^ (uint32_t)(context >> 16);                 // r9d
      uint32_t m = c ^ k;
      uint32_t mix = (((m << 1) | (m >> 31)) + 0xe8e7U) ^ 0x138cU;                 // secret_mix
      uint32_t second = mix ^ salt;
      uint32_t third = second ^ (k + sel + 0x138cU + (c >> 1));
      int size = snprintf(out, cap, "%s%s%" PRIu32 " %" PRIu32 " %" PRIu32,
                          "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "OPEN", sel, second, third);
      return size < 0 || (size_t)size >= cap;
}
