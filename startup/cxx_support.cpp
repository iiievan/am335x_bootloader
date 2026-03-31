/* C++ runtime support functions for bare-metal */

extern "C" {

    /* Pure virtual function handler */
    void __cxa_pure_virtual(void) {
        while (1) {
            /* Handle pure virtual function call error */
        }
    }

    /* Guard variables for static initialization */
    int __cxa_guard_acquire(int* guard) {
        return !*(char*)(guard);
    }

    void __cxa_guard_release(int* guard) {
        *(char*)guard = 1;
    }

    void __cxa_guard_abort(int* guard) {
        (void)guard;  /* Suppress unused parameter warning */
        /* Nothing to do */
    }

    /* Atexit support (optional) */
    int __aeabi_atexit(void* object, void (*destructor)(void*), void* dso_handle) {
        (void)object;
        (void)destructor;
        (void)dso_handle;
        return 0; /* Not supported in bare-metal */
    }

    /* For proper static initialization */
    void* __dso_handle = &__dso_handle;

    /* Our own implementation of __libc_init_array */
    typedef void (*func_ptr)(void);

    extern func_ptr __preinit_array_start[];
    extern func_ptr __preinit_array_end[];
    extern func_ptr __init_array_start[];
    extern func_ptr __init_array_end[];

    void __libc_init_array(void) {
        /* Call preinit functions */
        for (func_ptr* func = __preinit_array_start; func < __preinit_array_end; func++) {
            (*func)();
        }

        /* Call init functions (constructors) */
        for (func_ptr* func = __init_array_start; func < __init_array_end; func++) {
            (*func)();
        }
    }

    /* Dummy _init function for compatibility */
    void _init(void) {
        /* Nothing to initialize here, we use init_array */
    }

} /* extern "C" */