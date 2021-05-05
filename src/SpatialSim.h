#define DO_OMP_PARALLEL
#ifdef COUNTRY_US
#define MAX_NUM_THREADS 36
#else
#define MAX_NUM_THREADS 36
#endif
#define CACHE_LINE_SIZE 256
#include <omp.h>
#define KMP_LIBRARY throughput

#ifndef UNIX
#define WIN32_BM
#endif
#define STRICT
#ifdef WIN32_BM
#define _WIN32_WINNT 0x0400
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vfw.h>
#include <gdiplus.h>
#include "avi_utils.h"
#endif
#ifdef IMAGE_MAGICK
#include "Magick++.h"
#endif

#ifdef FRESSCA
#include "fressca.h"
#define MIN(x,y) x<y ? x : y
#define MAX(x,y) x>y ? x : y
#endif 

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <time.h>

/* ranf defines */
#define Xm1 2147483563
#define Xm2 2147483399
#define Xa1 40014
#define Xa2 40692
#define Xa1vw 2082007225
#define Xa2vw 84306273

/*
  #define COUNTRY_THAILAND 1
  */
#define COUNTRY_UK 1

#define ERR_CRITICAL(x) {fprintf(stderr,x);exit(1);}
  /*
	#define HOST_TREATED(x) (0)
	#define HOST_TO_BE_TREATED(x) (0)
	#define PLACE_TREATED(x,y) (0)
  */
#define FAST_US

#define HOST_TREATED(x) ((Hosts[x].treat_stop_time > ts) && (Hosts[x].treat_start_time <= ts))
#define HOST_TO_BE_TREATED(x) (Hosts[x].treat_stop_time > ts)
#define PLACE_TREATED(x, y) (Places[x][y].treat_end_time > ts)
#define PLACE_CLOSED(x, y) ((Places[x][y].close_start_time <= ts) && (Places[x][y].close_end_time > ts))
#define HOST_TO_BE_VACCED(x) (Hosts[x].vacc_start_time < USHRT_MAX - 1)
#define HOST_VACCED(x) ((Hosts[x].vaccRing == 3) ? (Hosts[x].vacc_start_time + P.usVaccTimeToEfficacyThirdRing <= ts) : (Hosts[x].vacc_start_time + P.usVaccTimeToEfficacy <= ts))
  //#define HOST_VACCED(x) (Hosts[x].vacc_start_time+P.usVaccTimeToEfficacy<=ts)
#define HOST_VACCED_SWITCH(x) (Hosts[x].vacc_start_time >= P.usVaccTimeEfficacySwitch)
#define HOST_QUARANTINED(x) ((Hosts[x].quar_comply == 1) && (Hosts[x].quar_start_time + P.usHQuarantineHouseDuration > ts) && (Hosts[x].quar_start_time <= ts))
#define HOST_TO_BE_QUARANTINED(x) ((Hosts[x].quar_start_time + P.usHQuarantineHouseDuration > ts) && (Hosts[x].quar_comply < 2))
#define HOST_ISOLATED(x) ((Hosts[x].isolation_start_time + P.usCaseIsolationDelay <= ts) && (Hosts[x].isolation_start_time + P.usCaseIsolationDelay + P.usCaseIsolationDuration > ts))
#define HOST_ABSENT(x) ((Hosts[x].absent_start_time <= ts) && (Hosts[x].absent_stop_time > ts))

#define PI 3.1415926535
#define EARTHRADIUS 6366707.0
#define BIT15 32768
#define BIT10 1024
#define BIT20 1048576

#define OUTPUT_DIST_SCALE 1000
#define MAX_PLACE_SIZE 20000
#define MAX_NUM_SEED_LOCATIONS 1000

#define MAX_BACKG_COLS 32

#ifdef COUNTRY_UK
#define MAX_DIST 2000
#define NK_HR 400
#define NKR 2000000
#elif defined(COUNTRY_THAILAND)
#define MAX_DIST 2000
#define NK_HR 400
#define NKR 2000000

#else
#define MAX_DIST 1000
#define NK_HR 2500
#define NKR 4000000
#endif

#define CDF_RES 20
#define INFPROF_RES 56
#define RECOVERY_RES 100 //resolution of recovery probability function: ggilani - 23/10/14
/* Max household size of 16 */



#define HH_DISABLED 16384
#define CONTACT_MASK 16383

#if   defined(COUNTRY_INDONESIA)
#define MAX_HOUSEHOLD_SIZE 15
#define MAX_NUM_RESIST_TYPES 3
#define MAX_INTERVENTION_TYPES 1
#define MAX_INTERVENTIONS_PER_ADUNIT 10
#elif   defined(COUNTRY_WA)
#define MAX_HOUSEHOLD_SIZE 15
#define MAX_NUM_RESIST_TYPES 3
#define MAX_INTERVENTION_TYPES 1
#define MAX_INTERVENTIONS_PER_ADUNIT 10
#else
#define MAX_HOUSEHOLD_SIZE 10
#define MAX_NUM_RESIST_TYPES 3
#define MAX_INTERVENTION_TYPES 1
#define MAX_INTERVENTIONS_PER_ADUNIT 10
#endif

#if   defined(COUNTRY_US)
#define NUM_PLACE_TYPES 3
#define NUM_PLACE_TYPES_NOAIR 2
#define HOTEL_PLACE_TYPE 2
#define IMPORT_POP_SIZE 3.2e8
#define ADUNIT_LOOKUP_SIZE 1000000
#define MAX_COUNTRIES 100
#define ABSENTEEISM_PLACE_CLOSURE
#define MAX_ABSENT_TIME 8
#define MAX_ADUNITS 3200
#elif defined(COUNTRY_UK)
#define NUM_PLACE_TYPES 4
#define NUM_PLACE_TYPES_NOAIR 4
#define HOTEL_PLACE_TYPE 5
#define MAX_ADUNITS 2600
#define ADUNIT_LOOKUP_SIZE 1000000
#define MAX_COUNTRIES 100
/*#define IMPORT_POP_SIZE 58000000
#define ABSENTEEISM_PLACE_CLOSURE
*/
#define MAX_ABSENT_TIME 8
#elif defined(COUNTRY_CHINA)
#define NUM_PLACE_TYPES 4
#define NUM_PLACE_TYPES_NOAIR 4
#define HOTEL_PLACE_TYPE 5
#define MAX_ADUNITS 1000
#define ADUNIT_LOOKUP_SIZE 60000
#define MAX_COUNTRIES 100
#elif defined(COUNTRY_THAILAND)
#define NUM_PLACE_TYPES 4
#define NUM_PLACE_TYPES_NOAIR 4
#define HOTEL_PLACE_TYPE 5
#define MAX_ADUNITS 1000
#else
#define NUM_PLACE_TYPES 4
#define NUM_PLACE_TYPES_NOAIR 4
#define HOTEL_PLACE_TYPE 5
#define MAX_ADUNITS 500
#define ADUNIT_LOOKUP_SIZE 1000000
#define MAX_COUNTRIES 100
#endif

