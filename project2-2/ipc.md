In Linux we have an incredible number of IPC methods.

* Signals - They notify a process of a change, or events that occur outside of it. Some like seg faults, and sigints tell the process something bad has occurred.

* Pipes - These allow processes to communicate with streams. They are generally used for child-parent relationships. They are useful when you want to say have a process wait for HTTP requests, and another to process them.

* Shared Memory - These are the fastest way to share information. They are not very fault tolerance, and only useful if you can ensure that no two processes will work on top of eachothers work. They are prone to 2 processes trying to modify memory at the same time.

* Semaphores - Semaphores are incredibly useful to prevent the above problem. They ensure order and enforce resource access.

* Unix Domain Sockets - These are incredibly useful for having a way to communicate according to the server-client relationship. They allow a bidirectional pipe of information with a different kind of API then pipes.
