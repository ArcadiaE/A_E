/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
****/

/* thread.h */

/*
=================
last modified: 2023/3/25
=================
*/

#ifndef __THREADS__
#define __THREADS__

#ifdef __cplusplus
extern "C"
{
#endif

extern	int		numthreads;

void ThreadSetDefault (void);
int	GetThreadWork (void);
void RunThreadsOnIndividual (int workcnt, qboolean showpacifier, void(*func)(int));
void RunThreadsOn (int workcnt, qboolean showpacifier, void(*func)(int));
void ThreadLock (void);
void ThreadUnlock (void);

#ifndef NO_THREAD_NAMES
#define RunThreadsOn(n,p,f) { if (p) printf("%-20s ", #f ":"); RunThreadsOn(n,p,f); }
#define RunThreadsOnIndividual(n,p,f) { if (p) printf("%-20s ", #f ":"); RunThreadsOnIndividual(n,p,f); }
#endif





#ifdef __cplusplus
}
#endif

#endif /*__THREADS__*/
