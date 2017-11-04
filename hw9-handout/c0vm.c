#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/stacks.h"
#include "lib/c0vm.h"
#include "lib/c0vm_c0ffi.h"
#include "lib/c0vm_abort.h"

/* call stack frames */
typedef struct frame * frame;
struct frame {
  c0_value *V; /* local variables */
  stack S;     /* operand stack */
  ubyte *P;    /* function body */
  size_t pc;   /* return address */
};

/* TODO: implement execute function */
int execute(struct bc0_file *bc0) {
  
  /* Variables used for bytecode interpreter. You will need to initialize
     these appropriately. */
  
  /* callStack to hold frames when functions are called */
  stack callStack = NULL;
  (void) callStack;
  /* initial program is the "main" function, function 0 (which must exist) */
  struct function_info *main_fn = bc0->function_pool;
  /* array to hold local variables for function */
  c0_value *V = NULL;
  (void) V;
  /* stack for operands for computations */
  stack S;
  /* array of (unsigned) bytes that make up the program */
  ubyte *P;
  /* program counter that holds "address" of next bytecode to interpret from
     program P */
  size_t pc;
  
  while (true) {
    
#ifdef DEBUG
    fprintf(stderr,
            "Opcode %x -- Operand stack size: %zu -- Program counter: %zu\n",
            P[pc], stack_size(S), pc);
#endif
    
    switch (P[pc]) {
      
      /* GENERAL INSTRUCTIONS: Implement the following cases for each of the
         possible bytecodes.  Read the instructions in the assignment to see
         how far you should go before you test your code at each stage.  Do
         not try to write all of the code below at once!  Remember to update
         the program counter (pc) for each case, depending on the number of
         bytes needed for each bytecode operation.  See PROG_HINTS.txt for
         a few more hints.
         
         IMPORTANT NOTE: For each case, the case should end with a break
         statement to prevent the execution from continuing on into the
         next case.  See the POP case for an example.  To introduce new
         local variables in a case, use curly braces to create a new block.
         See the DUP case for an example.
         
         See C_IDIOMS.txt for further information on idioms you may find
         useful.
      */
      
    /* Additional stack operation: */

    case POP: {
      pc++;
      pop(S);
      break;
    }

    case DUP: {
      pc++;
      c0_value v = pop(S);
      push(S,v);
      push(S,v);
      break;
    }
      
    case SWAP: 

    /* Returning from a function */

    case RETURN:

    /* Arithmetic and Logical operations */

    case IADD:
      
    case ISUB:
      
    case IMUL:
      
    case IDIV:
      
    case IREM:
      
    case IAND:
      
    case IOR:
      
    case IXOR:
      
    case ISHL:
      
    case ISHR:
      
      
    /* Pushing small constants */

    case BIPUSH:

    /* Operations on local variables */

    case VLOAD:
      
    case VSTORE:
      
    case ACONST_NULL:
      
    case ILDC:
      
    case ALDC:
      
      
    /* Control flow operations */

    case NOP:
      
    case IF_CMPEQ:
      
    case IF_CMPNE:
      
    case IF_ICMPLT:
      
    case IF_ICMPGE:
      
    case IF_ICMPGT:
      
    case IF_ICMPLE:
      
    case GOTO:
      
    case ATHROW:

    case ASSERT:

    /* Function call operations: */

    case INVOKESTATIC:
      
    case INVOKENATIVE:
      

    /* Memory allocation operations: */

    case NEW:
      
    case NEWARRAY:
      
    case ARRAYLENGTH:


    /* Memory access operations: */

    case AADDF:
      
    case AADDS:
      
    case IMLOAD:
      
    case IMSTORE:
      
    case AMLOAD:
      
    case AMSTORE:
      
    case CMLOAD:
      
    case CMSTORE:
      
    default:
      fprintf(stderr, "invalid opcode: 0x%02x\n", P[pc]);
      abort();
    }
  }
  
  /* cannot get here from infinite loop */
  assert(false);
}

