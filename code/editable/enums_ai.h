
#include "enumlist.h"

#ifndef _ENUMS_AI_INC
#define _ENUMS_AI_INC

// -- AI state enum definitions
// -----------------------------
ENUM_START(AI_START_STATE)
	ENUM_AUTO(AI_IDLE)
	ENUM_AUTO(AI_SEARCHING)
	ENUM_AUTO(AI_CHASING)
	ENUM_AUTO(AI_JOIN_FORMATION)
	ENUM_AUTO(AI_IN_FORMATION)
	ENUM_AUTO(AI_CUTSCENE)
ENUM_END()


// -- Extension of the action, giving a concept of using state
// -----------------------------
ENUM_STARTEX_PUBLISH_AS(AI_ACTION_USING, ENUM_XML|ENUM_LUA, USING_WEAPON )
	ENUM_AUTO(AU_NOTHING)			// Nothing, the entity has it's hands free
	ENUM_AUTO(AU_RSWORD)			// Sword in right hand
	ENUM_AUTO(AU_RSWORD_LSHIELD)	// Sword in right hand, Shield in left
	ENUM_AUTO(AU_RCROSSBOW)			// Crossbow right hand
	ENUM_AUTO(AU_RLAXE)				// 1 Axe in both left and right hands
	ENUM_AUTO(AU_RBALL_LCAHIN)		// Ball and chain
ENUM_END()


// Formation types
//------------------------------------------------------------------------------------------

ENUM_STARTEX_PUBLISH_AS(AI_FORMATION_TYPE, ENUM_XML|ENUM_LUA, FORMATION_TYPE )
	ENUM_SET_AS(AFT_CIRCLE, 0,		CIRCLE)
	ENUM_AUTO_AS(AFT_LINE,			LINE)
	ENUM_AUTO_AS(AFT_MAPPED,		MAPPED)
	ENUM_AUTO_AS(AFT_ARBITRARY,		ARBITRARY)
	ENUM_AUTO_AS(AFT_SET,			SET)
	ENUM_AUTO_AS(AFT_ARMY,			ARMY)
ENUM_END()


// Attack Type Enumerations for Lua
// ---------------------------------
ENUM_STARTEX_PUBLISH_AS(AI_ATTACK_TYPE, ENUM_XML|ENUM_LUA, ATT)
	ENUM_SET_AS(AAT_NONE, 0,		NONE)
	ENUM_AUTO_AS(AAT_PAUSE,			PAUSE)			
	ENUM_AUTO_AS(AAT_SPEED_FAST,	SPEED_FAST)
	ENUM_AUTO_AS(AAT_SPEED_MEDIUM,	SPEED_MEDIUM)
	ENUM_AUTO_AS(AAT_SPEED_GRAB,	SPEED_GRAB)
	ENUM_AUTO_AS(AAT_POWER_FAST,	POWER_FAST)
	ENUM_AUTO_AS(AAT_POWER_MEDIUM,	POWER_MEDIUM)
	ENUM_AUTO_AS(AAT_POWER_GRAB,	POWER_GRAB)
	ENUM_AUTO_AS(AAT_RANGE_FAST,	RANGE_FAST)
	ENUM_AUTO_AS(AAT_RANGE_MEDIUM,	RANGE_MEDIUM)
	ENUM_AUTO_AS(AAT_RANGE_GRAB,	RANGE_GRAB)
	ENUM_AUTO_AS(AAT_ACTION,		ACTION)
	ENUM_AUTO_AS(AAT_EVADE,			EVADE)
	ENUM_AUTO_AS(AAT_SPEED_BLOCK,	SPEED_BLOCK)
	ENUM_AUTO_AS(AAT_POWER_BLOCK,	POWER_BLOCK)
	ENUM_AUTO_AS(AAT_RANGE_BLOCK,	RANGE_BLOCK)
	ENUM_AUTO_AS(AAT_GRAB_BLOCK,	GRAB_BLOCK)
	ENUM_AUTO_AS(AAT_EVADE_LEFT,	EVADE_LEFT)
	ENUM_AUTO_AS(AAT_EVADE_RIGHT,	EVADE_RIGHT)
	ENUM_AUTO_AS(AAT_EVADE_FORWARD,	EVADE_FORWARD)
	ENUM_AUTO_AS(AAT_EVADE_BACK,	EVADE_BACK)
							
	// Non moves			
	ENUM_AUTO_AS(AAT_RET_FORMATION,		RET_FORMATION)
	ENUM_AUTO_AS(AAT_LUA_CALLBACK,		LUA_CALLBACK)
	ENUM_AUTO_AS(AAT_MSG_FORMATION,		MSG_FORMATION)
	ENUM_AUTO_AS(AAT_PLAY_ANIM,			PLAY_ANIM)
	ENUM_AUTO_AS(AAT_DIRECT_ATTACK,		DIRECT_ATTACK)

	// Flush flags
	ENUM_AUTO_AS(AAT_QUEUE_FLUSH,		QUEUE_FLUSH)
	ENUM_AUTO_AS(AAT_COMBAT_FLUSH,		COMBAT_FLUSH)
	
	// Flags 
	ENUM_SET_AS(AAT_FORCE_LOCKON, 0x10000, FORCE_LOCKON)