#define PLACE_GROUPS_PER_INT 2
#define NUM_AGE_GROUPS 17
#define AGE_GROUP_WIDTH 5
#define DAYS_PER_YEAR 364
#define INFECT_TYPE_MASK 16
#define MAX_GEN_REC 20
#define MAX_SEC_REC 500
#define INF_QUEUE_SCALE 5
#define MAX_TRAVEL_TIME 14
#define MAX_TRAVEL_RATIO 50

//#define MAX_INFECTIOUS_STEPS 255 //// orig
#define MAX_INFECTIOUS_STEPS 2550



#define MAX_DUR_IMPORT_PROFILE 10245
#define MAX_CHANGE_POINTS 100
#define MAX_RING_SIZE 1000000 //added this for vaccination code

#define MAX_AIRPORTS 5000
#define NNA 10
#define MAX_DIST_AIRPORT_TO_HOTEL 200000.0
#define MIN_HOTELS_PER_AIRPORT 20
#define HOTELS_PER_1000PASSENGER 10
#define PLACE_CLOSE_ROUND_HOUSEHOLD 1

//added for radiation model
#define RAD_INVCDF 100
#define RAD_TRIPS_PP 5
#define RAD_TEMP_MEM_SCALE 1

/*
  #define NO_TREAT_PROPH_CASES
*/

#ifdef NEW_AGE_MODEL
#define HOST_AGE_YEAR(x) ((P.ts_age-Hosts[x].birth_time)/((int) P.TimeStepsPerYear))
#define HOST_AGE_GROUP(x) ((P.ts_age-Hosts[x].birth_time)/(((int) P.TimeStepsPerYear)*AGE_GROUP_WIDTH))
#define DEMOG_EQUILIB_YEARS 1000
#else
#define HOST_AGE_YEAR(x) (Hosts[x].age)
#define HOST_AGE_GROUP(x) (Hosts[x].age / AGE_GROUP_WIDTH)
#endif

#pragma pack(2)


#define NUM_SYMPTO_SEVERITY_CLASSES 4

// SeverityClass defintions / labels (numbers arbitrary but must be different to each other).
#define Severity_Asymptomatic				-1		//// Flag value.
#define Severity_Mild						0
#define Severity_ILI						1
#define Severity_SARI						2
#define Severity_Critical					3
#define Severity_RecoveringFromCritical		4		//// Recovering from Critical (not recovered yet). Not included in NUM_SYMPTO_SEVERITY_CLASSES but could change. Also doesn't count as person.Severity_Final
#define Severity_Dead						5		//// label to avoid double counting. Not sure you need. 
#define Severity_Recovered					6		//// label to avoid double counting. Not sure you need. 

//// Infection Status definitons / labels (generally positive value indicates asymptomatic infection, negative value indicates symptomatic infection). 
#define InfStat_Susceptible						0				//// Susceptible
#define InfStat_Latent							1				//// E or L (neither infectious nor symptomatic). 
#define InfStat_InfectiousAlmostSymptomatic		-1				//// Infectious and about to become a case.
#define InfStat_InfectiousAsymptomaticNotCase	2				//// Not just asymptomatic, but also will not become symptomatic (i.e. a case.)
#define InfStat_Case							-2				//// case. Infectious and symptomatic. 
#define InfStat_RecoveredFromAsymp				3				//// Recovered from asymptomatic infection
#define InfStat_RecoveredFromSymp				-3				//// Recovered from symptomatic infection
#define InfStat_Recovered						3				//// InfStat_Recovered (will use this for abs() values) so code reads correctly
#define InfStat_ImmuneAtStart					4				//// Immune at start of epidemic - used to model partially immune population. Distinct therefore from recovered, who recovered during runtime. Doesn't take negative values. 
#define InfStat_Dead_WasAsymp					5				//// Dead was asymptomatic
#define InfStat_Dead_WasSymp					-5				//// Dead was symptomatic
#define InfStat_Dead							5				//// Dead (will use this for abs() values) so code reads correctly
#define InfStat_DeadButInfectious				6				//// Dead but infectious (for funerals)

//// place type codes
#define PlaceType_PrimarySchool			0
#define PlaceType_SecondarySchool		1
#define PlaceType_University			2
#define PlaceType_Office				3

//// need to test that inequalities in IncubRecoverySweep can be replaced if you initialize to USHRT_MAX, rather than zero. 
//// need to output quantities by admin unit

typedef struct PERSON {

	int pcell; //// place cell, 
	int mcell; //// microcell
	int listpos, infector, hh /*= household*/;
#ifdef NEW_AGE_MODEL	
	int birth_time, init_birth_time;
	unsigned short int life_expectancy;
#else
	unsigned short int age;
#endif
	unsigned short int to_die, Travelling, hospitalised, detected; //added hospitalisation flag: ggilani 28/10/2014, added flag to determined whether this person's infection is detected or not
	int dayDetected; //added a parameter to store the day on which a case is detected, to determine whether or not they are eligible for contact tracing or not : ggilani 23/06/2015
	int contactTraced; //added a parameter to store whether someone is contact traced or not: ggilani 06/06/17
	int vaccRing, ringCase; //added to track who is in the third ring of vaccination and which ring they are associated with: ggilani 29/05/19
	int hosp_AU; //added identifier for which admin unit a host is hospitalised in: ggilani 24/11/14
	unsigned short int nc_plus_hh_disabled, esocdist_comply, quar_start_time, quar_comply, isolation_start_time, isolation_stop_time, keyworker; //added isolation stop time to help with contact tracing
	unsigned short int absent_start_time, absent_stop_time;
	unsigned short int PlaceGroupLinks[NUM_PLACE_TYPES];
	int PlaceLinks[NUM_PLACE_TYPES]; //// indexed by i) place type. Value is the number of that place type (e.g. school no. 17; office no. 310 etc.)
	int PlacePresence[NUM_PLACE_TYPES]; //added this to help keep track of household members who should be in similar places, when actually doing the place assignment: ggilani 10/02/17
	float base_inf_level;
	float infectiousness, susc, vacc_eff, infectiousMult; //added infectiousMult to help reset infectiousness
	double rep_rate; // added this to allow for clustering of reporting rates in households/places: ggilani 
	short int inf, infect_type;
	unsigned short int infection_time, latent_time;		// Set in DoInfect function. infection time is time of infection; latent_time is time at which you become infectious (i.e. infection time + latent period for this person). latent_time will also refer to time of onset with ILI or Mild symptomatic disease. 
	unsigned short int recovery_time, hospital_time;	// set in DoIncub function (note recovery_time can be death_time also) //added time to hospitalisation: ggilani 28/10/2014//added time to hospitalisation: ggilani 28/10/2014
	unsigned short int treat_start_time, treat_stop_time, vacc_start_time;  //// set in TreatSweep function. 
	unsigned short int contactTraced_start_time, contactTraced_end_time; //added contact tracing start time as well: ggilani 14/06/17
	short int num_treats, resist;
	int Severity_Current, Severity_Final; //// Note we allow Severity_Final to take values: Severity_Mild, Severity_ILI, Severity_SARI, Severity_Critical (not e.g. Severity_Dead or Severity_RecoveringFromCritical)
	unsigned short int SARI_time, Critical_time, RecoveringFromCritical_time; //// /*mild_time, ILI_time,*/ Time of infectiousness onset same for asymptomatic, Mild, and ILI infection so don't need mild_time etc. 

#ifdef FRESSCA
	int vacc_queue_pos;
#endif
} person;

