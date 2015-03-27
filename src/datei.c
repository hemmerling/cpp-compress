/**
 *  @package   compress
 *  @file      datei.c
 *  @brief     Kompressionsverfahren "Lauflaengenkomprimierung" - 
 *             Komprimierung der in einer Binaerdatei gespeicherten Daten
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "Microsoft Visual C++",
 *             Entwicklungswerkzeug 
 *             "Microsoft Visual Studio Express 2013 for Windows Desktop"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  datei.c - Kompressionsverfahren "Lauflaengenkomprimierung" - 
 *            Komprimierung der in einer Binaerdatei gespeicherten Daten
 *            Labor fuer Datenverarbeitung, FH Hannover,
 *            Versuch 12 "Datenkompression"   
 *  
 *  Copyright 2000-2015 Rolf Hemmerling
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *  either express or implied.
 *  See the License for the specific language governing permissions
 *  and limitations under the License.
 *
 *  Last update: 2000-03-17
 */

#ifdef _MSC_VER
/**
*  Error	1	error C4996 : 'fopen' :
*  This function or variable may be unsafe.
*  Consider using fopen_s instead.
*  To disable deprecation, use _CRT_SECURE_NO_WARNINGS
*/
#define _CRT_SECURE_NO_WARNINGS 1
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Include-Dateien                                                 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "compress.h"
#include "datei.h"

/*******************************************************************/
/* Modulglobale Variablen                                          */
/*******************************************************************/

/**
 *  @var      MV_datenfeld
 *  @brief    Feld fuer Orginaldaten  
 */
DATENTYP char MV_datenfeld[IN_DATEILAENGE];

/**
 *  @var      MV_lauflaengenfeld
 *  @brief    Feld fuer Lauflaengenkomprimierte Daten 
 */
DATENTYP char MV_lauflaengenfeld[OUT_DATEILAENGE];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Funktions-Deklarationen                                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int MP_datei_oeffnen(char* IV_dateiname)
/*******************************************************************/
/* Datei oeffnen                                                   */
/*******************************************************************/
{
  FILE* PV_fp;
  size_t PV_rueckgabezeiger;

  /* Uebergebene Datei oeffnen */
  PV_fp=fopen(IV_dateiname,"rb");

  if (PV_fp==NULL)
   { return (FEHLER_BEIM_OEFFNEN); };

  PV_rueckgabezeiger=fread(MV_datenfeld,IN_DATEILAENGE,1,PV_fp);

  if (PV_rueckgabezeiger < 1)
   { return (FEHLER_BEIM_LESEN); };

  fclose (PV_fp);
  return (OK);
}


int MP_argumente_pruefen(int VV_argumente, char *IV_argumentfeld[])
/*******************************************************************/
/* Argumente pruefen                                               */
/*******************************************************************/
{
  MT_boolean PV_test = EK_false;
  char PV_zaehler;

  /* Ungueltige Anzahl uebergebener Argumente beim Aufruf ? */
  if (VV_argumente != 2)
   { return (UNGUELTIGE_ARGUMENTENANZAHL); }
      
  /* Endung suchen */
  do  
  {
    if ((char *)*IV_argumentfeld[1] == (char *)NULL)
     { return (NULL_ZEIGER); }
    else
      {
       if (*IV_argumentfeld[1] == '.')
         { PV_test = EK_true; }
       else
         { IV_argumentfeld[1]++; }
      }
  } while (PV_test != EK_true);

  for (PV_zaehler = 0; PV_zaehler <= 3; PV_zaehler ++)
    {
      /* Beliebige Endung erlaubt */
      IV_argumentfeld[1]++;
    }
  return (OK);
}