ENUM_END()

#define AAT_COUNT 20	      //Defined outside the enum, then compiler won't let anyone use these in place of an enum
#define AAT_LAST  AAT_COUNT-1 // Why doesn't C++ have a sizeof operator for enums!
#define AAT_FIRST 1


// Attack Response Enumerations for Lua
// -------------------------------------
ENUM_STARTEX_PUBLISH_AS(AI_ATTACK_RESPONSE, ENUM_LUA, RESPONSE)
	ENUM_SET_AS(AAR_NONE, 0,		NONE)
	ENUM_SET_AS(AAR_DEFLECTED, 2,	DEFLECTED)
	ENUM_AUTO_AS(AAR_RECOILED,		RECOILED)
	ENUM_AUTO_AS(AAR_STAGGERED,		STAGGERED)
	ENUM_AUTO_AS(AAR_KOED,			KOED)
	ENUM_AUTO_AS(AAR_HELD,			HELD)
	ENUM_AUTO_AS(AAR_DEAD,			DEAD)
ENUM_END()

// Movement Controller Modifier Enumeration
// These are used to set the appropriate walking/strafing controllers.
// ----------------------------------------
ENUM_STARTEX_PUBLISH_AS(AI_MOVEMENT_CONTROLLER_MODIFIER, ENUM_LUA, AMCM)	//Feel free to rename this!
	ENUM_AUTO_AS(AMCM_NONE,		NONE)
	ENUM_AUTO_AS(AMCM_CROSSBOW,	CROSSBOW)
	ENUM_AUTO_AS(AMCM_BAZOOKA,	BAZOOKA)
	//Add here as needed.
ENUM_END()


// Weapon-pickup-type enumeration.
// These are used to specify a pickup-target when retrieving a weapon.
// ----------------------------------------
ENUM_STARTEX_PUBLISH_AS(WEAPON_PICKUP_TYPE, ENUM_LUA, WPT)
	ENUM_AUTO_AS(WPT_NONE,		NONE)
	ENUM_AUTO_AS(WPT_CROSSBOW,	CROSSBOW)
	ENUM_AUTO_AS(WPT_BAZOOKA,	BAZOOKA)
ENUM_END()


