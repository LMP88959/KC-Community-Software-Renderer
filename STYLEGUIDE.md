# KC-Community-Software-Renderer Style Guide  
================================================================  


Formatting
------

- 4 space indent, avoid tabs.  
- Pointer asterisk is attached to the variable name not the type (e.g: `char *p` not `char* p`)  
- Never use empty parentheses for functions that take no parameters. (e.g: `func(void)` not `func()`)  
- Functions that return a success or failure should look like this:  
```c
/* note that the extern/static modifier and function name is irrelevant to this example */
extern int
PREFIX_check_something(void)
{
    int success;

    /* do the check */
    success = something() ? 1 : 0;

    return success; /* important: 0 means failure, 1 means success. */
}
```
- Avoid using enums, use #defines instead so you can see concrete values for constants.
- Always have braces around if-statement and loop bodies, regardless of if they're one liners.  
- Use post-incrementing when just incrementing a value, e.g x++ instead of ++x.  
  - If the return value is so important that you need to do pre-incrementing, consider redesigning the code.  
- Either use `stdint.h` type names or the regular builtin ones like `short`, `int`, `long`.  
- No forward declaration of static functions in a file. Reorder the functions as needed so that no forward declarations are required.  
- Try to adhere to a limit of 80 characters per line. Feel free to spread argument lists over a few lines to avoid crossing the limit.  
- snake_case names. See the example for when to use upper and lower case.  
- avoid using `const` unless you really believe it helps clarify the behavior of a variable.  
- try to use multi-line comments as much as possible, // comments are permitted if a comment is only one line long.  
- if you want to comment out a chunk of code, instead of using a multi-line comment, wrap it in #if 0 like so:  
```c
#if 0

/* code */

#endif
```


Formatting/Style Example
------


example.h  
```c
/*****************************************************************************/
/*
 * PROJECT NAME
 * 
 *   by AUTHOR(s)
 *   
 * LICENSE
 */
/*****************************************************************************/

/* use #pragma once if you want, I prefer this method though, even though it's error prone */
#ifndef EXAMPLE_H
#define EXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define PREFIX_macro(x, y) (((x) - (y)) * 100)

/* align values of related sequences of #defines in a column */
#define PREFIX_DEFINE_NAME            8
#define PREFIX_OTHER_NAME             10
#define PREFIX_SOME_MUCH_LONGER_NAME  12
#define PREFIX_DELTA                  14

/* I personally don't like typedeffing struct names
 * but I know it's cumbersome to type struct everywhere.
 * As a result, if you want, you can typedef struct names.
 */
extern struct PREFIX_MUL { /* note, unnamed structs are fine */
    int data;
} PREFIX_multiplier;

extern int PREFIX_func_name(int *arr, int size);

#ifdef __cplusplus
}
#endif

#endif
```

example.c  
```c
/*****************************************************************************/
/*
 * PROJECT NAME
 * 
 *   by AUTHOR(s)
 *   
 * LICENSE
 */
/*****************************************************************************/

/* the first include in every C file is its matching header,
 * unless the C file just contains the implementation of something
 */
#include "example.h"

/*  example.c
 * 
 * General description of what functionality the code in this C file provides.
 * 
 */

/* other includes */
#include <stdlib.h>

#define IMPORTANCE 2 /* note no prefix on local macro */

struct PREFIX_MUL PREFIX_multiplier = { PREFIX_macro(20, 10) }; /* note prefix on global variables */
static int assumed_importance = IMPORTANCE; /* note no prefix on static variable */

/* note no prefix on static function */
static int
get_arr_val(int *arr, int i)
{
    return (arr[i] / assumed_importance * PREFIX_multiplier.data) & 0xff;
}

/* extern functions must have the extern keyword for both definition and declaration */
extern int
PREFIX_func_name(int *arr, int size)
{
    /* try to adhere to C89 separation of variable declaration to the top of block scope.
     * This is only a suggestion though, not a requirement.
     */
    int i, sum;

    sum = 0;
    /* early return for simple conditions. AVOID nesting if statements for trivial things like this. */
    if (size < 1) {
        return 0; 
    }

    for (i = 0; i < size; i++) {
        sum += get_arr_val(arr, i);
    }
    return sum / size;
}
```
