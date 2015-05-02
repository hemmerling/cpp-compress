#ifndef EINSDIFF_H
#define EINSDIFF_H
/**
 *  @package   compress
 *  @file      einsdiff.h
 *  @brief     Include-Datei fuer das Programm "einsdiff.c"
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             Programmiersprache "Microsoft Visual C++",
 *             Entwicklungswerkzeug 
 *             "Microsoft Visual Studio Express 2013 for Windows Desktop"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  einsdiff.h - Include-Datei fuer das Programm "einsdiff.c"
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
 *  Haupt-Entwicklungszeit: 2000-03-01 - 2000-03-17
 */
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Konstanten-Definitionen                                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Programm-spezifische Datei-Endungen definieren */
/**
 *  @def      ENDUNG_IN
 *  @brief    Endung und Dateilaenge definieren - ENDUNG_IN
 */
#define ENDUNG_IN ".mes"

/**
 *  @def      ENDUNG_OUT
 *  @brief    Endung und Dateilaenge definieren - ENDUNG_OUT
 */
#define ENDUNG_OUT ".1st"

 
/*******************************************************************/
/* Funktions-Definitionen ( Prototypen )                           */
/*******************************************************************/
/**
 *  @fn       MP_datei_oeffnen(char* IV_dateiname)
 *  @param    IV_dateiname
 *  @return   int
 *  @brief    Datei öffnen
 */
int MP_datei_oeffnen(char* IV_dateiname);

/**
 *  @fn       MP_argumente_pruefen(int VV_argumente, char* IV_argumentfeld[])
 *  @param    VV_argumente
 *  @param	  IV_argumentfeld
 *  @return   int
 *  @brief    Argumente pruefen  
 */
int MP_argumente_pruefen(int VV_argumente, char* IV_argumentfeld[]);

/**
 *  @fn       MP_feld_speichern(char* IV_dateiname, int VV_laenge)
 *  @param    IV_dateiname
 *  @param	  VV_laenge
 *  @return   int
 *  @brief    Feld speichern  
 */
int MP_feld_speichern(char* IV_dateiname, int VV_laenge);

/**
 *  @fn       MP_berechnung
 *  @return   int
 *  @brief    1. Differenzen berechnen  
 */
int MP_berechnung(void);

/**
 *  @fn       main(int VV_argumenteanzahl, char* IV_argumentefeld[])
 *  @param    VV_argumenteanzahl
 *  @param    IV_argumentefeld
 *  @return   int
 *  @brief    Hauptprogramm  
 */
int main(int VV_argumenteanzahl, char* IV_argumentefeld[]);

#ifdef DEBUGGEN
/**
 *  @fn       MP_debug_ausgabe(int VV_dateilaenge)
 *  @param    VV_dateilaenge
 *  @brief    Hauptprogramm  
 */
void MP_debug_ausgabe(int VV_dateilaenge);
#endif

#endif

