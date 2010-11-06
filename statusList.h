#pragma once
#define NULL 0
//transition defines
#define TRANSITION_OK 0
#define TRANSITION_BAD_ARGS -1
#define TRANSITION_UNCLEAR_PATH -2
#define TRANSITION_SIM_END 1
//place defines
#define PLACE_OK 0
#define PLACE_BAD_ARGS -1
#define PLACE_SIM_END 1
//directed arc defines
#define DIRECTEDARC_OK 0
#define DIRECTEDARC_NULL_ARG -1
//directed arc modes
#define DIRECTEDARC_INHIB 1
#define DIRECTEDARC_DEFAULT 0
//base defines
#define BASE_OK 0
#define BASE_NULL_ARG -1
//baseData defines
#define TRANSITION_WAIT 0
#define TRANSITION_PROBAB 1
#define TRANSITION_PRIO 2
#define TRANSITION_DEFAULT -1
#define TRANSITION_NOPARAM 5
#define BASE_DEFAULT 3
#define PLACE_CAP 4
//model error defines
#define RUNTIME_TRANSITION_CRASH -1
#define RUNTIME_PLACE_CRASH -2
#define RUNTIME_PLACE_CRASH_WAIT - 3
#define PLACE_UNKNOWN_ERR -4
//action codes
#define ACTION_TAKE	0
#define ACTION_RETURN 1
//runtime codes
#define ACTION_DEFAULT 0
#define PLACE_EMPTY 1
#define PLACE_TAKEN 2
#define PLACE_RETURNED 3
#define PLACE_SUCC 4
#define PLACE_FAIL 5