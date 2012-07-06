
// for some types of variables
#include "StdAfx.h"

// for prevent of multiple definitions
#ifndef PRODEF_H
#define PRODEF_H

	// Gs definition offsets
	#ifdef _GS
		#define ConfigGS				".\\GameServer.ini"		// for WzAG
		#define GSSIZE					4452468					// for VirtualProtect
	#endif								 

	// GsCs definition offsets
	#ifdef _GS_CS
		#define ConfigGS				".\\GameServerCS.ini"	// for WzAG
		#define GSSIZE					4685942					// for VirtualProtect
	#endif

	// Definition Config Strings
	#define ConfigCommon "..\\Configs\\Common.ini"

#endif PRODEF_H