int MP_feld_speichern(char* IV_dateiname, int VV_laenge)
/*******************************************************************/
/* Feld speichern                                                  */
/*******************************************************************/
{
  FILE* PV_fp;
  MT_boolean PV_fertig = EK_false;
  char* PV_dateinamenkopie;
  size_t PV_anzahl;

  PV_dateinamenkopie = IV_dateiname;

  /* Endung suchen */
  do  
  {
    if (*PV_dateinamenkopie == 0)
     { return (FEHLER_IM_DATEINAMEN); };
    if (*PV_dateinamenkopie == '.')
     { PV_fertig = EK_true; }
    else 
     { PV_dateinamenkopie++;}
  } while (PV_fertig != EK_true);

  /*-spezifisch-------------------------*/
  /* Endung anfuegen */
  PV_dateinamenkopie++;
  if (*PV_dateinamenkopie == 0)
   { return (FEHLER_IM_DATEINAMEN); };

  PV_dateinamenkopie++;
  if (*PV_dateinamenkopie == 0)
   { return (FEHLER_IM_DATEINAMEN); };
  /*------------------------------------*/

  /* Neue Endung einfgen */
  strncpy(PV_dateinamenkopie,ENDUNG_OUT,strlen(ENDUNG_OUT));

  /* Ausgabedatei oeffnen */
  PV_fp=fopen(IV_dateiname,"wb"); 

  if (PV_fp == NULL)
   { return (FEHLER_BEIM_ERSTELLEN); };

  /* Daten schreiben */
  PV_anzahl=fwrite(MV_lauflaengenfeld,VV_laenge,1,PV_fp);

  if (PV_anzahl != 1)
   { return (FEHLER_BEIM_SCHREIBEN); };

  /* Kein Fehler aufgetreten */
  printf("Schreibe %s ... O.K.!\n",IV_dateiname);
  return (OK);
}


#ifdef DEBUGGEN
void MP_debug_ausgabe(int VV_dateilaenge)
/*******************************************************************/
/* Fuer Entwicklungszwecke:                                        */
/* Ausgabe der interpretierten Daten auf StdOut                    */
/*******************************************************************/
{
  int LV_zaehler;

  int PV_zaehler2 = 0;
  /* Zaehler, wieviel Zeichen noch zur aktuellen Zeichenkette gehoeren */

  printf("\n");
    for (LV_zaehler = 0;LV_zaehler < VV_dateilaenge;LV_zaehler++)
    {
      if (PV_zaehler2 == 0)
       {

         if  (
               ( MV_lauflaengenfeld[LV_zaehler] & KOMPRESSIONSINDIKATOR ) ==
                 KOMPRESSIONSINDIKATOR
               )
          {
            /* komprimierte Zeichenfolge liegt vor */
            PV_zaehler2 = 1;

            printf ("\nlaengenkomprimiert (%d):",
             (int)(MV_lauflaengenfeld[LV_zaehler] ^ KOMPRESSIONSINDIKATOR));
          }
         else
          {
            /* unkomprimierte Zeichenfolge liegt vor */
            PV_zaehler2 = MV_lauflaengenfeld[LV_zaehler];

            printf ("\nunkomprimiert (%d):",
             (int)(MV_lauflaengenfeld[LV_zaehler]));

          };

       }
      else
       {
         /* Zeichen gehoert zu komprimierter oder unkomprimierter
            Zeichenkette */
         printf("%c",MV_lauflaengenfeld[LV_zaehler]);

         /* Zeichenkette wurde um 1 Stelle abgearbeitet */
         PV_zaehler2--;
       };

    }
}
#endif


void MP_ausgabe(int VV_dateilaenge)
/*******************************************************************/
/* Ausgabe des Kompressionsgrades auf StdOut                       */
/*******************************************************************/
{
  double PV_kompressionsgrad;

  PV_kompressionsgrad = (1 -
                         (
                          (double)VV_dateilaenge / 
                          (double)IN_DATEILAENGE) 
                         ) * 100;

  printf("Dateilaenge: %d Bit\n", VV_dateilaenge*8);
  printf("Kompressionsgrad: %f %%\n", PV_kompressionsgrad);

}


