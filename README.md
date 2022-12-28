DPBOXT is a terminal client for DPBOX .
License details can be found in file: doc/license

A Description of all files in the doc/ directory can be found in doc/FILES 

Compilation:
1. make dep
2. make

Important:
In the actual Linux-Kernels all interrupts are disabled during data-transfer
to or from an IDE/EIDE-harddisk. This will lead, even with a FIFO-16550, to
missing characters. Therefore the program 'hdparm' must be used to enable
the interrupts during data-transfers (parameter '-u 1' <device>).

TNT is Copyright (C) 1993-1997 by Mark Wahl, DL4YBG


--------------------------------------------------------
NEW: Linux AX25 Kernel supported! Read doc/ax25krnl.doc!
--------------------------------------------------------
