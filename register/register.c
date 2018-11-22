
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
#include <linux/vmalloc.h>

extern int (*SchedulerEntry)(void);

int test(void)
{
	int a=1024;
	a <<=2;
	return a;
}

static int hello_init(void)
{
	unsigned p;
	printk("before in register: %x\n",SchedulerEntry);

	p = __vmalloc(4096,GFP_KERNEL,PAGE_KERNEL_EXEC);
	memcpy(p,test,4096);
	SchedulerEntry = (int (*)(void))p;
	printk("after in register: %x\n",SchedulerEntry);
	//msleep(100000);
	return 0;
}


static void hello_exit(void)
{

	printk("end module\n=========================================================\n");

}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");