int MP_berechnung(void)
/*******************************************************************/
/* Lauflaengenkompression berechnen                                */
/*******************************************************************/
{
  int LV_zaehler;
  /* Datenzeichen-Zaehler im Datenfeld */

  int PV_dateilaenge;
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  /* Dateilaenge = Anzahl gueltige Zeichen des Lauflaengenfeldes */
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  int PV_zaehlzeichen_zeiger;
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  /* Zeiger auf aktuelles Zaehlzeichens im Lauflaengenfeld */
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  char PV_vergleichszeichen;
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
  /* Vergleichszeichen = letztes gespeichertes Zeichen */
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++*/


  /* 1. Zeichen wird zum ersten Vergleichszeichen */
  PV_vergleichszeichen = MV_datenfeld[0];

  /* Anfangs-Laenge des ersten Zaehlzeichens */
  MV_lauflaengenfeld[0] = 1;

  /* 1. Zeichen wird in jedem Fall abgespeichert */
  MV_lauflaengenfeld[1] = MV_datenfeld[0];

  /* Zeiger auf aktuelles Zaehlzeichens im Lauflaengenfeld */
  PV_zaehlzeichen_zeiger=0;

  /* 1 Zaehlzeichen und 1 Datenzeichen werden in jedem Fall abgespeichert */
  PV_dateilaenge = 2;


  for (LV_zaehler = 1; LV_zaehler < IN_DATEILAENGE; LV_zaehler++)
   {

    switch ( MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] )

    {

     case 1:
     case (1 | KOMPRESSIONSINDIKATOR):
       /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       /* Hier Entscheidung, ob die gerade angefangene Zeichenfolge   */ 
       /* eine komprimierte oder unkomprimierte  Zeichenfolge wird    */ 
       /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       
       MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]++;

       if (PV_vergleichszeichen == MV_datenfeld[LV_zaehler])
         {
           /* komprimierte Zeichenfolge liegt vor */

           /* Setzen des Kompressionsbits */
           MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] =
           MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] | KOMPRESSIONSINDIKATOR;

         }
       else
         {
           /* unkomprimierte Zeichenfolge liegt vor */

           /* Abspeichern des unkomprimierten Zeichens */
           MV_lauflaengenfeld [PV_dateilaenge++] = MV_datenfeld[LV_zaehler];

         };

       break;

     case (KOMPRESSIONSINDIKATOR - 1):

       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       /* Maximaler Wert des Zaehlzeichens einer unkomprimierten     */
       /* Zeichenkette erreicht                                      */
       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

       if (PV_vergleichszeichen == MV_datenfeld[LV_zaehler])
         {
           /*+++++++++++++++++++++++++++++++++++++++++++++++++*/
           /* Mit dem letzten Zeichen wurde eine komprimierte */
           /* Zeichenfolge angefangen                         */
           /*+++++++++++++++++++++++++++++++++++++++++++++++++*/

           /* Letzte Zeichenfolge wird um ein Zeichen gekuerzt */
           MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]--;

           /* Zaehlzeichen-Zeiger tritt an die Stelle des letzten */
           /* Zeichens im Lauflaengenfeld                         */
           PV_zaehlzeichen_zeiger = PV_dateilaenge - 1;

           /* Setzen des Kompressionsbits, Zeichenfolgenlaenge = 2 */
           MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] =
                                               2 | KOMPRESSIONSINDIKATOR;

           /* Abspeichern des Zeichens */
           MV_lauflaengenfeld [PV_dateilaenge++] = MV_datenfeld[LV_zaehler];

           break;
         };

       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       /* Wenn mit dem letzten Zeichen keine komprimierte Zeichenfolge */
       /* angefangen wurde, Behandlung wie Ueberlauf einer             */
       /* unkomprimierbaren Zeichenkette                               */
       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

     case ((KOMPRESSIONSINDIKATOR - 1) | KOMPRESSIONSINDIKATOR):

       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       /* Maximaler Wert des Zaehlzeichens einer komprimierten       */
       /* Zeichenkette erreicht                                      */
       /* Beginn einer unkomprimierbaren Zeichenkette.               */
       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

       PV_zaehlzeichen_zeiger = PV_dateilaenge++;
       MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] = 1;
       MV_lauflaengenfeld [PV_dateilaenge++] = MV_datenfeld[LV_zaehler];

       break;

     default:

       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
       /* Maximaler Wert des Zaehlzeichens noch nicht erreicht */
       /*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

       if (
            (MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]
            & KOMPRESSIONSINDIKATOR)
            == KOMPRESSIONSINDIKATOR
          )

         {
           /* Bislang wird eine komprimierte Zeichenkette gesammelt */

           if (PV_vergleichszeichen == MV_datenfeld[LV_zaehler])
             {
               /* komprimierte Zeichenfolge wird fortgesetzt */
               MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]++;
             }
           else
             {
               /* Unkomprimierte Zeichenfolge wird begonnen */
               PV_zaehlzeichen_zeiger = PV_dateilaenge++;
               MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] = 1;
               MV_lauflaengenfeld [PV_dateilaenge++] =
                                                 MV_datenfeld[LV_zaehler];
             };

         }
       else
         {
           /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
           /* Bislang wird eine unkomprimierte Zeichenkette gesammelt      */
           /* Koennte es sein, dass mit dem letzten, schon abgespeicherten */
           /* Zeichen eine komprimierbare Zeichenfolge angefangen hat ?    */
           /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

           if (PV_vergleichszeichen == MV_datenfeld[LV_zaehler])
             {
               /*+++++++++++++++++++++++++++++++++++++++++++++++++*/
               /* Mit dem letzten Zeichen wurde eine komprimierte */
               /* Zeichenfolge angefangen                         */
               /*+++++++++++++++++++++++++++++++++++++++++++++++++*/

               /* Letzte Zeichenfolge wird um ein Zeichen gekuerzt */
               MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]--;

               /* Zaehlzeichen-Zeiger tritt an die Stelle des letzten */
               /* Zeichens im Lauflaengenfeld                         */
               PV_zaehlzeichen_zeiger = PV_dateilaenge - 1;

               /* Setzen des Kompressionsbits, Zeichenfolgenlaenge = 2 */
               MV_lauflaengenfeld[PV_zaehlzeichen_zeiger] =
                                                   2 | KOMPRESSIONSINDIKATOR;

               /* Abspeichern des Zeichens */
               MV_lauflaengenfeld [PV_dateilaenge++] = MV_datenfeld[LV_zaehler];

             }
           else
             {
               /* Unkomprimierte Zeichenfolge wird fortgesetzt */
               MV_lauflaengenfeld[PV_zaehlzeichen_zeiger]++;

               MV_lauflaengenfeld [PV_dateilaenge++] =
                                              MV_datenfeld[LV_zaehler];

             };


         };


     }; /* switch */

     /* aktuelles Zeichen wird neues Vergleichszeichen */
     PV_vergleichszeichen = MV_datenfeld[LV_zaehler];

   } /* for */

  return (PV_dateilaenge);
}