// Navigation Flags
// ---------------------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_NAVIGATION_FLAGS, ENUM_LUA, NF)
	ENUM_SET_AS(NF_NO_MOVEMENT,			0,				DISABLE_MOVEMENT)
	ENUM_SET_AS(NF_D_OBSTACLE,			1	<< 0,		DYNAMIC_OBSTACLE)
	ENUM_SET_AS(NF_S_OBSTACLE,			1	<< 1,		STATIC_OBSTACLE)
	ENUM_SET_AS(NF_AI_OBSTACLE,			1	<< 2,		AIBOT_OBSTACLE)
	ENUM_SET_AS(NF_FOLLOW_LEADER,		1	<< 3,		FOLLOW_LEADER)
	ENUM_SET_AS(NF_FOLLOW_ENTITY,		1	<< 4,		FOLLOW_ENTITY)
	ENUM_SET_AS(NF_SEEK,				1	<< 5,		SEEK)
	ENUM_SET_AS(NF_FLEE,				1	<< 6,		FLEE)
	ENUM_SET_AS(NF_ARRIVE,				1	<< 7,		ARRIVE)
	ENUM_SET_AS(NF_WANDER,				1	<< 8,		WANDER)
	ENUM_SET_AS(NF_CHASE_ENEMY,			1	<< 9,		CHASE_ENEMY)
	ENUM_SET_AS(NF_FOLLOW_PATH,			1	<< 10,		FOLLOW_PATH)
	ENUM_SET_AS(NF_FOLLOW_PATROL_PATH,	1	<< 11,		FOLLOW_PATROL_PATH)
	ENUM_SET_AS(NF_FLOCK,				1	<< 12,		FLOCK)
	ENUM_SET_AS(NF_TO_COMBAT_POINT,		1	<< 13,		TO_COMBAT_POINT)
	ENUM_SET_AS(NF_ARRIVE_AT_POINT,		1	<< 14,		ARRIVE_AT_POINT)
	ENUM_SET_AS(NF_ARRIVE_AT_LOCTR_NODE,1	<< 15,		ARRIVE_AT_LOCATOR_POINT)
	ENUM_SET_AS(NF_CHASE_MOVING_ENTITY,	1	<< 16,		CHASE_MOVING_ENTITY)
	ENUM_SET_AS(NF_FOLLOW_PATH_COVER,	1	<< 17,		FOLLOW_PATH_COVER)
	ENUM_SET_AS(NF_FOLLOW_PATH_DYNCOVER,1	<< 18,		FOLLOW_PATH_DYNAMIC_COVER)
	ENUM_SET_AS(NF_GO_AROUND_VOLUMES,	1	<< 19,		GO_AROUND_VOLUMES)
	ENUM_SET_AS(NF_DEFAULT,				1	<< 20,		DEFAULT)
ENUM_END()

// Navigation Weight Index
// ---------------------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_NAVIGATION_WEIGHT_INDEX, ENUM_LUA, NWI)
	ENUM_SET_AS(NWI_D_OBSTACLE,			0, DYNAMIC_OBSTACLE)
	ENUM_AUTO_AS(NWI_S_OBSTACLE,		STATIC_OBSTACLE)
	ENUM_AUTO_AS(NWI_AI_OBSTACLE,		AIBOT_OBSTACLE)
	ENUM_AUTO_AS(NWI_FOLLOW_LEADER,		FOLLOW_LEADER)
	ENUM_AUTO_AS(NWI_FOLLOW_ENTITY,		FOLLOW_ENTITY)	
	ENUM_AUTO_AS(NWI_SEEK,				SEEK)
	ENUM_AUTO_AS(NWI_FLEE,				FLEE)
	ENUM_AUTO_AS(NWI_ARRIVE,			ARRIVE)
	ENUM_AUTO_AS(NWI_WANDER,			WANDER)
	ENUM_AUTO_AS(NWI_CHASE_ENEMY,		CHASE_ENEMY)
	ENUM_AUTO_AS(NWI_FOLLOW_PATH,		FOLLOW_PATH)
	ENUM_AUTO_AS(NWI_FOLLOW_PATROL_PATH,FOLLOW_PATROL_PATH)
	ENUM_AUTO_AS(NWI_FLOCK,				FLOCK)
	ENUM_AUTO_AS(NWI_TO_COMBAT_POINT,	TO_COMBAT_POINT)
	ENUM_AUTO_AS(NWI_ARRIVE_AT_POINT,	ARRIVE_AT_POINT)
	ENUM_AUTO_AS(NWI_ARRIVE_AT_LOCTR_NODE,	ARRIVE_AT_LOCATOR_POINT)
	ENUM_AUTO_AS(NWI_GO_AROUND_VOLUMES,	GO_AROUND_VOLUMES)
	ENUM_AUTO_AS(NWI_LAST_INDEX,		LAST_INDEX)
