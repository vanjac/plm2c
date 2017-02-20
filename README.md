# PLM2C

Converts [PL/M](https://en.wikipedia.org/wiki/PL%2FM) code to C. This was not written by me, I downloaded it from [this page](http://www.cpm.z80.de/source.html), and I have been cleaning it up slightly.

## Original contents of the README file (formatted)

This is a PL/M to C converter.  It will take most PL/M code and do a nice
job of converting it to C.  It tries to be intelligent about leaving formatting
and comments intact.  This version supports PL/M-286.  It is something I wrote
about a year ago to convert several meg of source code, and it did a 99.5%
conversion.  I was later handed some source code that it crashed on, and I
extended it to support that code too.

Please keep in mind that this may well not work for your code.  It has
been tested only on a few sets of code, each following its own set of coding
standards.  Also, don't expect a lot of support from me, as my interest in
PL/M is next to none.  I no longer work for the employer for whom I wrote
this converter, but they have given me permission to own and post the sources.
I will, time permitting, collect bug fixes and post patches to the software.
Please mail fixes directly to me, as I may miss any posting of them.  If
anyone is interested in taking over maintenance of this code, please let me
know!

The source code compiles under Unix.  I've compiled it on a Sun-4, a VAX
running Ultrix, and a VAX running Mt. Xinu.  At one time I had a version that
ran under MSDOS, but I can't guarantee it will now.  I've included a makefile
for use with Turbo-C.  You need to define IBMPC to compile it.  What it could
really use is tuning for a large memory model, as in it's present state, it
can only handle small source files.  It could also benefit from a good man
page.

The converter expects source code to be in "proper" format (i.e. proper
use of EXTERNAL declarations, and following of the Intel PL/M grammar as the
converter knows it.)  It has some moderate error-recovery, but may well dump
core if it expects one thing and gets another.

I've included a garbage file test.plm; typeing "plm2c test.plm" should
result in a test.c file that is identical to the provided test.c.out.

See the file CAVEATS.DOC for compatibility issues.

Hope you find it useful!

Robert Ankeney

April 9, 1991

...!tektronix!bob@reed.bitnet

## Original contents of the CAVEATS.DOC file (formatted)

Some notes about the PL/M to C converter:

With case conversion enabled by the "ifdef" in main.c, all upper case 
characters in an identifier are converted to lower case, and all lower case 
characters are converted to upper case except for identifiers declared 
LITERALLY, in which case the identifier is not case converted.

Dollar signs used in identifiers are discarded.

The use of the AND, OR and NOT operators are converted to &&, ||, and !
operators respectively.  This should work, but conversion to &, |, and ~
may be desirable in many cases.  There is no clear way to distinguish which
conversion to use, thus the previous conversions were chosen.  A #define
in tokens.h allows either convention to be chosen.  A more intelligent
expression parser could do a better job of determining use of these operators.

Labels are limited in scope to that defined in C.  That is, use of labels is
limited to the current function.  PL/M allows external labels.

The dot operator is treated the same as the @ operator (converted to a &
reference).

Constant lists of the form: `@('string', 0)` are converted to: `"string"`

Constant lists of the form: `@('string')` are converted to: `'s', 't', 'r', 'i', 'n', 'g'`

BYTE strings of the form: `'string'` are converted to: `'s', 't', 'r', 'i', 'n', 'g'`

ADDRESSes and SELECTORs are not supported.

Variables declared AT in one module and EXTERNAL in another will produce
incorrect results, as the EXTERNAL declared variable will not be treated
as a pointer.  For example, in module A:

<pre>
     PL/M code:                           C code:
     ---------------------------------    ----------------------------------
     DECLARE MEMVAR BYTE AT(8000H);       BYTE *memvar = (BYTE *) 0x8000;
     MEMVAR = 14H;                        (*memvar) = 0x14;
</pre>

And in module B:

<pre>
     PL/M code:                           C code:
     ---------------------------------    ----------------------------------
     DECLARE MEMVAR BYTE EXTERNAL;        BYTE memvar;
     MEMVAR = 14H;                        memvar = 0x14;
</pre>

To avoid this problem, list each AT variable used on a single line in a file
called "at_decl.cvt".

Variable declarations within a procedure with the PUBLIC attribute *probably*
should be placed prior to the procedure definition. Currently, the PUBLIC
attribute is ignored.

Variable declarations of type POINTER are treated as type void.
BASED variables are treated as a pointer to the based variable.
For example, for the following declarations, the associated C code is
generated:

<pre>
     PL/M code:                           C code:
     ---------------------------------    ----------------------------------
     DECLARE I BYTE;                      BYTE i;
     DECLARE ITEM_PTR POINTER;            void *item_ptr;
     DECLARE ITEM BASED ITEM_PTR BYTE;    BYTE **item = (BYTE **) &item_ptr;
     ITEM_PTR = @I;                       item_ptr = &i;
     ITEM = 77H;                          (**item) = 0x77;
</pre>

Care should be taken in the use of LITERALLY declared variables.  Such
declarations are converted to a #define directive.  With the cvt.h flag
PARSE_LITERALS defined, the converter attempts to parse the contents of
all LITERALLY declared variables as the definition for the #define
directive.  With PARSE_LITERALS undefined, no parsing takes place.  Thus,
for the declaration:
	`DECLARE MAX_COUNT LITERALLY '55H';`

the code generated with PARSE_LITERALS defined is:
	`#define MAX_COUNT 0x55`

and the code generated with PARSE_LITERALS undefined is:
	`#define MAX_COUNT 55H`


Control directives within comments are ignored.

The procedure attribute REENTRANT is ignored.  Technically, all PL/M variables
are static and could be declared as such in all but REENTRANT procedures.
This was not done, as it was deemed improbable that any problems would result.
The user should keep this fact in mind though.  Especially in cases where the
C compiler warns about using a variable before it has been defined.

In most cases, white space (spaces, tabs, returns, line-feeds and comments)
are retained in their appropriate place.  In obscure instances, white space
may be discarded for the sake of simpler code.  For example, white space in
some portions of a DECLARE statement is discarded, since the structure of
a DECLARE statement is drastically converted.

Array subscripts and function calls appear to be ambiguous.  The converter
keeps a symbol table of DECLARATIONS to try to correctly distinguish one from
the other.


