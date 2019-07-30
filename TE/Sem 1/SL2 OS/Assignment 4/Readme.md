# Theory Required for this Practical
## MUTEX
### pthread_mutex_t lock_name;
     Defines a Mutext Lock Object which can be used to lock some region of code.
### pthread_mutex_lock(&lock);
     Locks the Region of code
### pthread_mutex_unlock(&lock);
     Unlocks the Region of code
### PTHREAD_MUTEX_INITIALIZER 
     Macro initializes the static mutex mutex.
## SEMAPHORE
     A semaphore is often used as a definitive mechanism for answering how many elements of a resource are in use -- e.g., an object that represents n worker threads might use a semaphore to count how many worker threads are available.
     