typedef struct HOUSEHOLD {
	int FirstPerson;
	unsigned short int nh; // number people in household
	float loc_x, loc_y;
	unsigned short int nhr, stockpile;
	float income;
} household;

typedef struct POPVAR {


	int NL, S, L, I, R, D, cumI, cumR, cumD, cumC, cumTC, cumFC, cumInf_h, cumInf_n, cumInf_s, cumDC, trigDC, cumFI; //added cumFI to account for cumulative funeral transmissions: ggilani 24/10/14
	int H, cumH; //Added total and cumulative hospitalisation: ggilani 28/10/14
	int CT, cumCT, CC, cumCC; //Added total and cumulative contact tracing: ggilani 15/06/17
	int cumC_country[MAX_COUNTRIES]; //added cumulative cases by country: ggilani 12/11/14
	int cumHQ, cumAC, cumAA, cumAH, cumACS, cumAPC, cumAPA, cumAPCS;
	//// age specific versions of above variables. e.g. cumI is cumulative infections. cumIa is cumulative infections by age group. 
	int Na[NUM_AGE_GROUPS], cumIa[NUM_AGE_GROUPS], cumCa[NUM_AGE_GROUPS], cumDa[NUM_AGE_GROUPS];
	int cumI_adunit[MAX_ADUNITS], cumC_adunit[MAX_ADUNITS], cumT_adunit[MAX_ADUNITS], cumH_adunit[MAX_ADUNITS], H_adunit[MAX_ADUNITS], cumDC_adunit[MAX_ADUNITS]; //added cumulative hospitalisation per admin unit: ggilani 28/10/14, cumulative detected cases per adunit: ggilani 03/02/15
	int cumCT_adunit[MAX_ADUNITS], CT_adunit[MAX_ADUNITS], cumCC_adunit[MAX_ADUNITS], CC_adunit[MAX_ADUNITS], trigDC_adunit[MAX_ADUNITS]; //added cumulative and CT per admin unit: ggilani 15/06/17
	int cumItype[INFECT_TYPE_MASK], cumI_keyworker[2], cumC_keyworker[2], cumT_keyworker[2];
	int cumI_resist[MAX_NUM_RESIST_TYPES], cumC_resist[MAX_NUM_RESIST_TYPES], cumT_resist[MAX_NUM_RESIST_TYPES];
	int* inv_cell_inf; //// think indexed by i) person. 
	int *inf_queue[MAX_NUM_THREADS], n_queue[MAX_NUM_THREADS * CACHE_LINE_SIZE]; 	// n_queue is number of people in the queue, inf_queue is the actual queue (i.e. list) of people. 1st index is thread, 2nd is person.
	int* p_queue[NUM_PLACE_TYPES], * pg_queue[NUM_PLACE_TYPES], np_queue[NUM_PLACE_TYPES];		// np_queue is number of places in place queue (by place type), p_queue, and pg_queue is the actual place and place-group queue (i.e. list) of places. 1st index is place type, 2nd is place.
	int NumPlacesClosed[NUM_PLACE_TYPES], n_mvacc, mvacc_cum;
	float* cell_inf;  //// List of spatial infectiousnesses by person within cell. 
	double sumRad2, maxRad2, cumT, cumV, cumVG, cumUT, cumTP, cumV_daily, cumVG_daily; //added cumVG, cumVG_daily
	int* CellMemberArray, * CellSuscMemberArray;
	int** InvAgeDist;
	int* mvacc_queue;
	//added for radiation model
	int* MobilityLinks, * InvCDFArray;
	float* MobilityProbs;
	long long NumMobilityLinks;
#ifdef FRESSCA
	int dvacc_wastage, * dvacc_queue;
	unsigned short int* dvacc_expiry_time;
#endif
	int dum[CACHE_LINE_SIZE];
	int* h_queue[MAX_ADUNITS], nh_queue[MAX_ADUNITS], * hd_queue[MAX_ADUNITS], nhd_queue[MAX_ADUNITS]; //queues for hospitalisation by admin unit: ggilani 30/10/14. h_queue and hd_queue actually 2D. Weirdly one dimension allocated on stack and other is pointer. d refers to discharge. n to length of queue. 
	int* ct_queue[MAX_ADUNITS], nct_queue[MAX_ADUNITS]; // queues for contact tracing: ggilani 12/06/17
	int* ringvacc_queue, * ring_queue, * geovacc_queue, nringvacc_queue, ngeovacc_queue, ringvacc_cum, ringvacc_ind, geovacc_cum, geovacc_ind, * ringvacclist, * ringlist; //queues for vaccine: ggilani 20/08/19
	double* origin_dest[MAX_ADUNITS]; //added intermediate storage for calculation of origin-destination matrix: ggilani 02/02/15

									  ///// Prevalence quantities (+ by admin unit)
	int Mild, ILI, SARI, Critical, CritRecov, /*cumulative incidence*/ cumMild, cumILI, cumSARI, cumCritical, cumCritRecov;
	int Mild_adunit[MAX_ADUNITS], ILI_adunit[MAX_ADUNITS], SARI_adunit[MAX_ADUNITS], Critical_adunit[MAX_ADUNITS], CritRecov_adunit[MAX_ADUNITS];
	/// cum incidence quantities. (+ by admin unit)
	int cumMild_adunit[MAX_ADUNITS], cumILI_adunit[MAX_ADUNITS], cumSARI_adunit[MAX_ADUNITS], cumCritical_adunit[MAX_ADUNITS], cumCritRecov_adunit[MAX_ADUNITS];

	//// above quantities need to be amended in following parts of code: 
	//// i) InitModel (set to zero); Done
	//// ii) RecordSample: (collate from threads); 
	//// iii) RecordSample: add to incidence / Timeseries). 
	//// iv) Print out statement in RunModel but you don't need to add to that yet. 
	///// need to update these quantities in InitModel (DONE), Record Sample (DONE) (and of course places where you need to increment, decrement). 



} popvar;