ENUM_END()

// Navigation Intentions
// ---------------------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_NAVIGATION_INTENTIONS_INDEX, ENUM_LUA, NAVINT)
	ENUM_SET_AS(NAVINT_NONE,						0, NONE)
	ENUM_AUTO_AS(NAVINT_IDLE,						IDLE)
	ENUM_AUTO_AS(NAVINT_INITIAL_REACTION,			INITIAL_REACTION)
	ENUM_AUTO_AS(NAVINT_FOLLOWPATHTONODE,			FOLLOW_PATH_TO_NODE) //GO_TO_NODE)
	ENUM_AUTO_AS(NAVINT_FOLLOWPATHCOVER_TO_ENEMY,	FOLLOW_PATH_COVER)
	ENUM_AUTO_AS(NAVINT_FOLLOWPATHCOVER_TO_NODE,	FOLLOW_PATH_COVER_TO_NODE)
	ENUM_AUTO_AS(NAVINT_FOLLOWPATHCOVER_INVESTIGATE,FOLLOW_PATH_COVER_INVESTIGATE)
	ENUM_AUTO_AS(NAVINT_FOLLOWPATHCOVER_MINMAX,		FOLLOW_PATH_COVER_MINMAX)
	ENUM_AUTO_AS(NAVINT_GOTOENTITY,					GO_TO_ENTITY)
	ENUM_AUTO_AS(NAVINT_GOTOLOCATORNODE,			GO_TO_LOCATOR_NODE) // GO_TO_LOCATION
	ENUM_AUTO_AS(NAVINT_ATTACK_ENTITY,				ATTACK_ENTITY)
	ENUM_AUTO_AS(NAVINT_FOLLOW_ENTITY,				FOLLOW_ENTITY)
	ENUM_AUTO_AS(NAVINT_INVESTIGATE,				INVESTIGATE)
	ENUM_AUTO_AS(NAVINT_PATROL,						PATROL)
	ENUM_AUTO_AS(NAVINT_FACE_ENTITY,				FACE_ENTITY)
	ENUM_AUTO_AS(NAVINT_WHACKAMOLE,					WHACKAMOLE)
	ENUM_AUTO_AS(NAVINT_USE_OBJECT,					USE_OBJECT)
	ENUM_AUTO_AS(NAVINT_PLAY_ANIM,					PLAY_ANIM)
	ENUM_AUTO_AS(NAVINT_GO_AROUND_VOLUMES,			GO_AROUND_VOLUMES)
	ENUM_AUTO_AS(NAVINT_USE_CANNON,					USE_CANNON)
	ENUM_AUTO_AS(NAVINT_LAST_INDEX,					LAST_INDEX)
ENUM_END()

