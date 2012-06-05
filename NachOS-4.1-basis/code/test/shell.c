#include "syscall.h"
#include "stdbool.h"
#include "string.h"
#include "errno.h"

int
main()
{
    char buffer[60];
    bool backgroundProcess = false;    
    ProcessID newProc;
    int i;
    int exitcode;


    while( 1 )
    {
    	print(ConsoleOutput, "--");
    
    	i = readLine(buffer, 60);
    
    	if ((i > 0) && (buffer[i-1] == '&')) {
                backgroundProcess = true;
                buffer[--i] = '\0';
            }
    
    	if( i > 0 ) {
    		newProc = Exec(buffer);
    		if (backgroundProcess) {
                    DebugString("Process started in the background.",0);
                    backgroundProcess = false;
                }
            else {
                exitcode = Join(newProc);
                if (exitcode == ERR_UNKNOWNFILE)
                    println(ConsoleOutput, "Executable not found.");
                else if (exitcode != 0) {
                    print(ConsoleOutput, "\nExitcode: ");
                    printInt(ConsoleOutput, exitcode);
                    println(ConsoleOutput, "");
                }
            }
    	}
    }
}