typedef struct RESULTS {

	double t, S, L, I, R, D, incC, incTC, incFC, incL, incI, incR, incD, incFI, incDC; //added incFI to monitor incidence of infections from funeral transmission: ggilani 24/10/14, added incidence of detected cases: 08/03/2017
	double H, incH; //added total hospitalisation and incidence of hospitalisation: ggilani 28/10/14
	double CT, incCT, CC, incCC; //added total numbers being contact traced and incidence of contact tracing: ggilani 15/06/17
	double incC_country[MAX_COUNTRIES]; //added incidence of cases
	double cumT, cumUT, cumTP, cumV, cumTmax, cumVmax, cumDC, extinct, cumVG; //added cumVG
	double incHQ, incAC, incAH, incAA, incACS, incAPC, incAPA, incAPCS;
	double incIa[NUM_AGE_GROUPS], incCa[NUM_AGE_GROUPS], incDa[NUM_AGE_GROUPS];
	double incItype[INFECT_TYPE_MASK], Rtype[INFECT_TYPE_MASK], Rage[NUM_AGE_GROUPS], Rdenom;
	double rmsRad, maxRad, PropPlacesClosed[NUM_PLACE_TYPES], PropSocDist;
	double incI_adunit[MAX_ADUNITS], incC_adunit[MAX_ADUNITS], cumT_adunit[MAX_ADUNITS], incH_adunit[MAX_ADUNITS], H_adunit[MAX_ADUNITS], incDC_adunit[MAX_ADUNITS]; //added incidence of hospitalisation per day: ggilani 28/10/14, incidence of detected cases per adunit,: ggilani 03/02/15
	double incCT_adunit[MAX_ADUNITS], CT_adunit[MAX_ADUNITS], incCC_adunit[MAX_ADUNITS], CC_adunit[MAX_ADUNITS]; //added incidence of contact tracing and number of people being contact traced per admin unit: ggilani 15/06/17
	double incI_keyworker[2], incC_keyworker[2], cumT_keyworker[2];
	double incI_resist[MAX_NUM_RESIST_TYPES], incC_resist[MAX_NUM_RESIST_TYPES], cumT_resist[MAX_NUM_RESIST_TYPES];
	float* bmi2, * bmi3, * bmi4;


	/////// Severity States
	double Mild, ILI, SARI, Critical, CritRecov;	// Prevalence				//// Must be: i) initialised to zero in SetUpModel. ii) outputted in SaveResults iii) outputted in SaveSummaryResults
	double incMild, incILI, incSARI, incCritical, incCritRecov;	// Incidence				//// Must be: i) initialised to zero in SetUpModel. ii) calculated in RecordSample iii) outputted in SaveResults. 
	double cumMild, cumILI, cumSARI, cumCritical, cumCritRecov;	// cumulative incidence		//// Must be: i) initialised to zero in SetUpModel. ii) outputted in SaveResults

																/////// Severity States by admin unit
	double Mild_adunit[MAX_ADUNITS], ILI_adunit[MAX_ADUNITS], SARI_adunit[MAX_ADUNITS], Critical_adunit[MAX_ADUNITS], CritRecov_adunit[MAX_ADUNITS];	// Prevalence by admin unit
	double incMild_adunit[MAX_ADUNITS], incILI_adunit[MAX_ADUNITS], incSARI_adunit[MAX_ADUNITS], incCritical_adunit[MAX_ADUNITS], incCritRecov_adunit[MAX_ADUNITS];	// incidence by admin unit
	double cumMild_adunit[MAX_ADUNITS], cumILI_adunit[MAX_ADUNITS], cumSARI_adunit[MAX_ADUNITS], cumCritical_adunit[MAX_ADUNITS], cumCritRecov_adunit[MAX_ADUNITS]; // cumulative incidence by admin unit

	/////// possibly need quantities by age (later)
	//// state varialbes (S, L, I, R) and therefore (Mild, ILI) etc. changed in i) SetUpModel (initialised to zero); ii) 

	//// above quantities need to be amended in following parts of code: 
	//// i) InitModel (set to zero); Done
	//// ii) RecordSample: (collate from threads); 
	//// iii) RecordSample: add to incidence / Timeseries). 
	//// iv) Print out statement in RunModel but you don't need to add to that yet. 
	///// SaveResults and SaveSummary results. 
	///// need to update these quantities in InitModel (DONE), Record Sample (DONE) (and of course places where you need to increment, decrement). 



} results;

// Added Events struct to allow us to log and write out infection events: ggilani 10/10/14
typedef struct EVENTS {
	double infectee_x, infectee_y, t, t_infector;
	int run, infectee_ind, infector_ind, type, infectee_adunit, listpos, infectee_cell, infector_cell, thread;
} events;

/*
  HQ - quarantined households
  AH - Quarantined (and perhaps sick) working adults
  AC - Non-quarantined working adult cases absent thru sickness.
  AA - Absent working adults who are caring for sick children (only assigned if no non-working, quarantine or sick adults available).
  ACS - Children below care requirement cut-off age who are absent (sick or quarantined)

  APC - Non-quarantined working adult cases absent due to closure of their workplace (excl teachers).
  APA - Absent working adults who are caring for children at home due to school closure (only assigned if no non-working, quarantine or sick adults available).
  ACS - Children below care requirement cut-off age who are absent due to school closure


  AH x rq + AC + AA +(APC+APA) x rc = total adult absence
  rq=ratio of quarantine time to duration of absence due to illness
  rc=ratio of school/workplace closure duration of absence due to illness
*/

typedef struct INDEXLIST {
	int id;
	float prob;
} indexlist;

typedef struct AIRPORT {
	int num_mcell, num_place, Inv_prop_traffic[129], Inv_DestMcells[1025], Inv_DestPlaces[1025];
	unsigned short int country, adunit, num_connected, control, * conn_airports;
	float int_traffic, total_traffic, loc_x, loc_y, control_start_time, control_end_time;
	float* prop_traffic;
	indexlist* DestMcells, * DestPlaces;
} airport;

typedef struct MICROCELL {
	/* Note use of short int here limits max run time to USHRT_MAX*TimeStep - e.g. 65536*0.25=16384 days=44 yrs.
	   Global search and replace of 'unsigned short int' with 'int' would remove this limit, but use more memory.
	*/
	int n /*Number of people in microcell*/, adunit;
	int* members;
	unsigned short int country;

	int* places[NUM_PLACE_TYPES];
	unsigned short int np[NUM_PLACE_TYPES];
	unsigned short int moverest, placeclose, socdist, keyworkerproph, move_trig, place_trig, socdist_trig, keyworkerproph_trig;
	unsigned short int move_start_time, move_end_time;
	unsigned short int place_end_time, socdist_end_time, keyworkerproph_end_time;
	unsigned short int treat, vacc, treat_trig, vacc_trig;
	unsigned short int treat_start_time, treat_end_time;
	unsigned short int vacc_start_time;
	indexlist* AirportList;
	float tot_traffic;
	//for road network
	int road_connection;
#ifdef FRESSCA
	GEO_DISTR_CENTER* VaccineCenter;
	int* dvacc_queue;
	unsigned short int* dvacc_min_vacc_time, * dvacc_expiry_time;
	int ndvacc_queue;
	int dvacc_count;
#endif
} microcell;

typedef struct CELL {
	int n, S, L, I, R, D, cumTC, S0, tot_treat, tot_vacc;
	int* members, * susceptible, * latent, * infected; //// pointers to people in cell. e.g. *susceptible identifies where the final susceptible member of cel is. 
	int* InvCDF;
	float tot_prob, * cum_trans, * max_trans;
	short int CurInterv[MAX_INTERVENTION_TYPES];
	//for radiation model
	//int nn,*NeighboursIndexRad,*InvCDFLookupRad;
	//float TotProbRad,*CumProbRad;
	//for roads
	int road_connection;
	double road_access;
	//for capital city only effect
	int capital_city;
} cell;

typedef struct PLACE {
	int n, mcell;
	unsigned short int ng, treat, control_trig, country;
	unsigned short int close_start_time, close_end_time, treat_end_time;
	unsigned short int* AvailByAge;
#ifdef ABSENTEEISM_PLACE_CLOSURE
	unsigned short int Absent[MAX_ABSENT_TIME], AbsentLastUpdateTime;
#endif
	float loc_x, loc_y;
	int* group_start, * group_size, * members;
} place;

