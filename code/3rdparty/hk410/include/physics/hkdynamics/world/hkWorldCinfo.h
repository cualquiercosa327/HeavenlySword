/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2006 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKDYNAMICS_WORLD_HKWORLDCINFO_XML_H
#define HKDYNAMICS_WORLD_HKWORLDCINFO_XML_H

#include <hkmath/basetypes/hkAabb.h>

/// hkWorldCinfo meta information
extern const class hkClass hkWorldCinfoClass;

/// This structure contains all the information needed to construct a hkWorld
/// object.
class hkWorldCinfo : public hkReferencedObject
{
	public:

		HK_DECLARE_REFLECTION();

			/// Used to specify the speed/stiffness balance of the core solver.
			/// Havok's solver is an iterative solver and similar to a 'successive
			/// over relaxation' (SOR) method. That means that each constraint will not
			/// be solved perfectly, but rather solved like a very stiff spring,
			/// which gives the solver a 'soft' feeling. So the goal of the solver
			/// is to make the constraint to appear hard.
			/// There are 3 parameters to control the behavior of the solver:
			///  - m_solverIterations: defines how often the solver iterates over
			///	   all constraints. The higher the number, the stiffer the constraints,
			///    however you need to spend more CPU. Values between 2 and 16 are
			///    reasonable, higher values could lead to instable behavior (in this
			///    case you can achieve the same results by decreasing the physics delta time).
			///  - m_tau: defines how much of the current constraint error is solved every
			///    solver iteration. High values (0.8 .. 1.2 ) make the constraints harder,
		    ///    however they get more unstable as well. Smaller numbers (0.3 .. 0.6) give
			///    much softer and smoother behavior, however you have to set the number of iterations
			///    pretty high to achieve a stiff behavior.
		    ///  - m_damping: defines how the current bodies velocity is taken into account.
			///    If you set damping to 0, you get an explicit solver, setting it to m_tau
			///    makes the solver semi-implicit. A good choice is to set it to tau.
			///  This enum list allows to define some reasonable defaults: NITERS refers
			///  to the number of iterations, SOFT/MEDIUM/HARD refers to the value of tau and
			///  damp.
			///  Note: there is a new experimental parameter: m_solverNumMicroSteps. This allows for
			/// further increasing (multiply) the m_solverIterations without adding extra instability
		enum SolverType
		{
				///
			SOLVER_TYPE_INVALID,
				/// 'Softest' solver type.
			SOLVER_TYPE_2ITERS_SOFT,
				/// .
			SOLVER_TYPE_2ITERS_MEDIUM,
				/// .
			SOLVER_TYPE_2ITERS_HARD,
				/// .
			SOLVER_TYPE_4ITERS_SOFT,
				/// .
			SOLVER_TYPE_4ITERS_MEDIUM,
				/// .
			SOLVER_TYPE_4ITERS_HARD,
				/// .
			SOLVER_TYPE_8ITERS_SOFT,
				/// .
			SOLVER_TYPE_8ITERS_MEDIUM,
				/// 'Hardest' solver type.
			SOLVER_TYPE_8ITERS_HARD,
				///
			SOLVER_TYPE_MAX_ID
		};

			/// Specifies simulation with discrete or continuous collision detection.
			// Note: all simulation types with enumeration values >= SIMULATION_TYPE_CONTINUOUS set m_wantContinuousAgents = true in hkWorld's constructor.
		enum SimulationType
		{
				///
			SIMULATION_TYPE_INVALID,

				/// No continuous simulation is performed
			SIMULATION_TYPE_DISCRETE,

				/// Use this simulation if you want any continouos simulation.
				/// Depending on the hkEntity->getQualityType(), collisions
				/// are not only performed at 'normal' physical timesteps (called PSI), but
				/// at any time when two objects collide (TOI)
			SIMULATION_TYPE_CONTINUOUS,

				/// Multithreaded simulation.
				/// You must have read the multi threading user guide.<br>
                /// To use this you have to call hkWorld::stepDeltaTime() several times
				/// (once for each thread).
				/// Each thread entering the physics using this hkWorld::stepDeltaTime() call
				/// will immediately be used by the engine. There is not need for
				/// all threads to enter the hkWorld at the same time, actually the
				/// first thread entering will do some special single threaded maintance
				/// jobs. After all threads have been finished you have to call
				/// hkWorld::m_simulation->resetThreadTokens() from a single thread.<br>
				/// Notes:
				///   - The internal overhead for multi threaded is small and you can expect
				///     good speedups, except:
				///   - TOI solving is not multithreaded
				///   - Solving a single huge island is not multithreaded.
				///   So multithreading works best if you have a distributed world.
			SIMULATION_TYPE_MULTITHREADED,
		};

