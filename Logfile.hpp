#ifndef LOGFILE_HPP
#define LOGFILE_HPP

// Includes
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Defines
#define MAX_BUFFER 4096           // Maximale Gr��e f�r den Buffer
#define L_FAIL false              // Funktion war erfolgreich
#define L_OK   true               // Funktion ist fehlgeschlagen

// Farben f�r den Text
enum FONTCOLORS
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    PURPLE
};

class Clogfile
{
    // Memberfunktionen
    public:

        Clogfile       ();
        ~Clogfile      ();
        void CreateLogfile  (void);
        void WriteTopic     (const char *Topic, int Size);
        void Textout        (std::string Text);
        void Textout        (int Color, std::string Text);
        void Textout        (int Color, bool List,std::string Text);
        void TextoutF       (const char *Text, ...);
        void TextoutF       (int Color, const char *Text, ...);
        void TextoutF       (int Color, bool List, const char *Text, ...);
        void FunctionResult (const char *Name, const char *ErrorMessage, bool Result);

        // Membervariablen
        private:
        FILE *m_logfile;

};
#endif