typedef struct INTERVENTION {
	int InterventionType, DoAUThresh, NoStartAfterMin;
	double StartTime, StopTime, MinDuration, RepeatInterval, TimeOffset;
	double StartThresholdHigh, StartThresholdLow, StopThreshold, Level, LevelCellVar, LevelAUVar, LevelCountryVar, ControlParam, LevelClustering;
	unsigned int MaxRounds, MaxResource;
} intervention;

typedef struct ADMINUNIT {
	int id, cnt_id, NI, NIactive[MAX_INTERVENTION_TYPES], n; //added n - number of people in admin unit: ggilani 05/01/15
	int ActiveInterv[MAX_INTERVENTION_TYPES][MAX_INTERVENTIONS_PER_ADUNIT];
	intervention InterventionList[MAX_INTERVENTIONS_PER_ADUNIT];
	char cnt_name[100], ad_name[200];
	int NP, place_close_trig;
	double CaseIsolationTimeStart, HQuarantineTimeStart;
	int currentBeds_inAU, currentBeds_outAU, totalBeds, nextBeds, initialBeds;
	int flagBeds, bedsActive; //added flag to count the number of times to increment beds: ggilani 30/03/17
	double timeBedsAvailable; //bed capacity parameters per admin unit and operation time: ggilani 28/10/14
	double nextTimeToBeds; //

	double propBeds_inAU; //proportion of beds for use by patients inside the admin unit: ggilani 24/11/14
	int* h_queue, nh_queue; //queues for hospitalisation: ggilani 30/10/14
	int caseDetPreFuneralControl;
	double delayDetFuneralControl, initPropSafeFunerals, secPropSafeFunerals, initRelInfSafeFuneral, secRelInfSafeFuneral; //admin unit level funeral controls: ggilani 10/11/14
	double timeToSafeFuneral, startFuneralControl, endFuneralControl; //admin unit level funeral controls: ggilani 10/11/14
	int contactTraceCapacity, contactTraceCapacityInc, contactTraceCaseThreshold, contactTraceCurrent; //number of cases that can be successfully contact traced per admin unit: ggilani 13/11/14
	int contactTraceStartDay, contactTraceThresholdCrossed; //day on which contact tracing starts for an admin unit and whether threshold has been crossed yet or not: ggilani 23/06/15
	int* ct_queue, nct_queue, * ct, nct; //queues for admin unit based contact tracing: ggilani 12/06/17 - including arrays to store people who are actually being contact traced as well as those in the queue for contact tracing
	double* origin_dest; //storage for origin-destination matrix between admin units: ggilani 28/01/15
	double caseDetectRate; //case detection rate: ggilani 03/02/15
	double caseDetectInit;
} adminunit;