			/// Specifies how aggressively the engine accepts new contact points
		enum ContactPointGeneration
		{
				/// Try to gather as many contact points as possible. This
				/// gives you the highest quality at the cost of some (up to 25%)
				/// extra CPU. You should use this setting if you want to stack
				/// very small objects in your game
			CONTACT_POINT_ACCEPT_ALWAYS,

				/// Accept good contact points immediately and try to
				/// to reject the rest. This is a compromise
			CONTACT_POINT_REJECT_DUBIOUS,

				/// Uses some optimistic algorithms to speed up contact point generation.
				/// This can seriously increase the performance of the engine.
				/// Note: Stacking small objects becomes very difficult with this option enabled
			CONTACT_POINT_REJECT_MANY,
		};

			/// Tell the system what should happen if an objects leaves the
			/// extents of the broadphase.
			/// If you want to do your own implementation,
			/// just derive from hkBroadPhaseBorder, implement your own
			/// maxPositionExceededCallback and call
			/// hkWorld::setBroadPhaseBorder( new myBroadPhaseBorder() );
		enum BroadPhaseBorderBehaviour
		{
				/// Cause an assert and set the motion type to be fixed (default).
			BROADPHASE_BORDER_ASSERT,

				/// Set the motion type to be fixed and raise a warning.
			BROADPHASE_BORDER_FIX_ENTITY,

				/// Remove the entity from the hkWorld and raise a warning.
			BROADPHASE_BORDER_REMOVE_ENTITY,

			    /// Do not do anything, just continue to work.
				/// If many (>20) objects leave the broadphase,
				/// serious memory and CPU can be wasted.
			BROADPHASE_BORDER_DO_NOTHING,
		};

			/// Default constructor
		hkWorldCinfo();

		//
		// Methods
		//

			/// Set the parameters of the world's solver. Each solver type provides a different
			/// speed/stiffness balance for the simulation. The default solver type is
			/// SOLVER_TYPE_4ITERS_MEDIUM, which is fast and moderately soft.
		void setupSolverInfo(enum SolverType st);

			/// Sets the broad phase size to be a cube centered on the origin of side
			/// sideLength. See also m_broadPhaseWorldSize.
		void setBroadPhaseWorldSize(hkReal size);

		//
		// Members
		//
	public:

		//
		// Basic setup
		//

			/// The gravity for the world. The default is (0, -9.8, 0).
		hkVector4 m_gravity; //+default(0,-9.8f,0)

			/// This variable is used to guess at the maximum number of overlaps you will get
			/// when you add or remove an entity or phantom. It determines the size of the local
			/// array used to query the broad phase. The local array uses the hkMemory stack,
			/// The default value is 1024, which requires a local array stack area of 8K.
		hkInt32 m_broadPhaseQuerySize; //+default(1024)

			/// The velocity which defines when two objects are assumed to be
			/// in resting contact. If the approaching velocity of the two objects
			/// at a point of contact is higher than this value, a special more accurate collision
			/// restitution algorithm is called. By default this value is HK_REAL_MAX
			/// which thus disables this algorithm (though more accurate, this algorithm can, as a side-effect,
			/// cause instabilites for long thin bodies). If you want to enable this algorithm
			/// and are aware of the possible artifacts mentioned above, you can set this value to 0.2f
			/// (the value used in Havok 3.1.0 and 3.1.1).
		hkReal m_contactRestingVelocity;

			/// Tell the system what should happen if an objects leaves the
			/// extents of the broadphase. Read BroadPhaseBorderBehaviour for more details.
			/// This value defaults to BROADPHASE_BORDER_ASSERT
		hkEnum<enum BroadPhaseBorderBehaviour,hkInt8> m_broadPhaseBorderBehaviour;

			/// Defines the area dealt with by the collision detection broadphase. The size
			/// specified is a cuboid in world units - this cuboid defines the broadphase
			/// limits. There is a significant performance cost for objects that leave this
			/// area. The default size is a cube of side 1000, centred at the origin.
		class hkAabb m_broadPhaseWorldAabb;

			/// The collision tolerance. This is used to create and keep contact points even for
			/// non penetrating objects. This dramatically increases the stability of the
			/// system. The default collision tolerance is 0.1f.
			/// It is safe to decrease this value slightly when continuous simulation is enabled. This allows
			/// for more precise creation of contact points and better quality at the cost of generating
			/// more TOI events.
		hkReal m_collisionTolerance; //+default(.1f)

			/// The collision filter used by the hkWorld. By default this is HK_NULL.
			/// If left as HK_NULL, a hkNullCollisionFilter is set as the default filter in the
			/// world. This disables no collisions.
		class hkCollisionFilter* m_collisionFilter;

