/**
 *  @package   compress
 *  @file      zweidiff.c
 *  @brief     Ermittelung der "Zweiten Differenzen" von in einer Binaerdatei
 *             gespeicherten Daten 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "Microsoft Visual C++",
 *             Entwicklungswerkzeug 
 *             "Microsoft Visual Studio Express 2013 for Windows Desktop"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  einsdiff.c - Ermittelung der "Zweiten Differenzen" von in einer Binaerdatei
 *               gespeicherten Daten 
 *               Labor fuer Datenverarbeitung, FH Hannover,
 *               Versuch 12 "Datenkompression"   
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
#include "zweidiff.h"

/*******************************************************************/
/* Modulglobale Variablen                                          */
/*******************************************************************/

/**
 *  @var      MV_datenfeld
 *  @brief    Feld fuer Orginaldaten  
 */
DATENTYP char MV_datenfeld[IN_DATEILAENGE];

/**
 *  @var      MV_differenzfeld
 *  @brief    Feld fuer Differenz-Daten 
 */
DATENTYP char MV_differenzfeld[OUT_DATEILAENGE];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Funktions-Deklarationen                                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static int MP_datei_oeffnen(char* dateiname)
/*******************************************************************/
/* Datei oeffnen                                                   */
/*******************************************************************/
{
  FILE* PV_fp;
  size_t PV_rueckgabezeiger;

  /* Uebergebene Datei oeffnen */
  PV_fp=fopen(dateiname,"rb");

  if (PV_fp==NULL)
   { return (FEHLER_BEIM_OEFFNEN); };

  PV_rueckgabezeiger=fread(MV_datenfeld,IN_DATEILAENGE,1,PV_fp);

  if (PV_rueckgabezeiger < 1)
   { return (FEHLER_BEIM_LESEN); };

  fclose (PV_fp);
  return (OK);
}


static int MP_argumente_pruefen(int VV_argumente, char *IV_argumentfeld[])
/*******************************************************************/
/* Argumente pruefen                                               */
/*******************************************************************/
{
  MT_boolean PV_test = EK_false;
  char LV_zaehler;
  /*-spezifisch-------------------------*/
  char PV_vergleich[] = ENDUNG_IN;
  /*------------------------------------*/

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

  for (LV_zaehler = 0; LV_zaehler <= 3; LV_zaehler ++)
    {
      /*-spezifisch-------------------------*/
      /* Endung vergleichen mit geforderter Endung*/
      if (*IV_argumentfeld[1] != PV_vergleich[LV_zaehler])
       { return (UNGUELTIGE_ENDUNG); };
      /*------------------------------------*/
      IV_argumentfeld[1]++;
    }
  return (OK);
}



static int MP_feld_speichern(char* IV_dateiname, int VV_laenge)
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

  /* Neue Endung einfgen */
  strncpy(PV_dateinamenkopie,ENDUNG_OUT,strlen(ENDUNG_OUT));

  /* Ausgabedatei oeffnen */
  PV_fp=fopen(IV_dateiname,"wb"); 

  if (PV_fp == NULL)
   { return (FEHLER_BEIM_ERSTELLEN); };

  /* Daten schreiben */
  PV_anzahl=fwrite(MV_differenzfeld,VV_laenge,1,PV_fp);

  if (PV_anzahl != 1)
   { return (FEHLER_BEIM_SCHREIBEN); };

  /* Kein Fehler aufgetreten */
  printf("Schreibe %s ... O.K.!\n",IV_dateiname);
  return (OK);
}


#ifdef DEBUGGEN
static void MP_debug_ausgabe(int VV_dateilaenge)
/*******************************************************************/
/* Fuer Entwicklungszwecke:                                        */
/* Ausgabe der ersten 21 Orginaldaten und 2.Differenzen auf StdOut */
/*******************************************************************/
{
  int LV_zaehler;
  printf("\n");
    for (LV_zaehler = 0;LV_zaehler < 20;LV_zaehler++)
    {
      printf("%d, ",MV_datenfeld[LV_zaehler]);
      printf("%d \n",MV_differenzfeld[LV_zaehler]);
    }
}
#endif


static int MP_berechnung(void)
/*******************************************************************/
/* 2. Differenzen berechnen                                        */
/*******************************************************************/
{
  int LV_zaehler;
  int PV_dateilaenge = OUT_DATEILAENGE; /* statisch */

  /* 1.+2. zweite Differenz berechnen */
  MV_differenzfeld[0] = MV_datenfeld[0];
  MV_differenzfeld[1] = MV_datenfeld[1] - (2 * (MV_datenfeld[1-1]));

  for (LV_zaehler = 2; LV_zaehler < IN_DATEILAENGE; LV_zaehler++)
  {
    /* 3. bis n. zweite Differenzen berechnen */
    MV_differenzfeld[LV_zaehler] =  MV_datenfeld[LV_zaehler] -
                                 (2*MV_datenfeld[LV_zaehler-1]) +
                                 MV_datenfeld[LV_zaehler-2];
  }

  

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

  /* Zweite Differenzen berechnen */
  PV_laenge = MP_berechnung();

  #ifdef DEBUGGEN
  /* Ausgabe der ersten 21 Orginaldaten und 2.Differenzen */
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

