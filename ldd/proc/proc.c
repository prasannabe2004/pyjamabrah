#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prasanna P M");
MODULE_DESCRIPTION("Hello Word");

char msg[100] = "";

ssize_t my_read(struct file *fp, char __user *user_buffer, size_t count, loff_t *offset)
{
    printk("my read\n");
    size_t len = sizeof(msg);

    if (*offset >= len)
        return 0;

    if (copy_to_user(user_buffer, msg, len))
        return -EFAULT;

    *offset += count;

    return count;
}

ssize_t my_write(struct file *fp, const char __user *user_buffer, size_t count, loff_t *offset)
{
    printk("my write\n");
    if (count > sizeof(msg) - 1)
        count = sizeof(msg) - 1;
    if (copy_from_user(msg, user_buffer, count))
        return -EFAULT;
    msg[count] = '\0';
    printk("Received from user: %s\n", msg);
    return count;
}

static struct proc_dir_entry *custom_proc_node;

static struct proc_ops driver_proc_ops = {
    .proc_read = my_read,
    .proc_write = my_write,
};

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
