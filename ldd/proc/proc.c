#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prasanna P M");
MODULE_DESCRIPTION("Hello Word");

static struct proc_dir_entry *custom_proc_node;
struct proc_ops driver_proc_ops = {};

static int my_module_init(void)
{
    printk("Hello world inserted\n");
    custom_proc_node = proc_create("my_driver",
                                   0,
                                   NULL,
                                   &driver_proc_ops);
    return 0;
}

static void my_module_exit(void)
{
    printk("Hello world exited\n");
    proc_remove(custom_proc_node);
}

module_init(my_module_init);
module_exit(my_module_exit);
