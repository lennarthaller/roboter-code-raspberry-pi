#include "Logfile.hpp"

// Konstruktor
Clogfile::Clogfile ()
{

}

// Destruktor
//Gibt Ende-Meldung aus und schlie� das Logfile
Clogfile::~Clogfile ()
{
    // logfile-Ende schreiben und Datei schlie�en
    //Textout ("<br><br>===End of logfile===</font></body></html>");
    fclose (m_logfile);
}

//Createlogfile
//logfile erstellen und Kopf schreiben
void Clogfile::CreateLogfile ()
{
    // logfile leeren und Kopf schreiben
    m_logfile = fopen ("Logfile.html", "w");
    Textout ("<html><head><title>Logfile</title></head>");
    Textout ("<body><font face='courier new'>");
    //fopen_s(&m_logfile, LogName, "a");

    // logfile schlie�en und mit append wieder �ffnen
    fclose (m_logfile);
     m_logfile = fopen ("Logfile.html", "a");
}

//WriteTopic
//�berschrift erzeugen
void Clogfile::WriteTopic (const char *Topic, int Size)
{
    // �berschrift schreiben und flushen
    Textout ("<table cellspacing='0' cellpadding='0' width='100%%' ");
    Textout ("bgcolor='#DFDFE5'>\n<tr>\n<td>\n<font face='arial' ");
    TextoutF ("size='+%i'>\n", Size);
    Textout (Topic);
    Textout ("</font>\n</td>\n</tr>\n</table>\n<br>");
    fflush (m_logfile);
}

// Textout
//Text ins logfile schreiben (schwarz)
void Clogfile::Textout (const char *Text)
{
    // Text schreiben und flushen
    fprintf (m_logfile, Text);
    fflush (m_logfile);
}

// Textout
//Text ins logfile schreiben (farbig)
void Clogfile::Textout (int Color, const char *Text)
{
    Textout (Color, false, Text);
}

// Textout
//Text ins logfile schreiben (farbig, Liste)
void Clogfile::Textout (int Color, bool List, const char *Text)
{
    //Listen-Tag schreiben
    if (List == true)
    Textout ("<li>");

    // Farbtag schreiben
    switch (Color)
    {
        case BLACK:
            Textout ("<font color=black>");  break;
        case RED:
            Textout ("<font color=red>");    break;
        case GREEN:
            Textout ("<font color=green>");  break;
        case BLUE:
            Textout ("<font color=blue>");   break;
        case PURPLE:
            Textout ("<font color=purple>"); break;
    };

    //Text schreiben
    Textout (Text);
    Textout ("</font>");

    if (List == false)
        Textout ("<br>");
    else
        Textout ("</li>");
}

// TextoutF
//formatierten Text ins logfile schreiben (schwarz)
void Clogfile::TextoutF (const char *Text, ...)
{
    char *buffer = new char[MAX_BUFFER];    // char-Buffer

    va_list pArgList;                       // Liste der �bergebenen Argumente


    // String aus den Argumenten erstellen
    va_start (pArgList, Text);
    vsprintf (buffer, Text, pArgList);
    va_end (pArgList);

    // Erzeugten String schreiben
    Textout (buffer);
}

// TextoutF
//formatierten Text ins Logfile schreiben (farbig)
void Clogfile::TextoutF (int Color, const char *Text, ...)
{
    char *buffer = new char[MAX_BUFFER];    // char-Buffer

    va_list pArgList;                       // Liste der �bergebenen Argumente


    // String aus den Argumenten erstellen
    va_start (pArgList, Text);
    vsprintf (buffer, Text, pArgList);
    va_end (pArgList);

    // Erzeugten String schreiben
    Textout (Color, buffer);
}

// TextoutF
// formatierten Text ins logfile schreiben (farbig, Liste)
void Clogfile::TextoutF (int Color, bool List,const char *Text, ...)
{
    char *buffer = new char[MAX_BUFFER];  // char-Buffer

    va_list pArgList;          // Liste der �bergebenen Argumente


    // String aus den Argumenten erstellen
    va_start (pArgList, Text);
    vsprintf (buffer, Text, pArgList);
    va_end (pArgList);

    // Erzeugten String schreiben
    Textout (Color, List, buffer);
}

// FunctionResult
//OK oder ERROR f�r Funktionsaufruf ausgeben
void Clogfile::FunctionResult (const char *Name, const char *ErrorMessage, bool Result)
{
    if (L_OK == Result)
    {
        Textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
        Textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
        TextoutF("'#FFFFFF' width='25%%'>%s</TD>", Name);
        Textout("<td bgcolor='#FFFFFF' width='5%%'><font color =");
        Textout("'green'>OK</FONT></TD><td bgcolor='#FFFFFF' ");
        TextoutF("'#FFFFFF' width='45%%'>%s</TD>", ErrorMessage);
    }
    else
    {
        Textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
        Textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
        TextoutF("'#FFFFFF' width='35%%'>%s</TD>", Name);
        Textout("<td bgcolor='#FFFFFF' width='5%%'><font color =");
        Textout("'red'>ERROR</FONT></TD><td bgcolor='#FFFFFF' ");
        TextoutF("'#FFFFFF' width='35%%'>%s</TD>", ErrorMessage);
    }
}