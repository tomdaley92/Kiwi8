/*
Author: Thomas Daley
Date: September 8, 2016
*/

#include "../../Core/Chip8.h"
#include "resource.h"

#include <SDL_image.h>
#include <windows.h>
#include <Commdlg.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    char cwd[MAX_PATH];
    
    char *rom;
    int fullscreen = 0;
    int R = 0;
    int G = 255;
    int B = 200;

    if (argc < 2) {

        GetCurrentDirectory(MAX_PATH, cwd);

        int result = MessageBox (NULL , "Click OK to select a ROM file.\n\n"
                            "Alternatively, you may launch Chip8 with the command line.\n\n"
                            "Usage: Chip8 PATH_TO_ROM [-F] [R G B]\n"
                            "       -F\t\tLaunch in fullscreen\n"
                            "       R G B\t\tRender color in RGB format, 3 numbers from 0-255\n\n\n\n"
                            "Enjoy!\n\n-Thomas Daley", "Chip8 v1.01" , MB_OKCANCEL);
        if (result == IDCANCEL) {
            return 0;
        }

        OPENFILENAME ofn;

        char szFile[MAX_PATH];

        // open a file name
        ZeroMemory( &ofn , sizeof( ofn));
        ofn.lStructSize = sizeof ( ofn );
        ofn.hwndOwner = NULL  ;
        ofn.lpstrFile = szFile ;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof( szFile );
        ofn.lpstrFilter = "Chip8\0*.ch8\0All\0*.*\0";
        ofn.nFilterIndex =1;
        ofn.lpstrFileTitle = NULL ;
        ofn.nMaxFileTitle = 0 ;
        ofn.lpstrInitialDir=NULL ;
        ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;

        if (!GetOpenFileName( &ofn)) {
            return 0;
        }

        /* Change current working directory back to location of executable */
        SetCurrentDirectory(cwd);

        rom = szFile;
        
    } else {
        rom = argv[1];
    }

    if (argc >= 3 && (strcmp(argv[2], "-F") == 0)) {
        fullscreen = 1;
    }

    if (argc > 2 + fullscreen) {
        R = atoi(argv[2 + fullscreen]);
    }

    if (argc > 3 + fullscreen) {
        G = atoi(argv[3 + fullscreen]);
    }
    

    if (argc > 4 + fullscreen) {
        B = atoi(argv[4 + fullscreen]);
    }
    
    Chip8 chip = Chip8();

    if (chip.Initialize(fullscreen, R, G, B)) {
        return 1;
    }


    /*  SDL2 provides no way of loading the Windows ICON 
        resource that is embedded in the executable at 
        compile time. The code below loads the window 
        icon from a file during runtime, but it requires 
        an SDL2 extension library - SDL_image 2.0  */
    SDL_Surface *image;
    image = IMG_Load("chip8.ico");
    if (image == NULL) {
        fprintf(stderr, "Error loading window icon...\n");
    }
    SDL_SetWindowIcon(chip.renderer.window, image);
    
    if (chip.Load(rom)) {
        return 1;
    }
    
    chip.Run();
    fprintf(stderr, "Main thread terminated.\n");
    return 0;
}
