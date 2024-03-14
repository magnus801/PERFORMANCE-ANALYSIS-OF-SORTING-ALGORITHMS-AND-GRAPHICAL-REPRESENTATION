#include <stdio.h>
#include <windows.h>
#include <stdint.h>

uint64_t get_cpu_frequency()
{
	LARGE_INTEGER frequency;
	if (!QueryPerformanceFrequency(&frequency))
	{
		fprintf(stderr, "Error querying performance frequency\n");
		return 0;
	}

	return (uint64_t)frequency.QuadPart;
}

static __inline__ uint64_t rdtsc(void)
{
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((uint64_t)hi << 32) | lo;
}