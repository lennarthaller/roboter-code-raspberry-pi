#ifndef __Clogfile
#define __Clogfile

// Includes

//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "Singleton.hpp"

// Defines

#define MAX_BUFFER 4096             // Maximale Größe für den Buffer

#define L_FAIL false                // Funktion war erfolgreich

#define L_OK   true                 // Funktion ist fehlgeschlagen

#define Log_File Clogfile::Get () // Makro zur einfachen Verwendung


// Farben für den Text

enum FONTCOLORS
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    PURPLE
};

class Clogfile : public TSingleton<Clogfile>
{
    // Memberfunktionen

    public:

        Clogfile       ();
        ~Clogfile      ();
        void CreateLogfile  (void);
        void WriteTopic     (const char *Topic, int Size);
        void Textout        (const char *Text);
        void Textout        (int Color, const char *Text);
        void Textout        (int Color, bool List, const char *Text);
        void TextoutF       (const char *Text, ...);
        void TextoutF       (int Color, const char *Text, ...);
        void TextoutF       (int Color, bool List, const char *Text, ...);
        void FunctionResult (const char *Name, const char *ErrorMessage, bool Result);

        // Membervariablen

        private:

        FILE *m_logfile;

};

#endif