// Navigation Parameters
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_NAVIGATION_PARAMETERS, ENUM_LUA, NAVPAR)
	ENUM_SET_AS(MP_MAX_SPEED,					0, MAX_SPEED)
	ENUM_AUTO_AS(MP_WALK_SPEED,					WALK_SPEED)
	ENUM_AUTO_AS(MP_CHASE_SPEED,				CHASE_SPEED)
	ENUM_AUTO_AS(MP_APPROACH_SPEED,				APPROACH_SPEED)
	ENUM_AUTO_AS(MP_FACE_DIR_SPEED,				FACE_DIR_SPEED)
	ENUM_AUTO_AS(MP_PANIC_DST_SQR,				PANIC_DST_SQR)
	ENUM_AUTO_AS(MP_AI_AVOID_RADIUS,			AI_AVOID_RADIUS)
	ENUM_AUTO_AS(MP_AI_AVOID_RADIUS_STD,		AI_AVOID_RADIUS_STD)
	ENUM_AUTO_AS(MP_AI_AVOID_RADIUS_COMBAT,		AI_AVOID_RADIUS_COMBAT)
	ENUM_AUTO_AS(MP_AI_FLOCKING_RADIUS,			FLOCKING_RADIUS)
	ENUM_AUTO_AS(MP_RESIDENTE_EVIL,				RESIDENT_RADIUS)
	ENUM_AUTO_AS(MP_ATTACK_RANGE,				ATTACK_RANGE)
	ENUM_AUTO_AS(MP_ATTACK_RANGE_SQR,			ATTACK_RANGE_SQR)
	ENUM_AUTO_AS(MP_ATTACK_POINT_RADIUS_SQR,	ATTACK_POINT_RADIUS_SQR)
	ENUM_AUTO_AS(MP_MIN_WALL_DET_RADIUS,		MIN_WALL_DET_RADIUS)
	ENUM_AUTO_AS(MP_MIN_DYN_OBST_DET_RADIUS,	MIN_DYN_OBST_DET_RADIUS)
	ENUM_AUTO_AS(MP_SIDE_DETECTION_LENGTH,		SIDE_DETECTION_LENGTH)
	ENUM_AUTO_AS(MP_FOLLOW_ENTITY_RADIUS,		FOLLOW_ENTITY_RADIUS)
	ENUM_AUTO_AS(MP_GO_TO_ENTITY_RADIUS,		GO_TO_ENTITY_RADIUS)
	ENUM_AUTO_AS(MP_FPC_WIDTH_PERCENTAGE,		FPC_WIDTH_PERCENTAGE)
	ENUM_AUTO_AS(MP_FPC_MAX_RECOVER_TIME_AFTER_PNF,		FPC_MAX_RECOVER_TIME_AFTER_PNF)
	ENUM_AUTO_AS(MP_DIVE_COOLING_TIME,			DIVE_COOLING_TIME)
	ENUM_AUTO_AS(MP_DIVE_CONE_LENGTH,			DIVE_CONE_LENGTH)
	ENUM_AUTO_AS(MP_DIVE_CONE_HALFRADIUS,		DIVE_CONE_HALFRADIUS)
	ENUM_AUTO_AS(MP_DIVE_PROBABILITY,			DIVE_PROBABILITY)
	ENUM_AUTO_AS(MP_DIVE_PANIC_PROBABILITY,		DIVE_PANIC_PROBABILITY)
	ENUM_AUTO_AS(MP_DIVE_AFTERTOUCH_PROBABILITY,DIVE_AFTERTOUCH_PROBABILITY)
	ENUM_AUTO_AS(MP_DIVE_AFTERTOUCH_PANIC_PROBABILITY,		DIVE_AFTERTOUCH_PANIC_PROBABILITY)
	ENUM_AUTO_AS(MP_COVER_TIME,					COVER_TIME)
	ENUM_AUTO_AS(MP_IN_COVER_PEEK_PROBABILITY,	IN_COVER_PEEK_PROBABILITY)
	
ENUM_END()

// Vision Parameters
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_VISION_PARAMETERS, ENUM_LUA, VISPAR)
	ENUM_SET_AS(VP_SEE_ALL_IN_RANGE,		0, SEE_ALL_IN_RANGE)
	ENUM_AUTO_AS(VP_CLOSE_DISTANCE_SQR,		CLOSE_DISTANCE_SQR)
	ENUM_AUTO_AS(VP_MID_DISTANCE_SQR,		MID_DISTANCE_SQR)
	ENUM_AUTO_AS(VP_MAX_DISTANCE_SQR,		MAX_DISTANCE_SQR)
	ENUM_AUTO_AS(VP_INNER_RADIUS_SQR,		INNER_RADIUS_SQR)
	ENUM_AUTO_AS(VP_HALF_CLOSE_DIST_ANGLE,	HALF_CLOSE_DIST_ANGLE)
	ENUM_AUTO_AS(VP_HALF_MID_DIST_ANGLE,	HALF_MID_DIST_ANGLE)
	ENUM_AUTO_AS(VP_HALF_MAX_DIST_ANGLE,	HALF_MAX_DIST_ANGLE)
	ENUM_AUTO_AS(VP_EYES_HEIGHT,			EYES_HEIGHT)
	ENUM_AUTO_AS(VP_SHOOTING_ANGLE,			SHOOTING_ANGLE)
	ENUM_AUTO_AS(VP_SHOOTING_RADIUS,		SHOOTING_RADIUS)	