			/// The filter used to decide how convex list shape collisions should be treated.
			/// By default this pointer is set to HK_NULL, in which case the default convex list filter
			/// will be created when the hkWorld is constructed.  
			/// It is not possible to change this collision filter after the world has been created.
		class hkConvexListFilter* m_convexListFilter;

			/// The max linear velocity you expect the continuous physics to work correctly.
			/// This value is used to set internal tolerances. It defaults to 200 [meters per second]
			/// Note: This value does not limit the maximum linear velocities of rigid bodies.
			/// You have to set hkRigidBody::m_maxLinearVelocity for each body yourself.
		hkReal m_expectedMaxLinearVelocity; //+default(200)

			/// The min delta time you expect between two PSI.
			/// This value is only used to set internal tolerances. It defaults to 1/30.0f second
			/// Note: This value does not limit the delta time.
		hkReal m_expectedMinPsiDeltaTime; //+default(1.0f/30.0f)


			/// The memory "watchdog" used by the world. By default this is HK_NULL, i.e. the memory
			/// for the world is not checked. If this is set, hkWorldMemoryWatchDog::watchMemory will be
			/// called every step, which gives the hkWorldMemoryWatchDog a chance to prevent the memory
			/// exceeding a desired threshold.
		class hkWorldMemoryWatchDog* m_memoryWatchDog;


		//
		// Optimizations
		//

			/// NOTE: There is currently a known issue HVK-2553 associated with markers which
			/// can cause a possible crash during simulation.  The fix is scheduled for the next
			/// release. You should leave this value at 0 in the mean time.
			/// This variable is used to subdivide the x-axis in the 3-axisSweepAndPrune space
			/// into regular intervals. Setting this value slows down the normal operations by a
			/// very small amount, but can speed up asynchronous broadphase queries by up to 10
			/// times. Values have to be of power of 2. A typical good value would be 64.
			/// The default is 0, i.e. markers are not enabled by default.
		hkInt32 m_broadPhaseNumMarkers;


			/// Specifies how aggressively the engine accepts new contact points
			/// Defaults to CONTACT_POINT_REJECT_MANY
		hkEnum<enum ContactPointGeneration, hkInt8> m_contactPointGeneration;


		//
		// Solver settings
		//

			/// Parameter of the world's constraint solver. Default sets of values can be
			/// automatically set using the setupSolverInfo() method by passing the required
			/// hkSolverType. See SolverType or documentation for details on customizing these values.
		hkReal m_solverTau;

			/// Parameter of the world's constraint solver. Default sets of values can be
			/// automatically set using the setupSolverInfo() method by passing the required
			/// hkSolverType. See SolverType or documentation for details on customizing these values.
			/// The default is 0.6f
		hkReal m_solverDamp; //+default(.6f)

			/// Parameter of the world's constraint solver. Default sets of values can be
			/// automatically set using the setupSolverInfo() method by passing the required
			/// hkSolverType. See SolverType or documentation for details on customizing these values.
			/// The default is 4.
		hkInt32 m_solverIterations; //+default(4)

			/// This is the number of gauss seidel steps the solver performs during each Havok step.
			/// Basically this allows for virtually increasing the number of solver steps without
			/// adding extra instability. However the microsteps are not as powerful as the main
			/// solver steps.
			/// So by default this value should be 1. Only if you wish to increase the number
			/// of solver steps to be higher than 8 and you experience stability problems,
			/// you can increase this value and leave the number of solver steps to 4 or 8.
		hkInt32 m_solverMicrosteps; //+default(1)

		//
		// Internal algorithm settings
		//


			/// (Collision config) The early out distance default for Linear casts. Defaults to
			/// 0.01 units, usually about a 10th of collision tolerance so change this if you
			/// change the collision tolerance value.
		hkReal m_iterativeLinearCastEarlyOutDistance; //+default(.01f)

			/// (Collision config) The max number of iterations the Linear casts will make.
			/// Defaults to 20.
		hkInt32 m_iterativeLinearCastMaxIterations; //+default(20)

			/// The high deactivation period (deprecated). By default this is 0.2.
		hkReal m_highFrequencyDeactivationPeriod; //+default(.2f)

			/// The low deactivation period (deprecated). By default this is 10.
		hkReal m_lowFrequencyDeactivationPeriod; //+default(10)


			/// This says whether bodies are to be activated when they get moved around with any
			/// of the setPositon/setRotation/setTransform calls. By default this is true.
		hkBool m_shouldActivateOnRigidBodyTransformChange; //+default(true)

