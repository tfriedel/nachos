#include "syscall.h"
#include "string.h"
#include "stdbool.h"

/* Test Programm fuer Aufgabe 2. Testet vor allem Funktionen in syscall.h
   Es werden eine Reihe von Tests durchgefuehrt. Schlaegt ein Test fehl,
   bricht das Programm an dieser Stelle ab.
*/

#define TESTMESSAGE "NetworkTest"

void bestanden() {
    println(ConsoleOutput, "Test bestanden.");
}

void durchgefallen() {
    println(ConsoleOutput, "Test nicht bestanden.");
    Exit(-1);
}

void assertTrue(bool b) {
    if (b)
        bestanden();
    else
        durchgefallen();
}

int main(int argc, char **argv)
{
	char* testmessage = TESTMESSAGE;
    int a[5];
	int senderaddr;
	int senderbox;
	int size;
	char receiveBuffer[50];
    char* buffer = "abcd\0";
    int errorCode,i;
    OpenFileId f = ConsoleOutput;
    OpenFileId id, id2;
    ProcessID PID;

    // run this program in a different mode
    if (argc==2) {
        if (argv[1][0]=='1') { // für Test 1 (erzeugt SEGFAULT)
            a[1000] = 1;
            Exit(1);
        }
        else if (argv[1][0]=='2') {  // für Test 6 und 7
            Exit(2);
        }
    }

    // dieses Programm wird mit Parameter 1 gestartet. Daraufhin wird versucht
    // auf a[1000] schreibend zuzugreifen. Dies sollte einen SEGFAULT erzeugen.
    println(f, "Test 1: SEGFAULT Test");
    PID = Exec("testXtreme 1");
    errorCode = Join(PID);
    assertTrue(errorCode == ERR_SEGFAULT);

    println(f, "Test 2: Exec mit nicht existierender Datei");
    PID = Exec("unknown");
    assertTrue (PID == ERR_FILENOTFOUND);

    println(f, "Test 3: Exec mit nicht ausfuehrbarer Datei");
    PID = Exec("test.txt");
    assertTrue (PID == ERR_EXECUTION);

    println(f, "Test 4: Exec mit zu grossem Programm");
    PID = Exec("bigProgram");
    // grosses Programm kann nicht geladen werden, wenn virtual memory intalliert ist
    // assertTrue (PID == ERR_OUTOFMEM);
    // grosses Programm soll geladen werden, wenn virtual memory intalliert ist
    assertTrue (PID != ERR_OUTOFMEM);

    println(f, "Test 5: Exec mit leerem Programmnamen");
    PID = Exec("");
    assertTrue (PID == ERR_FILENOTFOUND);

    println(f, "Test 6: Join auf ungueltige PID");
    PID = Exec("testXtreme 2");
    errorCode = Join(PID+2);
    assertTrue (errorCode == ERR_UNKOWNPROCESS);
    errorCode = Join(-5);
    assertTrue (errorCode == ERR_UNKOWNPROCESS);

    println(f, "Test 7: Join auf Prozess");
    errorCode = Join(PID);
    DebugInt(errorCode);
    assertTrue (errorCode == 2);

    println(f, "Test 8: Create mit leerem Dateinamen");
    errorCode = Create("");
    assertTrue(errorCode == ERR_FILESYSTEM);

    println(f, "Test 9: Create mit zu langem Dateinamen");  // implementierungsspezifisch
    errorCode = Create("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    assertTrue(errorCode == ERR_FILESYSTEM);

    println(f, "Test 10: Open mit leerem Dateinamen");
    errorCode = Open("",RO);
    assertTrue(errorCode == ERR_FILESYSTEM);

    println(f, "Test 11: Open mit nicht existierendem Dateinamen");
    errorCode = Open("kjasdlkf",RO);
    assertTrue(errorCode == ERR_FILESYSTEM);

    println(f, "Test 12: 20 Dateien auf einmal oeffnen");  // implementierungsspezifisch
    for (i=0; i<20; i++)
        id = Open("test.txt",RO);
    assertTrue(id >= 0);

    println(f, "Test 13: 21 Dateien oeffnen geht nicht"); // implementierungsspezifisch
    id = Open("test.txt",RO);
    assertTrue(id == ERR_FILELIMIT);

    println(f, "Test 14: Nachdem alle 20 Dateien geschlossen sind, kann wieder eine geoeffnet werden"); // implementierungsspezifisch
    for (i=0; i<20; i++)
        Close(i);
    id = Open("test.txt",RO);
    assertTrue(id >= 0);

    println(f, "Test 15: Read mit ungueltiger FileID");
    assertTrue( (Read(id+1, buffer,5)==ERR_UNKNOWNFILE) &&
        (Read(-5, buffer,5)==ERR_UNKNOWNFILE) &&
        (Read(123, buffer,5)==ERR_UNKNOWNFILE));

    println(f, "Test 16: Read mit nicht-positiver Buffergroesse");
    assertTrue( (Read(id, buffer,-5)==ERR_BUFFERFAILURE) &&
        (Read(id, buffer,0)==ERR_BUFFERFAILURE) );

    println(f, "Test 17: Write mit ungueltiger FileID");
    assertTrue( (Write(id+1, buffer,5)==ERR_UNKNOWNFILE) &&
        (Write(-5, buffer,5)==ERR_UNKNOWNFILE) &&
        (Write(123, buffer,5)==ERR_UNKNOWNFILE));

    println(f, "Test 18: Write mit nicht-positiver Buffergroesse");
    errorCode = Create("test2.txt");
    id2 = Open("test2.txt",RW);
    assertTrue( (Write(id2, buffer,-5)==ERR_BUFFERFAILURE) &&
        (Write(id2, buffer,0)==ERR_BUFFERFAILURE) );

    println(f, "Test 19: Write: 5 Zeichen schreiben");
    assertTrue(Write(id2, buffer,5)==5);

    println(f, "Test 20: Read: 5 Zeichen lesen und mit geschriebenen Zeichen vergleichen");
    Close(id2);    id2 = Open("test2.txt",RO);
    buffer = "0000\0";
    assertTrue((Read(id2, buffer,5)==5)
        && (strcmp(buffer,"abcd\0")==0));

    println(f, "Test 21: Close auf ungueltige FileId");
    assertTrue( (Close(-5)==ERR_UNKNOWNFILE) &&
                (Close(123)==ERR_UNKNOWNFILE) &&
                (Close(15)==ERR_UNKNOWNFILE) );

    println(f, "Test 22: DebugInt, DebugHex, DebugString");
    DebugInt(42);
    DebugHex(42);
    DebugString("zweiundvierzig",0);
    // Netzwerk Tests
	println(f, "Test 23: Message mit nicht-positiver Buffergroesse senden");
    assertTrue(Send(1,1,2,testmessage,-1)==ERR_BUFFERFAILURE);

	println(f, "Test 24: Message mit Buffergroesse = 0 senden");
    assertTrue(Send(1,1,2,testmessage,0)==ERR_BUFFERFAILURE);

	println(f, "Test 25: Message mit nicht-positiver Localbox senden");
    assertTrue(Send(1,1,-1,testmessage,strlen(testmessage))==ERR_INVALIDBOX);

    println(f, "Test 26: Message mit nicht-vorhandener Localbox senden");
    assertTrue(Send(1,1,10,testmessage,strlen(testmessage))==ERR_INVALIDBOX);

	println(f, "Test 27: Message mit nicht-positiver Buffergroesse empfangen");
    assertTrue(Receive(1,testmessage,-1,&senderaddr,&senderbox,&size)==ERR_BUFFERFAILURE);

	println(f, "Test 28: Message mit Buffergroesse = 0 empfangen");
    assertTrue(Receive(1,testmessage,0,&senderaddr,&senderbox,&size)==ERR_BUFFERFAILURE);

	println(f, "Test 29: Message mit nicht-positiver Localbox empfangen");
    assertTrue(Receive(-1,testmessage,strlen(testmessage),&senderaddr,&senderbox,&size)==ERR_INVALIDBOX);

	println(f, "Test 30: Message mit nicht-vorhandener Localbox empfangen");
    assertTrue(Receive(10,testmessage,strlen(testmessage),&senderaddr,&senderbox,&size)==ERR_INVALIDBOX);

	println(f, "Test 31: Teste, ob Message vorhanden mit nicht-positiver Localbox");
    assertTrue(CanReceive(-1)==ERR_INVALIDBOX);

	println(f, "Test 32: Teste, ob Message vorhanden mit nicht-vorhandener Localbox");
    assertTrue(CanReceive(10)==ERR_INVALIDBOX);

    println(f, "Test 33: Uebertragung von Daten testen");
    println(f, "Teste, ob eine Message fuer mich vorhanden ist");
	assertTrue(CanReceive(1)==0);
	println(f, "Sende Message an mich");
	println(f, testmessage);
	assertTrue(Send(1,1,1,testmessage,strlen(testmessage))==0);
	println(f, "Teste, ob jetzt eine Message fuer mich vorhanden ist");
	assertTrue(CanReceive(1)>0);
	println(f, "Empfange meine Nachricht");
	assertTrue(Receive(1,receiveBuffer,sizeof(receiveBuffer),&senderaddr,&senderbox,&size)==0);
    println(f, receiveBuffer);
    println(f, "Teste, ob noch eine Message fuer mich vorhanden ist");
	assertTrue(CanReceive(1)==0);
// Ende Netzwerk Tests

    println(f, "Alle Tests bestanden");
}
