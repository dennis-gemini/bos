#ifndef OS_MTASK_H
#define OS_MTASK_H

#include "os_sys.h"
#include "os_timer.h"
#include "os_memory.h"

/* task management */
#define MAX_TASK_NUM 10
struct task {
	int gdt_no; /* number of gdt table */
	int priority; /* priority for task runing */
	int flag;
	int pid; /* process identifier */
	struct TSS32 tss;
	char processname[32];
};

struct taskctl {
	int now;
	struct task tasks[MAX_TASK_NUM];
	struct task *taskring[MAX_TASK_NUM];
	int running;
};

extern struct taskctl _taskctl;

/** task control pointer */
extern struct taskctl *ptaskctl;

/** task state */
#define TASK_STOP 0
#define TASK_RUN  1
#define TASK_SEG  4
#define TASK_SLEEP 8

extern struct SEGMENT_DESCRIPTOR *gdt;

#define TASK_SEGNO(id) ((TASK_SEG + id) * 8)

struct TIMER *mt_timer;

void task_init(struct MEMMAN *memman);
int task_create(int func, struct MEMMAN *memman, const char *name);
void task_switch();
void task_run(struct task *t, int priority);

struct task *get_task(unsigned int task_id);
#endif /* OS_TASK_H */