			/// Set this to true if you want the old Havok4.0 style activation which
			/// uses an hkEntityDeactivator class 
			/// in parallel to the new system. This feature is deprecated.
			/// If you also want to disable the other system, simply set m_deactivationReferenceDistance to 0.0f
		hkBool m_wantOldStyleDeactivation;

			/// This is the base distance used for the deactivation check.
			/// The basic idea is that we deactivate an object if its position stays
			/// within a sphere (radius=m_deactivationReferenceDistance) for about 20 frames (high frequency deactivation).
			/// Or within a sphere (radius = 4*m_deactivationReferenceDistance) for about 80 frames (low frequency deactivation).
			/// If the object breaches this deactivation sphere, the center of the sphere is set to the current position
			/// of the object. Also the same rules apply to angular movement.
			/// Some details:
			///  - Every object is only checked every 4th frame for high frequency deactivation
			///  - Every object is only checked every 16th frame for low frequency deactivation
			///  - Just before deactivating we check the velocity again. If the velocity has significantly increased
			///    (is significantly (0.1f) bigger than 2 times the maximum velocity measured over the last 20/80 frames)
			///    we do not deactivate this object.
			/// You can set some of those values in the hkSolverInfo (hkWorld::getSolverInfo()) for each deactivation class after the world is constructed.
		hkReal m_deactivationReferenceDistance; //+default(0.02f)

			/// Advanced Parameter:
			/// Rotates the normal of the contact point for TOI contact point resolution.
			/// The range of this parameter should be between 0 and 1 (0.2f by default).
			/// Setting this parameter bigger than 0 simulates an extra surface roughness,
			/// thereby allowing sliding objects to get an extra separating velocity and
			/// therefore reducing the frequency of subsequent TOI.
			/// In short: Setting this parameter to >0 adds extra bounce and can greatly
			/// reduce CPU.
		hkReal m_toiCollisionResponseRotateNormal; //+default(0.2f)


		//
		// Debugging flags
		//

			/// Set to false if you want deactivation to be disabled. See the frequency settings
			/// for deactivation too.
		hkBool m_enableDeactivation; //+default(true)

			/// Simulation type. By default this is SIMULATION_TYPE_CONTINUOUS. See hkWorld::SimulationType for more details.
		hkEnum<enum SimulationType, hkInt8> m_simulationType;

			/// Sets whether the world is automatically segmented into separate islands each step.
			/// This should always be enabled. The default is enabled.
		hkBool m_enableSimulationIslands; //+default(true)

			/// This parameter allows to keep the islands size reasonable large to avoid performance overhead in multi threaded simulations.
			/// 
			/// Having lots of very small islands can cause some unnecessary overhead in the multithreaded simulation.
			/// (Its like rendering single triangles using a modern graphics card).
			/// Therefore we have the concept of sparse islands.
			/// These islands could in theory be split into smaller islands,
			/// however its not done and those islands are flagged with hkSimulationIsland::m_sparseEnabled = true.
			/// But whenever an island is deactivated, it will be checked for split and only that sub island will be deactivated
			/// which is actually inactive. 
			/// 
			/// This parameter only works in multithreading mode, otherwise it will not be used and will be set to 0.
		hkUint32 m_minDesiredIslandSize; //+default(64)

			/// Forces actions to be processed in a single thread. If you have a multi threaded simulation and
			/// you are using actions which influence objects other then the action's entities (listed in hkAction::getEntities(), this flag must
			/// be set to true (e.g. hkVehicleInstance applies forces on objects laying on the ground and uses a phantom).
		hkBool m_processActionsInSingleThread; //+default(true)

			/// Snaps the frameTimeMarker to the currentPsiTime when those times are close together.
			/// By default they must be less than .0001 seconds apart to be snapped together.
			/// This synchronization of frameTime and physicsTime is performed by default, and is useful to control numerical drift when e.g.
			/// running simulation at half the frequency of the frame rate. A side effect is such that the total time of simulation may
			/// slightly vary from the sum of frameDeltaTime parameters passed to world->setFrameTimeMarker(frameDeltaTime).
			/// If you use your hkWorld for testing and precise measurements you may prefer to disable synchronization.
			/// To do this set this variable to 0.
		hkReal m_frameMarkerPsiSnap; //+default(.0001f)

		virtual ~hkWorldCinfo() {}
		hkWorldCinfo( hkFinishLoadedObjectFlag flag );

};

#endif // HKDYNAMICS_WORLD_HKWORLDCINFO_XML_H

/*
* Havok SDK - PUBLIC RELEASE, BUILD(#20060902)
*
* Confidential Information of Havok.  (C) Copyright 1999-2006 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available from salesteam@havok.com.
*
*/
