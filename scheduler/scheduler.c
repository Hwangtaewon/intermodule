
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/desc.h>
#include <asm/pgtable.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/highmem.h>
#include <linux/preempt.h>
#include <asm/topology.h>
#include <linux/kthread.h>
#include <linux/kernel_stat.h>
#include <linux/percpu-defs.h>
#include <linux/smp.h>
#include <linux/delay.h>

int (*SchedulerEntry)(void);
EXPORT_SYMBOL(SchedulerEntry);


int thread1(void *data)
{
	int res=0;
	int (*fp)(void);
	printk("before in scheduler: %d\n",res);
	msleep(15000);
	fp = SchedulerEntry;
	res = fp();
	printk("after in scheduler: %d\n",res);
	return 0;
}

static int hello_init(void)
{
	struct task_struct *task1;

	task1 = kthread_create(thread1,NULL,"task1");
	wake_up_process(task1);

	return 0;
}


static void hello_exit(void)
{

	printk("end module\n=========================================================\n");

}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");