ENUM_END()

// Ranged Targeting Params
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_RANGEDTARGETING_PARAMETERS, ENUM_LUA, RANGEDTARGETPAR)
	ENUM_SET_AS(RTP_MAX_EXPANSION,				0, MAX_EXPANSION)
	ENUM_AUTO_AS(RTP_MAX_EXPANSION_DISTANCE,	MAX_EXPANSION_DISTANCE)
	ENUM_AUTO_AS(RTP_MIN_CONTRACTION,			MIN_CONTRACTION)
	ENUM_AUTO_AS(RTP_CONTRACTION_COOLDOWN,		CONTRACTION_COOLDOWN)
	ENUM_AUTO_AS(RTP_CONTRACTION_TIME,			CONTRACTION_TIME)
	ENUM_AUTO_AS(RTP_MOVINGEXPANSION_TIME,		MOVINGEXPANSION_TIME)
	ENUM_AUTO_AS(RTP_STOPPINGEXPANSION_MINTIME,	STOPPINGEXPANSION_MINTIME)
	ENUM_AUTO_AS(RTP_NUM_PARAMS,				NUM_PARAMS)
ENUM_END()

// Hearing Parameters
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_HEARING_PARAMETERS, ENUM_LUA,HEARPAR)
	ENUM_SET_AS(HP_IS_DEAF,				0, IS_DEAF)
	ENUM_AUTO_AS(HP_VOLUME_THRESHOLD,	VOLUME_THRESHOLD)
ENUM_END()

// Cover Point Parameters
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_COVER_POINT_PARAMETERS, ENUM_LUA,COVER)
	ENUM_SET_AS(COVER_DEFAULT,	0, DEFAULT)
	ENUM_AUTO_AS(COVER_NONE,	NEVER)
	ENUM_AUTO_AS(COVER_SELDOM,	SELDOM)
	ENUM_AUTO_AS(COVER_OFTEN,	OFTEN)
	ENUM_AUTO_AS(COVER_ALWAYS,	ALWAYS)
ENUM_END()

// Ranged Combat Parameters
// ---------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_RANGED_PARAMETERS, ENUM_LUA,RANGEDPAR)
	ENUM_SET_AS(RANGED_TIME_BETWEEN_SHOTS,	0,	TIME_BETWEEN_SHOTS)
	ENUM_AUTO_AS(RANGED_CONSECUTIVE_SHOTS,		CONSECUTIVE_SHOTS)
	ENUM_AUTO_AS(RANGED_MISS_RADIUS,			MISS_RADIUS)
	ENUM_AUTO_AS(RANGED_SHOOTING_ACCURACY,		SHOOTING_ACCURACY)
	ENUM_AUTO_AS(RANGED_ALWAYS_MISS,			ALWAYS_MISS)
	ENUM_AUTO_AS(RANGED_MAX_HIDDING_TIME,		MAX_HIDDING_TIME)
	ENUM_AUTO_AS(RANGED_MIN_HIDDING_TIME,		MIN_HIDDING_TIME)
	ENUM_AUTO_AS(RANGED_MIN_AIMING_TIME,		MIN_AIMING_TIME)
	ENUM_AUTO_AS(RANGED_MAX_AIMING_TIME,		MAX_AIMING_TIME)
	ENUM_AUTO_AS(RANGED_MIN_RANGE_RADIUS,		MIN_RANGE_RADIUS)
	ENUM_AUTO_AS(RANGED_MAX_RANGE_RADIUS,		MAX_RANGE_RADIUS)
ENUM_END()

// AI Boolean Params
// ------------------
ENUM_STARTEX_PUBLISH_AS(ENUM_BOOL_AI_PARAMS, ENUM_LUA,AIBOOL)
	ENUM_SET_AS(AIBOOL_IDLE_PLAYS_ANIM,	0,	IDLE_PLAYS_ANIM)
ENUM_END()

#endif // _ENUMS_AI_INC



