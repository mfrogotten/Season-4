
// for some types of variables
#include "StdAfx.h"

// for prevent of multiple definitions
#ifndef PRODEF_H
#define PRODEF_H

	// Gs definition offsets
	#ifdef _GS
		#define ConfigGS				".\\GameServer.ini"		// for WzAG
		//#define GSSIZE				4452468					// for VirtualProtect (NormalGS)
		#define GSSIZE					4493410					// for VirtualProtect (Hermex&CrazzyGS)
	#endif								 

	// GsCs definition offsets
	#ifdef _GS_CS
		#define ConfigGS				".\\GameServerCS.ini"	// for WzAG
		// #define GSSIZE				4685942					// for VirtualProtect (NormalGSCS)
		#define GSSIZE					4751460					// for VirtualProtect (Hermex&CrazzyGSCS)
	#endif

	// Definition Config Strings
	#define ConfigCommon "..\\Configs\\Common.ini"

#endif PRODEF_H