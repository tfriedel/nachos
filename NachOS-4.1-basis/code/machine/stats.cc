// stats.h
//	Routines for managing statistics about Nachos performance.
//
// DO NOT CHANGE -- these stats are maintained by the machine emulation.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "debug.h"
#include "stats.h"
#include "main.h"
#include "utility.h"

//----------------------------------------------------------------------
// Statistics::Statistics
// 	Initialize performance metrics to zero, at system startup.
//----------------------------------------------------------------------

Statistics::Statistics()
{
    totalTicks = idleTicks = systemTicks = userTicks = 0;
    numDiskReads = numDiskWrites = 0;
    numConsoleCharsRead = numConsoleCharsWritten = 0;
    numPageFaults = numPacketsSent = numPacketsRecvd = 0;
}

//----------------------------------------------------------------------
// Statistics::Print
// 	Print performance metrics, when we've finished everything
//	at system shutdown.
//----------------------------------------------------------------------

void
Statistics::Print()
{
    cout << "number of physical memory pages: " << kernel->NumPhysPages
         << ", TLB size: "<< kernel->TLBSize << "\n";
   #ifdef USE_TLB
    cout << "Page swaps (read/write): " << kernel->pagefaults << ", TLB misses: " << kernel->tlbmisses << "\n";
   #endif

    cout << "Ticks: total " << totalTicks << ", idle " << idleTicks;
		cout << ", system " << systemTicks << ", user " << userTicks << endl;
    cout << "Milliseconds: " << getRealTicks() << endl;
    cout << "Disk I/O: reads " << numDiskReads;
		cout << ", writes " << numDiskWrites << "\n";
		cout << "Console I/O: reads " << numConsoleCharsRead;
    cout << ", writes " << numConsoleCharsWritten << "\n";
    cout << "Paging: faults " << numPageFaults << "\n";
    cout << "Network I/O: packets received " << numPacketsRecvd;
		cout << ", sent " << numPacketsSent << "\n";
}
