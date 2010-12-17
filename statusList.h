/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     statusList.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once
//#define NULL 0
//transition defines
#define TRANSITION_OK 0								//prechod vporiadku
#define TRANSITION_BAD_ARGS -1						//prechod dostal nespravne nastavenia
#define TRANSITION_UNCLEAR_PATH -2
#define TRANSITION_SIM_END 1						//prechod uz nema kam pokracovat
#define TRANSITION_BAD_DATA -3						//metoda GetData nedostane ocakavane data, chyba v modely
#define TRANSITION_ACTION_FAIL -4					//nepodarilo sa odobrat gulicky miestu
#define TRANSITION_NOT_RUN -5						//transakcia nemoze prebehnut z dovodu nedostatku guliciek
//place defines
#define PLACE_OK 0									//miesto vporiadku
#define PLACE_BAD_ARGS -1							//miesto dostalo nespravne nastavenia
#define PLACE_SIM_END 1								//miesto nema kam pokracovat
//directed arc defines
#define DIRECTEDARC_OK 0							//hrana vporiadku
#define DIRECTEDARC_NULL_ARG -1
//directed arc modes
#define DIRECTEDARC_INHIB 1							//inhibicna hrana
#define DIRECTEDARC_DEFAULT 0						//normalna hrana
//base defines
#define BASE_OK 0
#define BASE_NULL_ARG -1
//baseData defines
#define TRANSITION_WAIT 0							//prechod s casom
#define TRANSITION_PROBAB 1							//prechod s pravdepodobnostou
#define TRANSITION_PRIO 2							//prechod s prioritou
#define TRANSITION_DEFAULT -1						//prechod zo zakladnym nastavenim po spusteni iba pre kontrolu
#define TRANSITION_NOPARAM 5						//prechod bez parametra - zakladne nastavenie
#define BASE_DEFAULT 3								//zakladne nastavenie struktury
#define PLACE_CAP 4									//miesto s parametrami - prve styri byty aktualna hodnota, druhe styri byty maximalna kapacita 
//model error defines
#define RUNTIME_TRANSITION_CRASH -1					//prechody patriace k jednemu miestu nie su kompatibilne
#define RUNTIME_PLACE_CRASH_PROBAB -5
#define RUNTIME_PLACE_CRASH -2
#define RUNTIME_PLACE_CRASH_WAIT - 3
#define RUNTIME_DIRECTEDARC_INHIB_COL -6			//nastavenie inhibicnej hrany zlyhalo pretoze uz je nastavena vaha
#define RUNTIME_TRANS_PROB_LIMIT -7					//sucet pravdepodobnosti u prechodov dosahuje viac ako 100 percent
#define PLACE_UNKNOWN_ERR -4
//action codes
#define ACTION_TAKE	0								//odcitaj z aktualnej hodnoty poctu guliciek parameter
#define ACTION_RETURN 1								//pripocitaj k aktualnej hodnote poctu guliciek parameter
//runtime codes
#define ACTION_DEFAULT 0							//zakladna hodnota pri inicializacii
#define PLACE_EMPTY 1								//miesto je prazdne
#define PLACE_TAKEN 2								//gulicky boli uspesne odobrane z miesta
#define PLACE_RETURNED 3							//gulicky boli uspesne vratene miestu
#define PLACE_SUCC 4								//miesto uspesne prevedene
#define PLACE_FAIL 5								//miesto neuspesne prevedene
//time types
#define TIME_ABS 9									//absolutny cas
#define TIME_EXP 0									//exponencialny cas
#define TIME_POIS 1									//poissonov proces prichodov
#define TIME_NORM 2									//gausove rozlozenie nahodnosti prichodov
//compare results
#define COMPARE_EQUAL 0								//scplaces are equal
#define COMPARE_VALUE 1								//value not same
#define COMPARE_CAP 2								//capacity not same
#define COMPARE_ID 3								//id not sam
// coreFunc typ modelu
#define MODEL_0 0									// vsechny modely
#define MODEL_1 1									// 1 model
#define MODEL_2 2									// modely ...
#define MODEL_3 3
#define MODEL_4 4
#define MODEL_5 5
#define MODEL_6 6
#define MODEL_7 7
#define MODEL_8 8

