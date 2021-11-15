struct lock {
    int locked;
    struct queue q;
};

void lock_acquire(struct lock *l) {
    intr_disable();
    if (!l->locked) {
        l->locked = 1;
    } else {
        queue_add(&l->q, thread_current());
        thread_block();
    }
    intr_enable();
}

void lock_release(struct lock *l) {
    intr_disable();
    if (queue_empty(&l->q) {
        l->locked = 0;
    } else {
        thread_unblock(queue_remove(&l->q));
    }
    intr_enable();
}

//Link: https://web.stanford.edu/~ouster/cgi-bin/cs140-spring20/lecture.php?topic=lockImpl