#pragma once

#include <ctime>
#include <cstdlib>
#include <cstdint>

#define CPU_FREQ_MHZ (1994) // cat /proc/cpuinfo
#define DELAY_IN_NS (1000)  // Wook : Pcoomit latency in ns (now 1us)
#define PAGESIZE 4096

#define CACHE_LINE_SIZE 64

#define FLUSH 1

unsigned long write_latency_in_ns = 0; //Wook : write latency in ns
unsigned long pcommit_latency_in_ns = 0; //Wook : write latency in ns

unsigned long clflush_cnt = 0;


static inline void cpu_pause() {
    __asm__ volatile ("pause" ::: "memory");
}

static inline unsigned long read_tsc(void) {
    unsigned long var;
    unsigned int hi, lo;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    var = ((unsigned long long int) hi << 32) | lo;
    return var;
}

static inline void pm_wbarrier(unsigned long lat) {
    unsigned long etsc = read_tsc() + (unsigned long)(lat*CPU_FREQ_MHZ/1000);
    while (read_tsc() < etsc)
        cpu_pause();
}

void clear_cache() {
    int* dummy = new int[1024*1024*256];
    for (int i=100; i<1024*1024*256; i++) {
        dummy[i] = i;
    }

    for (int i=100;i<1024*1024*255;i++) {
        dummy[i] = dummy[i-rand()%100] + dummy[i+rand()%100];
    }

    delete[] dummy;
}

inline void mfence() {
    asm volatile("mfence":::"memory");
}

inline void sfence() {
    asm volatile("sfence":::"memory");
}

inline void clflush(char *data, int len) {
    volatile char *ptr = (char *)((unsigned long)data &~(CACHE_LINE_SIZE-1));
    mfence();
    for (; ptr<data+len; ptr+=CACHE_LINE_SIZE) {
        unsigned long etsc = read_tsc() + (unsigned long)(write_latency_in_ns*CPU_FREQ_MHZ/1000);
        asm volatile("clflush %0" : "+m" (*(volatile char *)ptr));
        while (read_tsc() < etsc)
            cpu_pause();
        clflush_cnt++;
    }
    mfence();
}

inline void pCommit() {
    unsigned long etsc = read_tsc() + (unsigned long)(pcommit_latency_in_ns*CPU_FREQ_MHZ/1000);
    while ( read_tsc() < etsc ) {
        cpu_pause();
    }
}