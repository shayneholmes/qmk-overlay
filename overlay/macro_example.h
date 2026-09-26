/**
 * Use this file privately by copying it to macro.h and changing it there.
 * It will get ignored by git.
 */

#define MACRO_DEF_Q     SEND_STRING_DELAY("Example!\n", 15); return

#define MACRO_DEF_Q_S   SEND_STRING_DELAY("Example!\n", 45); return

#define MACRO_DEF_L     SEND_STRING_DELAY("Another example... ", 15); return

#define MACRO_DEF_K     SEND_STRING_DELAY("And a third", 15); return

#define MACRO_DEF_D     SEND_STRING_DELAY("One more...", 15); return

#define MACRO_DEF_P     SEND_STRING_DELAY("P", 15); return
