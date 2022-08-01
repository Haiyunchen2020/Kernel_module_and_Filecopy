# Kernel_module_and_Filecopy

1. The code jiffies.c builds a kernel module that creates a /proc file named /proc/jiffies that reports the current value of jiffies when the /proc/jiffies file is read, such as with the command cat /proc/jiffies

2. The code seconds.c builds a kernel module that creates a proc file named /proc/seconds that reports the number of elapsed seconds since the kernel module was loaded. This involves using the value of jiffies as well as the HZ rate. The user enters the command cat/proc/seconds