int main(int VV_argumenteanzahl, char* IV_argumentefeld[])
/*******************************************************************/
/* Hauptprogramm                                                   */
/*******************************************************************/
{
  int PV_rueckgabewert, PV_laenge;
  char* PV_argument;

  /* Vom DOS bergebenen Parameter uebernehmen */
  PV_argument = IV_argumentefeld[1]; 

  #ifdef BILDSCHIRM_LOESCHEN
    clrscr();
  #endif

  #ifdef DEBUGGEN
    /* Anzahl und 1. uebergebenes Argument ausgeben */
    printf("Anzahl der Argumente: %d\n Argument 1: %s\n",
           VV_argumenteanzahl,IV_argumentefeld[1]);
  #endif

  PV_rueckgabewert = MP_argumente_pruefen(2,IV_argumentefeld);

  /* Ueberpruefung ob ein gueltiger Dateiname uebergeben wurde */
  if (PV_rueckgabewert != OK)  
    {
      /* Wenn nicht -> Fehlermeldung */
      printf("Fehler! Fehlercode = %d",PV_rueckgabewert);
      return (PV_rueckgabewert);
    }

  #ifdef DEBUGGEN
    /* Anzahl und 1. uebergebenes Argument ausgeben */
    printf("Anzahl der Argument: %D\nArgument 1: %s\n",
           VV_argumenteanzahl,IV_argumentefeld[1]);
  #endif

  PV_rueckgabewert = MP_datei_oeffnen(PV_argument);

  /* Datei mit Daten oeffnen */
  if (PV_rueckgabewert != OK)  
    {
      /* Wenn Fehler beim Oeffnen -> Fehlermeldung */
      printf("Fehler! Fehlercode = %d",PV_rueckgabewert);
      return (PV_rueckgabewert);
    }

  /* Lauflaengenkompression berechnen */
  PV_laenge = MP_berechnung();

  /* Ausgabe des Kompressionsgrades */
  MP_ausgabe(PV_laenge);
 
  #ifdef DEBUGGEN
  /* Ausgabe der ersten interpretierten Daten */
  MP_debug_ausgabe(PV_laenge);
  #endif

  /* Speichern der Differenzen */
  PV_rueckgabewert = MP_feld_speichern(PV_argument, PV_laenge);

  /* Wenn Fehler beim Erstellen -> Fehlermeldung */
  if (PV_rueckgabewert != OK)
    {
      printf("Fehler! Fehlercode = %d",PV_rueckgabewert);
      return (PV_rueckgabewert);
    }
  return (0);
}

/* EOF */

