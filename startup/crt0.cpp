
namespace crt
{
  void init_ram  ();
  void init_ctors();
}

extern "C" int  main                   ();
extern "C" void __initial_stack_pointer();
extern "C" void __my_startup           () __attribute__((section(".startup"), used, noinline));

void __my_startup()
{
  // Setup the stack pointers and the stacks.
  // For additional information on stack setup,
  // see parts of Sitara Ware's "init.s".

  // Setup the stack pointer for the supervisor mode.
  asm volatile("msr cpsr_c, #0x13 | 0xC0");
  asm volatile("ldr r3, =__SVC_STACK_TOP");
  asm volatile("mov sp, r3");

  // Relocate the interrupt vector table.
  asm volatile("ldr r3, =__INTVECT_BASE_ADDRESS");
  asm volatile("mcr p15, 0, r3, c12, c0, 0");

  // Switch to Undefined mode and setup the relevant stack pointer.
  asm volatile("msr cpsr_c, #0x1B | 0xC0");
  asm volatile("ldr r3, =__UND_STACK_TOP");
  asm volatile("mov sp, r3");

  // Switch to Abort mode and setup the relevant stack pointer.
  asm volatile("msr cpsr_c, #0x17 | 0xC0");
  asm volatile("ldr r3, =__ABT_STACK_TOP");
  asm volatile("mov sp, r3");

  // Switch to IRQ mode and setup the relevant stack pointer.
  asm volatile("msr cpsr_c, #0x12 | 0xC0");
  asm volatile("ldr r3, =__IRQ_STACK_TOP");
  asm volatile("mov sp, r3");

  // Switch to FIQ mode and setup the relevant stack pointer.
  asm volatile("msr cpsr_c, #0x11 | 0xC0");
  asm volatile("ldr r3, =__FIQ_STACK_TOP");
  asm volatile("mov sp, r3");

  // Switch to System mode and setup the relevant stack pointer.
  asm volatile("msr cpsr_c, #0x1f | 0xC0");
  asm volatile("ldr r3, =__SYS_STACK_TOP");
  asm volatile("mov sp, r3");

  //mcal::cpu::init();

  // Enable Neon/VFP Co-Processor
  //asm volatile("mrc p15, #0, r1, c1, c0, #2");
  //asm volatile("orr r1, r1, #(0xf << 20)");
  //asm volatile("mcr p15, #0, r1, c1, c0, #2");
  //asm volatile("mov r1, #0");
  //asm volatile("mcr p15, #0, r1, c7, c5, #4");
  //asm volatile("mov r0,#0x40000000");
  //asm volatile("fmxr fpexc, r0");


  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  //mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  //mcal::wdg::secure::trigger();

  // Jump to main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    //mcal::wdg::secure::trigger();
  }
}
