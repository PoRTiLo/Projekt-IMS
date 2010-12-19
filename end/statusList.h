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
#define TRANSITION_BAD_ARGS -21						//prechod dostal nespravne nastavenia
#define TRANSITION_UNCLEAR_PATH -2
#define TRANSITION_SIM_END 1						//prechod uz nema kam pokracovat
#define TRANSITION_BAD_DATA -13						//metoda GetData nedostane ocakavane data, chyba v modely
#define TRANSITION_ACTION_FAIL 4					//nepodarilo sa odobrat gulicky miestu
#define TRANSITION_NOT_RUN 5						//transakcia nemoze prebehnut z dovodu nedostatku guliciek
//place defines
#define PLACE_OK 0									//miesto vporiadku
#define PLACE_BAD_ARGS -1							//miesto dostalo nespravne nastavenia
#define PLACE_SIM_END 10							//miesto nema kam pokracovat
//directed arc defines
#define DIRECTEDARC_OK 0							//hrana vporiadku
#define DIRECTEDARC_NULL_ARG -1
//directed arc modes
#define DIRECTEDARC_INHIB 1							//inhibicna hrana
#define DIRECTEDARC_DEFAULT 0						//normalna hrana
//base defines
#define BASE_OK 0
#define BASE_NULL_ARG -1
#define BASE_FATAL -100								//nastala fatalna chyba s petriho sietou, nemozno pokracovat
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
#define RUNTIME_DIRECTEDARC_INHIB_COL -6			//nastavenie inhibicnej hrany zlyhalo pretoze uz je nastavena vaha
#define RUNTIME_TRANS_PROB_LIMIT -7					//sucet pravdepodobnosti u prechodov dosahuje viac ako 100 percent
#define RUNTIME_TRANS_PROB_LOW -8					//sucet pravdepodobnosti u prechodov nedosahuje 100 percent a neexistuje prechod bez parametra
#define PLACE_UNKNOWN_ERR -4
//action codes
#define ACTION_TAKE	0								//odcitaj z aktualnej hodnoty poctu guliciek parameter
#define ACTION_RETURN 1								//pripocitaj k aktualnej hodnote poctu guliciek parameter
//runtime codes
#define ACTION_DEFAULT 0							//zakladna hodnota pri inicializacii
#define PLACE_FULL	14
#define PLACE_EMPTY 11								//miesto je prazdne
#define PLACE_TAKEN 12								//gulicky boli uspesne odobrane z miesta
#define PLACE_RETURNED 13							//gulicky boli uspesne vratene miestu
//time types
#define TIME_ABS 9									//absolutny cas
#define TIME_EXP 0									//exponencialny cas
#define TIME_POIS 1									//poissonov proces prichodov
#define TIME_NORM 2									//gausove rozlozenie nahodnosti prichodov od - do
#define TIME_ROV 3									//rovnomerne rozlozenie prichodov od - do
//compare results
#define COMPARE_EQUAL 0								//scplaces are equal
#define COMPARE_VALUE 1								//value not same
#define COMPARE_CAP 2								//capacity not same
#define COMPARE_ID 3								//id not sam
//completation errors
#define ERR_COMP_LOOP "MODEL COMPLETATION ERROR: Model contains infinite loop in zero time and cannot be simulated properly, Check model !!!"
#define ERR_COMP_LENGHT "MODEL COMPLETATION ERROR: Model contains infinite mark emitter and is not limited by time, please use function SetSimulationLength() !!!"
