# CSCE311 Project
# Justin Baum

## APIs

System call:  In the system call I use the Linux included library for `get_current` using `mm_types.h` for all the types I needed. With that I just access through the pointers for `mm`, `vma`, and so on.
Userspace:    In userspace I used a bare `syscall` C std library for invoking the system call and my system call number from the `syscall_tbl`.