typedef struct PARAM {

	int DoBin, DoSaveSnapshot, DoLoadSnapshot, DoTimeSeries;
	double SnapshotSaveTime, SnapshotLoadTime, clP1, clP2,clP3,clP4,clP5,clP6;
	int N /*Population size*/, NH, NR /*Number Realisations*/, NRN /*Number non-extinct realisations*/, NRactual, NRactE, NRactNE, UpdatesPerSample, NumSamples, KernelType, MoveKernelType, AirportKernelType;
	unsigned int BinFileLen;
	int NC, NMC, NMCL, NCP /*Number of populated cells*/, NMCP, ncw, nch, nmcw, nmch, DoUTM_coords, nsp, DoSIS, DoInitEquilib, DoSeasonality;
	int DoAdUnits, NumAdunits, DoAdunitBoundaries, AdunitLevel1Divisor, AdunitLevel1Mask, AdunitBitmapDivisor, CountryDivisor;
	int DoAdunitOutput, DoAdunitBoundaryOutput, DoAdunitDemog, DoCorrectAdunitPop, DoSpecifyPop, DoAdunitIncome, AdunitLevel1Lookup[ADUNIT_LOOKUP_SIZE];
	int DoOutputPlaceDistForOneAdunit, OutputPlaceDistAdunit, OutputDensFile;
	int DoOneGen, OutputAll, BitmapMovieFrame, MaxCorrSample, DoLatent, InfQueuePeakLength, NumThreads, MaxNumThreads;
	int bwidth, bheight, bheight2, bminx, bminy, OutputBitmap, DoSI, DoHeteroDensity, DoPeriodicBoundaries, DoImmuneBitmap, OutputBitmapDetected; //added OutputBitmapDetected - ggilani 04/08/15
	int DoHouseholds, DoPlaces, PlaceTypeNum, Nplace[NUM_PLACE_TYPES], SmallEpidemicCases, DoPlaceGroupTreat;
	int NumInitialInfections[MAX_NUM_SEED_LOCATIONS], DoRandomInitialInfectionLoc, DoAllInitialInfectioninSameLoc;
	int MinPopDensForInitialInfection, NumSeedLocations, MaxPopDensForInitialInfection, InitialInfectionsAdminUnit[MAX_NUM_SEED_LOCATIONS];
	int DoAge, DoSymptoms, LoadSaveNetwork, TargetCountry, RestrictTreatToTarget, IncThreshPop, GlobalIncThreshPop, TargetCountry2, TargetCountry3;
	int OutputNonExtinct, DoInfectiousnessProfile, DoInfectionTree, DoWholeHouseholdImmunity, DoSpatial, DoDeath, UpdatesPerDemogUpdate;
	int DoAirports, Nairports, Air_popscale, DoSchoolFile, DoRealSymptWithdrawal, CaseAbsentChildAgeCutoff, DoEarlyCaseDiagnosis, DoInterventionFile;
	long seed1, seed2, seed3, seed4;
	int ResetSeeds; //added this to reset seeds for each run - ggilani 09/03/17
	long newseed1, newseed2, newseed3, newseed4; //added these to allow for seeds to be reset - ggilani 09/03/17
	int KeepSameSeeds, ResetSeedsPostIntervention, ResetSeedsFlag;
	int TimeToResetSeeds;
	double SpatialBoundingBox[4], LocationInitialInfection[MAX_NUM_SEED_LOCATIONS][2], InitialInfectionsAdminUnitWeight[MAX_NUM_SEED_LOCATIONS], TimeStepsPerDay, TimeStepsPerYear;
	double FalsePositiveRate, FalsePositivePerCapitaIncidence, FalsePositiveAgeRate[NUM_AGE_GROUPS];
	double latent_icdf[CDF_RES + 1], infectious_icdf[CDF_RES + 1], infectious_prof[INFPROF_RES + 1], infectiousness[MAX_INFECTIOUS_STEPS];

	//// I_asymp -> recovery: just use infectious_icdf to preserve non severity analysis. 
	//// Also assume that latent to infectious sojourn time independent of disease severity and same for symptomatic and asymptomatic infection. 
	int DoSeverity; //// Flag
	double MildToRecovery_icdf[CDF_RES + 1], ILIToRecovery_icdf[CDF_RES + 1], SARIToRecovery_icdf[CDF_RES + 1], CriticalToCritRecov_icdf[CDF_RES + 1], CritRecovToRecov_icdf[CDF_RES + 1];
	double ILIToSARI_icdf[CDF_RES + 1], SARIToCritical_icdf[CDF_RES + 1], CriticalToDeath_icdf[CDF_RES + 1];
	/// means for above icdf's. 
	double Mean_MildToRecovery, Mean_ILIToRecovery, Mean_SARIToRecovery, Mean_CriticalToCritRecov, Mean_CritRecovToRecov;
	double Mean_ILIToSARI, Mean_SARIToCritical, Mean_CriticalToDeath;
	double Prop_Mild_ByAge[NUM_AGE_GROUPS], Prop_ILI_ByAge[NUM_AGE_GROUPS], Prop_SARI_ByAge[NUM_AGE_GROUPS], Prop_Critical_ByAge[NUM_AGE_GROUPS];
	double CFR_SARI_ByAge[NUM_AGE_GROUPS],CFR_Critical_ByAge[NUM_AGE_GROUPS];

	double T, TimeStep, SampleTime, SampleStep, BitmapAspectScale;
	int ts_age, TimeStepsPerDayInt;
	double scalex, scaley, width, height, cwidth, cheight, mcwidth, mcheight;
	double KernelShape, KernelScale, KernelP3, KernelP4, KernelDelta, MoveKernelShape, MoveKernelScale, MoveKernelP3, MoveKernelP4;
	double AirportKernelShape, AirportKernelScale, AirportKernelP3, AirportKernelP4, AirportTrafficScale, CellPop2;
	double R0, R0scale, ContactsPerDay, LocalBeta, LatentPeriod, InfectiousPeriod, R0household, R0places, R0spatial;	//// LatentPeriod and InfectiousPeriod are means of icdf's (inverse cumulative distribution functions). 
	double Seasonality[DAYS_PER_YEAR];
	double InfectiousnessSD, R0DensityScalePower, InfectiousnessGamA, InfectiousnessGamR, SuscReductionFactorPerInfection, InfectiousnessBetaA, InfectiousnessBetaB;
	double LethalInfectiousPeriod, ProportionSymptomatic[NUM_AGE_GROUPS], LatentToSymptDelay, SymptInfectiousness;
	double SymptSpatialContactRate, SymptPlaceTypeContactRate[NUM_PLACE_TYPES], InhibitInterAdunitPlaceAssignment[NUM_PLACE_TYPES];
	double SymptPlaceTypeWithdrawalProp[NUM_PLACE_TYPES], CaseAbsenteeismDuration, CaseAbsenteeismDelay;
	double CaseAbsentChildPropAdultCarers;
	double ProportionHospitalised, DiseaseMortality;
	double RelativeTravelRate[NUM_AGE_GROUPS], RelativeSpatialContact[NUM_AGE_GROUPS];
	double AgeSusceptibility[NUM_AGE_GROUPS], AgeInfectiousness[NUM_AGE_GROUPS], InitialImmunity[NUM_AGE_GROUPS];
	double WAIFW_Matrix[NUM_AGE_GROUPS][NUM_AGE_GROUPS];
	double HotelPropLocal, JourneyDurationDistrib[MAX_TRAVEL_TIME], LocalJourneyDurationDistrib[MAX_TRAVEL_TIME];
	double MeanJourneyTime, MeanLocalJourneyTime;
	int InvJourneyDurationDistrib[1025], InvLocalJourneyDurationDistrib[1025];
	double HouseholdTrans, HouseholdSizeDistrib[MAX_ADUNITS][MAX_HOUSEHOLD_SIZE], HouseholdTransPow;
	double HouseholdDenomLookup[MAX_HOUSEHOLD_SIZE];
	double EvolInfectMax, EvolInfectStep, EvolInfectMutationRate;
	int EvolResistNumTypes;
	double EvolResistTreatMutationRate, EvolResistProphMutationRate, EvolResistRelProphSusc[MAX_NUM_RESIST_TYPES], EvolResistRelTreatDeathDrop[MAX_NUM_RESIST_TYPES];
	double EvolResistRelInf[MAX_NUM_RESIST_TYPES], EvolResistRelTreatInfDrop[MAX_NUM_RESIST_TYPES], EvolResistRelTreatSympDrop[MAX_NUM_RESIST_TYPES];
	double EvolResistSeedProp[MAX_NUM_RESIST_TYPES];
	int PlaceTypeAgeMin[NUM_PLACE_TYPES], PlaceTypeAgeMax[NUM_PLACE_TYPES], PlaceTypeMaxAgeRead[NUM_PLACE_TYPES];
	int PlaceTypeAgeMin2[NUM_PLACE_TYPES], PlaceTypeAgeMax2[NUM_PLACE_TYPES];
	int PlaceTypeAgeMin3[NUM_PLACE_TYPES], PlaceTypeAgeMax3[NUM_PLACE_TYPES];
	int PlaceTypeNearestNeighb[NUM_PLACE_TYPES], PlaceTypeDoHousehold[NUM_PLACE_TYPES], PlaceTypeKernelType[NUM_PLACE_TYPES];
	double PlaceTypePropAgeGroup[NUM_PLACE_TYPES], PlaceTypePropAgeGroup2[NUM_PLACE_TYPES];
	double PlaceTypePropAgeGroup3[NUM_PLACE_TYPES], PlaceTypeKernelShape[NUM_PLACE_TYPES], PlaceTypeKernelScale[NUM_PLACE_TYPES];
	double PlaceTypeKernelP3[NUM_PLACE_TYPES], PlaceTypeKernelP4[NUM_PLACE_TYPES], PlaceTypeTrans[NUM_PLACE_TYPES];
	double PlaceTypeMeanSize[NUM_PLACE_TYPES], PlaceTypePropBetweenGroupLinks[NUM_PLACE_TYPES], PlaceTypeSizeSD[NUM_PLACE_TYPES]; //added PlaceTypeSizeSD for lognormal distribution - ggilani 09/02/17
	double PlaceTypeSizePower[NUM_PLACE_TYPES], PlaceTypeSizeOffset[NUM_PLACE_TYPES], PlaceTypeSizeMax[NUM_PLACE_TYPES];
	int PlaceHouseholdOverlap; //added this to allow to specify when/if household members should be assigned to overlapping places - ggilani 10/02/17
	double PlaceTypeGroupSizeParam1[NUM_PLACE_TYPES], PlaceExclusivityMatrix[NUM_PLACE_TYPES * NUM_PLACE_TYPES]; //changed PlaceExclusivityMatrix from [NUM_PLACE_TYPES][NUM_PLACE_TYPES]
	double PropAgeGroup[MAX_ADUNITS][NUM_AGE_GROUPS], PopByAdunit[MAX_ADUNITS][2], MedianIncomeByAdunit[MAX_ADUNITS], MeanAnnualDeathRate;
	double MortalityByAge[MAX_ADUNITS][NUM_AGE_GROUPS * AGE_GROUP_WIDTH], CumulPropDead[MAX_ADUNITS][NUM_AGE_GROUPS * AGE_GROUP_WIDTH + 1], InvLifeExpecDist[MAX_ADUNITS][1001];
	int HouseholdsByAdunit[MAX_ADUNITS], PrivateStockByAdunit[MAX_ADUNITS];
	double IncomeWeibullPower, MedianIncome;
	double PlaceCloseTimeStart, PlaceCloseTimeStart2, PlaceCloseDurationBase, PlaceCloseDuration, PlaceCloseDuration2, PlaceCloseDelayMean, PlaceCloseRadius, PlaceCloseRadius2;
	double PlaceCloseEffect[NUM_PLACE_TYPES], PlaceCloseSpatialRelContact, PlaceCloseHouseholdRelContact;
	double PlaceCloseCasePropThresh, PlaceCloseAdunitPropThresh, PlaceCloseFracIncTrig;
	int DoHolidays, NumHolidays;
	double HolidayEffect[NUM_PLACE_TYPES], HolidayStartTime[DAYS_PER_YEAR], HolidayDuration[DAYS_PER_YEAR];
	double ColourPeriod, BoundingBox[4], BitmapScale, BitmapStartTime, BitmapStopTime;
	double TreatSuscDrop, TreatInfDrop, TreatDeathDrop, TreatSympDrop, TreatDelayMean, TreatTimeStart, TreatPlaceGeogDuration;
	double TreatProphCourseLength, TreatCaseCourseLength, TreatPropRadial, TreatRadius, TreatRadius2, TreatCellIncThresh;
	double TreatPropCases, TreatPropCaseHouseholds, TreatHouseholdsDuration;
	double PrivateTreatDelayMean, PrivateTreatPropCaseHouseholds, PrivateTreatPropCases;
	double TreatPlaceProbCaseId[NUM_PLACE_TYPES], TreatPlaceTotalProp[NUM_PLACE_TYPES];
	double TreatMaxCoursesBase, TreatNewCoursesRate, TreatNewCoursesStartTime, TreatMaxCourses, PropPrivateStockpile;
	double VaccSuscDrop, VaccSuscDrop2, VaccInfDrop, VaccMortDrop, VaccSympDrop, VaccDelayMean, VaccTimeStart, VaccTimeEfficacySwitch, VaccTimeStartGeo;
	double VaccTimeToEfficacy, VaccProp, VaccRadius, VaccRadius2, VaccMinRadius, VaccMinRadius2, VaccPropCaseHouseholds, VaccHouseholdsDuration, VaccMaxCoursesBase;
	double VaccNewCoursesRate, VaccNewCoursesStartTime, VaccMaxCourses, VaccNewCoursesEndTime, VaccEfficacyDecay, VaccCellIncThresh, VaccCampaignInterval, VaccCoverageIncreasePeriod;
	double VaccTimeToEfficacyThirdVaccRing;
	int DoRingVaccination, NVaccRings, NVaccRingsActive, MinVaccAge, VaccDosePerDay; //added this for ring vaccination - ggilani 15/02/2017
	int NPropRingVacc, CurrIndPropRingVacc; //added for updated ring vaccination code - gilani 29/05/19
	double PropRingVacc, TimeToIncVaccRing; //added this for ring vaccination - ggilani 15/02/2017
	double ChangePointPropRingVacc[MAX_CHANGE_POINTS], ListPropRingVacc[MAX_CHANGE_POINTS]; //added this for ring vaccination - ggilani 29/05/19
	int VaccRingScale, VaccCaseScale; //added to control vaccination from commandline
	double VaccPropScale, VaccDelayScale, VaccEffTimeScale; //added to control vaccination from commandline
	double PreAlertControlPropCasesId, PostAlertControlPropCasesId, ControlPropCasesId;
	double MoveRestrRadius, MoveRestrRadius2;
	double MoveDelayMean, MoveRestrEffect, MoveRestrDuration, MoveRestrTimeStart;
	double AirportCloseTimeStart, AirportCloseDuration, AirportCloseEffectiveness;
	double CaseIsolationTimeStart, CaseIsolationDuration, CaseIsolationEffectiveness, CaseIsolationHouseEffectiveness;
	double CaseIsolationDelay, CaseIsolationPolicyDuration, CaseIsolationProp;
	double HQuarantineTimeStart, HQuarantineHouseDelay, HQuarantineHouseDuration, HQuarantinePolicyDuration, HQuarantinePropIndivCompliant;
	double HQuarantinePropHouseCompliant, HQuarantinePlaceEffect[NUM_PLACE_TYPES], HQuarantineSpatialEffect, HQuarantineHouseEffect;
	double SocDistTimeStart, SocDistDuration, SocDistHouseholdEffect, SocDistPlaceEffect[NUM_PLACE_TYPES], SocDistSpatialEffect;
	double ESocDistHouseholdEffect, ESocDistPlaceEffect[NUM_PLACE_TYPES], ESocDistSpatialEffect, ESocProportionCompliant[NUM_AGE_GROUPS];
	double SocDistRadius, SocDistRadius2;
	double KeyWorkerProphTimeStart, KeyWorkerProphDuration, KeyWorkerPropInKeyPlaces[NUM_PLACE_TYPES], KeyWorkerHouseProp;
	double KeyWorkerProphRenewalDuration, KeyWorkerProphRadius, KeyWorkerProphRadius2;
	double TreatTimeStartBase, VaccTimeStartBase, MoveRestrTimeStartBase, PlaceCloseTimeStartBase, PlaceCloseTimeStartBase2;
	double AirportCloseTimeStartBase, HQuarantineTimeStartBase, CaseIsolationTimeStartBase, SocDistTimeStartBase, KeyWorkerProphTimeStartBase;
	double InfectionImportRate1, InfectionImportRate2, InfectionImportChangeTime, ImportInfectionTimeProfile[MAX_DUR_IMPORT_PROFILE];
	int PreControlClusterIdCaseThreshold, DoPerCapitaTriggers, DoGlobalTriggers, DoAdminTriggers, DoICUTriggers, MoveRestrCellIncThresh,DoHQretrigger;
	int PlaceCloseCellIncThresh, TriggersSamplingInterval, PlaceCloseIndepThresh, SocDistCellIncThresh, VaccPriorityGroupAge[2];
	int PlaceCloseCellIncStopThresh, SocDistCellIncStopThresh;
	int PlaceCloseAdunitPlaceTypes[NUM_PLACE_TYPES], DoPlaceCloseOnceOnly, DoSocDistOnceOnly, DoMoveRestrOnceOnly, DoKeyWorkerProphOnceOnly, PrivateStockpileOrderByIncome;
	int VaccMaxRounds, VaccByAdminUnit, VaccAdminUnitDivisor, TreatByAdminUnit, TreatAdminUnitDivisor, MoveRestrByAdminUnit, MoveRestrAdminUnitDivisor, PlaceCloseByAdminUnit, PlaceCloseAdminUnitDivisor;
	int KeyWorkerProphCellIncThresh, KeyWorkerPopNum, KeyWorkerPlaceNum[NUM_PLACE_TYPES], KeyWorkerNum, KeyWorkerIncHouseNum;
	int DoBlanketMoveRestr, PlaceCloseIncTrig, TreatMaxCoursesPerCase, DoImportsViaAirports, DoMassVacc, DurImportTimeProfile;
	unsigned short int usHQuarantineHouseDuration, usVaccTimeToEfficacy, usVaccTimeEfficacySwitch, usVaccTimeToEfficacyThirdRing;
	unsigned short int usCaseIsolationDuration, usCaseIsolationDelay, usCaseAbsenteeismDuration, usCaseAbsenteeismDelay;

	double RoutineImmunisationStartTime, RoutineImmunisationEffectiveCoverage, RoutineImmunisationMinAge, RoutineImmunisationMaxAge, RoutineCoverageNonDistrCountry;
	double SIAMinAge, SIAMaxAge, SIAStartTime, SIARepeatInterval, SIAEffectiveCoverage, SIADuration, VaccPhialLifetime;
	unsigned short int usRoutineImmunisationStartTime, usSIAStartTime, usRoutineImmunisationMaxAge, usRoutineImmunisationMinAge;
	unsigned short int usSIAMaxAge, usSIAMinAge, usSIARepeatInterval, usSIADuration;
	int DoDistributionVaccination, DistribNetCountry, SIADoAllCountries, VaccDosesPerPhial;
	//Added DoRecordInfEvents and MaxInfEvents in order to give the user a choice as to whether to output infection events as a line list: ggilani - 10/10/14
	int DoRecordInfEvents, MaxInfEvents, RecordInfEventsPerRun;
	double KernelPowerScale, KernelOffsetScale;
	int LimitNumInfections, MaxNumInfections;
	//Added parameters to incorporate time to death/recovery functions: ggilani - 22/10/14
	int DoMortality;
	double RecoveryAmp, RecoveryShape, RecoveryScale, RecoveryProb[RECOVERY_RES];
	//Parameters for funeral transmission
	int DoFuneralTransmission, DoFuneralByAdUnit, CasesDetPreFuneralControl;
	double FuneralControlStartTime, FuneralControlEndTime, DelayDetectFuneralControl;
	double FuneralTransmissionDuration, RelativeInfectiousnessFuneral, InitRelInfSafeFuneral, SecRelInfSafeFuneral, InitProportionSafeFuneral, SecProportionSafeFuneral, TimeToSafeFuneral;
	//Parameters for hospitalisation/treatment centres: ggilani - 28/10/2014
	int DoHospitalisation, DoHospByAdUnit, DoReactHospBeds;
	double HospitalisationTime, hospital_icdf[CDF_RES + 1], RelativeInfectiousnessHospitalised, HospWaitingTime, HospitalisationTime_contactTrace; //added time to hospitalisation for a hospitalised case - ggilani 05/07/17
	int CurrIndMeanTimeToHosp, CurrIndHospBeds, CurrIndMeanTimeToHospCT;
	int NHospBeds, NMeanTimeToHosp, NMeanTimeToHospCT, HospBeds[MAX_CHANGE_POINTS];
	double ChangePointMeanTimeToHosp[MAX_CHANGE_POINTS], ChangePointMeanTimeToHospCT[MAX_CHANGE_POINTS], ChangePointHospBeds[MAX_CHANGE_POINTS], MeanTimeToHosp[MAX_CHANGE_POINTS], MeanTimeToHospCT[MAX_CHANGE_POINTS];
	int InitCasesToBeds, InitNumBeds, IntervalCasesToBeds, SubNumBeds; // added these variable for reactive provisioning of beds: ggilani 30/03/2017
	double InitDelayToBeds, SubDelayToBeds, StartTimeReactiveBeds; //added these variable for reactive provisioning of beds: ggilani 30/03/2017
	//Pseudo contact tracing parameters: ggilani 13/11/14
	int DoContactTracing, contactTraceCapacity, contactTraceCaseThreshold, contactTraceCaseThresholdInc, DoNewContactTracing; //added DoNewContactTracing - 06/06/17
	double R0contract_trace, contactTraceDuration, propContactTraced;
	int CT_scale1, CT_scale2; //scaling factors for contact tracing capacity
	int CT_thresh1, CT_thresh2; //scaling for different contact tracing thresholds
	int CTinc_scale1, CTinc_scale2; //scaling for increased capacity
	int GlobalContractTracingStarted, GlobalContractTracingIncreased; //flags to help with contact tracing
	double PropCrossBorderInf; //reduction in transmission probability if infector and potential infectee aren't in the same country: ggilani - 09/12/14
	double BC_scale; //scaling factor for cross border contact: to allow it to be input on the command line - ggilani 17/12/14
	//transmission dependent on total number of cases/current number of infectious
	int DoPrevDependTrans, DoPrevDepTransTotalCases, DoPrevDepTransCurrInf;
	double PrevDependTransThresh, PrevDependRelativeSusc;
	//origin destination matrix on or off
	int DoOriginDestinationMatrix; //added: ggilani 28/01/15
	//case detection parameters: 03/02/15 ggilani
	int DoCaseDetection, DoCaseDetectionAdunit, DoClusterCaseDetection;
	double CaseDetectionRate;
	double RR1, RR2, RR3; //reporting rate scalings for Guinea, Liberia, Sierra Leone
	double RRAlt; //**separate reporting rate for individual admin units** - ggilani 18/06/2015
	int AltAU1, AltAU2; //**adunit codes that alternative reporting rate is used for** - ggilani 18/06/2015
	//things added for radiation model
	int DoRadiationMobility;
	double KernelRadiusMax, KernelRadiusMax2, PropWithinCellTransmission;
	//variables relevant to reading in and using road networks: ggilani 12/11/15
	int DoRoadNetwork, MaxRoadType, DoRoadDistanceEffect, DoRoadPopEffect, MaxRoadNeighbour;
	double RoadAccessDistance, RoadAccessPop;
	//for capital city effect: ggilani - 26/02/15
	int DoCapitalCityEffect, DoCapitalCityDistanceEffect, DoCapitalCityPopEffect, DoCapitalCityAddEffect;
	int CapitalCityAdunit, CapitalCityAdunit2, CapitalCityAdunit3;
	double CapitalCityDistanceEffect, CapitalCityPopEffect, CapitalCityAddEffect;
	//relative susceptilbility of Guinea - added to scale down R0 in Guinea by making people there less susceptible: ggilani 23/06/2015
	double RelativeSusceptibilityGuinea, RelativeSusceptibilityLiberia;
	// couple of parameters to allow use to specify where a case is imported to: ggilani 01/07/2015
	int DoImportToSpecLocation; // specify whether to import to a set location or not
	double ImportLocation[2]; //coordinates to import cases to
	int DoUpdateCaseDetection;
	double TimeToUpdateCaseDetection, UpdatedCaseDetectionRate;

	int DoInterruptIntervention, NDaysInterrupt, DaysInterruptIntervention[MAX_CHANGE_POINTS], InterruptIntervention; //extra parameters to model interruptions of intervention: ggilani 08/01/20
} param;

typedef struct BIN_FILE {
	double x, y, pop;
	int cnt, ad;
} bin_file;

typedef struct BITMAP_HEADER {
	unsigned int filesize;
	unsigned int spare;
	unsigned int boffset;
	unsigned int headersize;
	unsigned int width, height;
	unsigned int PlanesAndBitspp;
	unsigned int compr;
	unsigned int imagesize;
	unsigned int hres, vres;
	unsigned int colours, impcol;
	unsigned char palette[256][4];
} bitmap_header;


