/* syscalls.h
 *  Nachos system call interface.  These are Nachos kernel operations
 *  that can be invoked from user programs, by trapping to the kernel
 *  via the "syscall" instruction.
 *
 *  This file is included by user programs and by the Nachos kernel.
 *
 * Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation
 * of liability and disclaimer of warranty provisions.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "copyright.h"
#include "errno.h"
/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */
#define SC_Halt         1
#define SC_Exit         2
#define SC_Exec         3
#define SC_Join         4
#define SC_Create       5
#define SC_Remove       6
#define SC_Open         7
#define SC_Read         8
#define SC_Write        9
#define SC_Seek         10
#define SC_Close        11
#define SC_Delete       12
#define SC_ThreadFork   13
#define SC_ThreadYield  14
#define SC_ExecV        15
#define SC_ThreadExit   16
#define SC_ThreadJoin   17
#define SC_getProcessID 18
#define SC_getThreadID  19
#define SC_Ipc          20
#define SC_Clock        21

#define SC_Send         22
#define SC_Receive      23
#define SC_CanReceive   24

#define SC_DebugInt     25
#define SC_DebugHex     26
#define SC_DebugString  27

#define SC_Add          42

#ifndef IN_ASM

/* The system call interface.  These are the operations the Nachos
 * kernel needs to support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the
 * procedure; an assembly language stub stuffs the system call code
 * into a register, and traps to the kernel.  The kernel procedures
 * are then invoked in the Nachos kernel, after appropriate error checking,
 * from the system call entry point in exception.cc.
 */

/* Stop Nachos, and print out performance stats */
void Halt();


/*
 * Add the two operants and return the result
 */

int Add(int op1, int op2);

/* Address space control operations: Exit, Exec, Execv, and Join */

/* This user program is done (status = 0 means exited normally). */
void Exit(int exitcode);

/* A unique identifier for an executing user program (address space) */
typedef int ProcessID;

/* A unique identifier for a thread within a task */
typedef int ThreadId;

/* Run the specified executable,  cmdLine contains the name of the executable + args*/
ProcessID Exec(char* cmdLine);

/* Only return once the user program "id" has finished.
 * Return the exit status.
 */
int Join(ProcessID id);


/* File system operations: Create, Remove, Open, Read, Write, Close
 * These functions are patterned after UNIX -- files represent
 * both files *and* hardware I/O devices.
 *
 * Note that the Nachos file system has a stub implementation, which
 * can be used to support these system calls if the regular Nachos
 * file system has not been implemented.
 */

/* A unique identifier for an open Nachos file. */
typedef int OpenFileId;

/* when an address space starts up, it has two open files, representing
 * keyboard input and display output (in UNIX terms, stdin and stdout).
 * Read and Write can be used directly on these, without first opening
 * the console device.
 */

#define ConsoleInput    0
#define ConsoleOutput   1

/* Create a Nachos file, with name "name" */
/* Note: Create does not open the file.   */
/* Return 1 on success, negative error code on failure */
int Create(char *name);

/* Remove a Nachos file, with name "name" */
int Remove(char *name);

/* Open the Nachos file "name", and return an "OpenFileId" that can
 * be used to read and write to the file. "mode" gives the requested
 * operation mode for this file.
 */
#define RO 1
#define RW 2
#define APPEND 3
OpenFileId Open(char *name, int mode);

/* Write "size" bytes from "buffer" to the open file.
 * Return the number of bytes actually read on success.
 * On failure, a negative error code is returned.
 */
int Write(OpenFileId id, char *buffer, int size);

/* Read "size" bytes from the open file into "buffer".
 * Return the number of bytes actually read -- if the open file isn't
 * long enough, or if it is an I/O device, and there aren't enough
 * characters to read, return whatever is available (for I/O devices,
 * you should always wait until you can return at least one character).
 */
int Read(OpenFileId id, char *buffer, int size);

/* Set the seek position of the open file "id"
 * to the byte "position".
 */
int Seek(OpenFileId id, int position);

/* Close the file, we're done reading and writing to it.
 * Return 1 on success, negative error code on failure
 */
int Close(OpenFileId id);


/*
 * int Send(int addr, int remotebox, int localbox, void *buffer, int size);
 *
 * Sende Daten an ein entferntes System
 * Rückgabewert  < 0 ==> Fehlercode
 *                 0 Alles OK
 * addr,box     Adresse und Postbox des Empfängers
 * buffer       Zeiger auf die Daten im Speicher des Userprogramms
 * size         Größe der Nahcricht in Byte
 *
 */

int Send(int addr, int remotebox, int localbox, void *buffer, int size);

/*
 * int Receive(int localbox, void *buffer, int maxsize, int *addr,
 *  int *remotebox, int *size);
 *
 * Empfange (Teil-)Nachrichten vom Network.
 * Rückgabe      0: wenn Nachricht vollständig empfangen
                >0: wieviele Bytes sind für diese Nachricht noch zu empfangen
                <0: Fehler
 * localbox     lokale Postbox, aus der gelesen werden soll
 * buffer       Zeiger auf Puffer, der Daten aufnehmen soll
 * maxsize      Größe des Puffers in Byte
 * addr         Adresse des Absenders (Rückgabewert!)
 * remotebox    Postbox des Absenders (Rückgabewert!)
 * size         verwendeter Bereich des Puffers in Byte (Rückgabewert!)
 */
int Receive(int localbox, void *buffer, int maxsize, int *addr,
        int *remotebox, int *size);

/*
 * int CanReceive(int localbox);
 *
 * Prüfe, ob eine Nachricht bereitsteht
 * Rückgabe      0: keine Nachricht
 *              >0: Größe der nächsten Nachricht, die abgeholt werden muss
 *              <0: Fehler
 */
int CanReceive(int localbox);

/*
 * Die folgenden drei Systemaufrufe dienen nur Debug-Zwecken. Da sie im
 * Betriebssystem nur ein DEBUG() auslösen, benötigen sie keinen Rückgabewert
 * Auch ein Speicherzugriffsfehler in DebugString sollte nur eine Warnmeldung
 * per DEBUG() auslösen, nicht jedoch das Programm terminieren.
 */

void DebugInt(long value); /* gebe einen Integerwert dezimal per DEBUG() aus */
void DebugHex(long value); /* gebe einen Integerwert hexadezimal per DEBUG() aus */
void DebugString(char* str, int size); /* gebe eine Zeichenfolge vorgegebener Lääng per DEBUG() aus */


#endif /* IN_ASM */

#endif /* SYSCALL_H */

