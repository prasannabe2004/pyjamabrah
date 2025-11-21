#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prasanna P M");
MODULE_DESCRIPTION("Hello Word");

static int my_module_init(void)
{
    printk("Hello world inserted\n");
    return 0;
}

static void my_module_exit(void)
{
    printk("Hello world exited\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
