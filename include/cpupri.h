#ifndef __CPUPRI_H
#define __CPUPRI_H

#ifdef SCHED_RT

#include "cpumask.h"
#include "kernel_data_struct.h"

#define MAX_RT_PRIO							100
#define CPUPRI_NR_PRIORITIES		(MAX_RT_PRIO + 2)

#define CPUPRI_INVALID					-1
#define CPUPRI_IDLE							0
#define CPUPRI_NORMAL						1
/* values 2-101 are RT priorities 0-99 */

/* from /include/linux/sched.h */
#define MAX_PRIO								(MAX_RT_PRIO + 40)

struct cpupri_vec {
	int							count;		/* operations on this MUST be ATOMIC */
	cpumask_var_t		mask;
};

struct cpupri {
	struct cpupri_vec	pri_to_cpu[CPUPRI_NR_PRIORITIES];
	int								cpu_to_pri[NR_CPUS];
};

struct task_struct;
/* we have to export this for checker in practise.c */
int convert_prio(int prio);
int cpupri_find(struct cpupri *cp,
								struct task_struct *p, struct cpumask *lowest_mask);
void cpupri_set(struct cpupri *cp, int cpu, int pri);
int cpupri_init(struct cpupri *cp);
void cpupri_cleanup(struct cpupri *cp);

#endif /* SCHED_RT */

#endif	/* __CPUPRI_H */
