// Copyright 2019
// Justin Baum
// Project 3
// CSCE311

#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/mm_types.h>

#ifndef __hello_world
#define __hello_world
asmlinkage long sys_helloworld(void) {
  printk("Hello World \n");
  return 0;
}

asmlinkage long sys_justin(unsigned long int addr) {
  struct task_struct* process;
  struct mm_struct* mm;
  struct vm_area_struct* mmap;
  long start;
  long end;
  long address;
  process = get_current();
  mm = (*process).mm; // Current mm
  mmap = (*mm).mmap; // To get to next

  printk("The address in question is: %p", addr);
  printk("Task Struct Address: %p", process);
  printk("MM address: %p", mm);
  while (mmap != NULL) {
    printk("Entering virtual memory map");
    printk("vm address: %p", mmap);
    address = (long)addr;
    start = mmap->vm_start;
    end = mmap->vm_end;
    if (address >= start && address <= end) {
      return (long)mmap->vm_flags; 
    }
    // Move mmap
    mmap = mmap->vm_next;
  }
  printk("vm address: %p", mmap);
  return -1;
}
#endif //__hello_world
