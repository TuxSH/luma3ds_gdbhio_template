#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <unistd.h>
#include "gdbhiodev.h"

int main(int argc, char* argv[])
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Hello, world!\n");
    printf("gdbHioDevInit %d\n", gdbHioDevInit());

    // Main loop
    while (aptMainLoop())
    {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        // Your code goes here
        u32 kDown = hidKeysDown();
        if (kDown & KEY_Y) {
            FILE *f = fopen("gdbhio:test.txt", "w+");
            if (f == NULL) {
                perror("fopen");
                continue;
            }
            fprintf(f, "Hello world!");
            fclose(f);

            gdbHioDevRedirectStdStreams(true, true, true);
            printf("Hello from 3DS!\n");

            int r = 0;
            while (r != EOF) {
                int v = -1;
                printf("Enter a number: ");
                fflush(stdout);
                r = scanf("%d", &v);
                printf("You entered: %d\n", v);
            }
        }
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    gdbHioDevExit();
    gfxExit();
    return 0;
}
