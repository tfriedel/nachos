/* errno.h
 *	Error codes for system calls.
 *
 *	Do not modify the contents of this file.
 *
 *	Try to use the most descriptive error number for the error.
 *      You may find it helpful to see what errors equivalent UNIX
 *      system calls return under various error conditions.
 *      For example the man page for the write system call "man 2 write"
 *      provides a list of different error number values for different
 *      conditions.
 *      NOTE: there are way more errors here than you should be supporting
 *            and many more error conditions listed in man pages than
 *            Nachos can possibly generate. The list here is to give you
 *            some ideas and to hopefully standardize on some error numbers.
 *
 *      ALSO NOTE: These definitions may not correspond to Solaris definitions
 *      (for copyright reasons these are taken from Linux).
 */

#ifndef ERRNO_H
#define ERRNO_H

#include "copyright.h"

// general error codes:
#define ERR_INVALIDID -998
#define ERR_IDLIMIT -4

// exec error codes:
// file does not exist
#define ERR_FILENOTFOUND -1
// file is not executable, maybe wrong parameters/format
#define ERR_EXECUTION    -2
// not enough memory
#define ERR_OUTOFMEM     -3
// too much processes (limited by maxProcesses)
#define ERR_PROCESSLIMIT ERR_IDLIMIT

// join error codes:
// (child) process terminated because of segmentation fault
#define ERR_SEGFAULT      -997
// unknown PID
#define ERR_UNKOWNPROCESS ERR_INVALIDID
// join not allowed because process is not a child
#define ERR_NOCHILD       -999

// filesystem error codes:
// device error/filesystem error
#define ERR_FILESYSTEM    -3
// too much open files (limited by maxOpenFiles)
#define ERR_FILELIMIT ERR_IDLIMIT
// file not open/invalid file id
#define ERR_UNKNOWNFILE ERR_INVALIDID

// Read and Write error codes:
// wrong buffer size
#define ERR_BUFFERFAILURE -2

// network error codes:
// invalid box id
#define ERR_INVALIDBOX ERR_INVALIDID


#endif // ERRNO_H
