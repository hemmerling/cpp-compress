#ifndef COMPRESS_H
#define COMPRESS_H
/**
 *  @package   compress
 *  @file      compress.h
 *  @brief     Include-Datei fuer die Programme des Pakets compress
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "Microsoft Visual C++",
 *             Entwicklungswerkzeug 
 *             "Microsoft Visual Studio Express 2013 for Windows Desktop"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  compress.h - Include-Datei fuer die C-Programme des Pakets compress
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
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Include-Dateien                                                 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Konstanten-Definitionen                                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  @def      FALSCHER_WERT
 *  @brief    FALSCHER_WERT
 */
#define FALSCHER_WERT 0
/**
 *  @def      WAHRER_WERT
 *  @brief    WAHRER_WERT
 */
#define WAHRER_WERT 1
/**
 *  @def      OK
 *  @brief    OK
 */
#define OK 5


/* Argumente_pruefen */
/**
 *  @def      UNGUELTIGE_ARGUMENTENANZAHL
 *  @brief    Argumente_pruefen - UNGUELTIGE_ARGUMENTENANZAHL
 */
#define UNGUELTIGE_ARGUMENTENANZAHL 10
/**
 *  @def      UNGUELTIGE_ENDUNG
 *  @brief    Argumente_pruefen - UNGUELTIGE_ENDUNG
 */
#define UNGUELTIGE_ENDUNG 11
/**
 *  @def      NULL_ZEIGER
 *  @brief    Argumente_pruefen - NULL_ZEIGER
 */
#define NULL_ZEIGER 12


/* Datei_oeffnen */
/**
 *  @def      UNGUELTIGE_DATEILLAENGE
 *  @brief    Datei_oeffnen - UNGUELTIGE_DATEILLAENGE
 */
#define UNGUELTIGE_DATEILLAENGE 20
/**
 *  @def      FEHLER_BEIM_LESEN
 *  @brief    Datei_oeffnen - FEHLER_BEIM_LESEN
 */
#define FEHLER_BEIM_LESEN 21
/**
 *  @def      FEHLER_BEIM_OEFFNEN
 *  @brief    Datei_oeffnen - FEHLER_BEIM_OEFFNEN
 */
#define FEHLER_BEIM_OEFFNEN 22


/* Feld_speichern */
/**
 *  @def      FEHLER_IM_DATEINAMEN
 *  @brief    Feld_speichern - FEHLER_IM_DATEINAMEN
 */
#define FEHLER_IM_DATEINAMEN 30
/**
 *  @def      FEHLER_BEIM_ERSTELLEN
 *  @brief    Feld_speichern - FEHLER_BEIM_ERSTELLEN
 */
#define FEHLER_BEIM_ERSTELLEN 31
/**
 *  @def      FEHLER_BEIM_SCHREIBEN
 *  @brief    Feld_speichern - FEHLER_BEIM_SCHREIBEN
 */
#define FEHLER_BEIM_SCHREIBEN 32


/* Dateilaenge definieren */
/**
 *  @def      DATEILAENGE
 *  @brief    Endung und Dateilaenge definieren - DATEILAENGE
 */
#define DATEILAENGE 500
/**
 *  @def      IN_DATEILAENGE
 *  @brief    Endung und Dateilaenge definieren - IN_DATEILAENGE
 */
#define IN_DATEILAENGE DATEILAENGE
/**
 *  @def      OUT_DATEILAENGE
 *  @brief    Endung und Dateilaenge definieren - OUT_DATEILAENGE
 */
#define OUT_DATEILAENGE 2*DATEILAENGE
/**
 *  @def      KOMPRESSIONSINDIKATOR
 *  @brief    Endung und Dateilaenge definieren - KOMPRESSIONSINDIKATOR
 */
#define KOMPRESSIONSINDIKATOR 0x080
/**
 *  @def      DATENTYP
 *  @brief    Endung und Dateilaenge definieren - DATENTYP
 */
#define DATENTYP unsigned


/* Schalter */
/**
 *  @def      DEBUGGEN
 *  @brief    Schalter - DEBUGGEN
 */
#define DEBUGGEN
/**
 *   def      BILDSCHIRM_LOESCHEN
 *  @brief    Schalter - BILDSCHIRM_LOESCHEN
 */
#undef BILDSCHIRM_LOESCHEN

/*******************************************************************/
/* Typendefinition                                                 */
/*******************************************************************/

/** 
 *  @typedef  MT_boolean
 *  @brief    MT_boolean
 */
typedef enum
      { EK_true   = 1,
        EK_false  = 0
      } MT_boolean;

#endif
