#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>/*For jiffies*/
#include <asm/param.h> /*For HZ*/

#define BUFFER_SIZE 128
#define PROC_NAME "Seconds"

unsigned long int volatile f_jiffies,l_jiffies,now_jiffies;
const int hz=HZ;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count,loff_t *pos);

static struct file_operations proc_ops = {
   .owner = THIS_MODULE,
   .read = proc_read,
};

int proc_init(void)
{
    proc_create(PROC_NAME,0666,NULL,&proc_ops);
    f_jiffies = jiffies;
    printk(KERN_INFO "seconds loaded!\n");
    return 0;
}

void proc_exit(void)
{
    remove_proc_entry(PROC_NAME,NULL);
    l_jiffies = jiffies;
    printk(KERN_INFO "seconds unloaded!\n");
    printk(KERN_INFO "The running time is %ld s\n", ((l_jiffies-f_jiffies)/hz));
}


ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE];
    now_jiffies = jiffies;
    static int completed = 0;
    if (completed) {
      completed = 0;
    return 0;
}
    completed = 1;
    rv = sprintf(buffer,"The running time is %ld s\n", ((now_jiffies-f_jiffies)/hz));
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}
module_init(proc_init);
module_exit(proc_exit);
