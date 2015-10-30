#pragma once

#include <Windows.h>

#include "GWCAManager.h"
#include "GwConstants.h"
#include "GWStructures.h"


namespace GWAPI {
	class MapMgr : public GWCAManager {
		friend class GWAPIMgr;

		struct PAB_ZoneMap {
			const DWORD header = 0xAB;
			DWORD mapid;
			int region;
			int district;
			int language;
			DWORD unk;
		};
	public:

		// Get current map ID.
		GwConstants::MapID GetMapID();

		// Get current region you are in.
		inline int GetRegion() { return *(int*)(MemoryMgr::MapInfoPtr + 0x10); }

		// Get current language you are in.
		inline int GetLanguage() { return *(int*)(MemoryMgr::MapInfoPtr + 0xC); }

		// Get time, in ms, since the instance you are residing in has been created.
		DWORD GetInstanceTime();

		// Get the instance type (Outpost, Explorable or Loading)
		GwConstants::InstanceType GetInstanceType();

		// Travel to specified outpost.
		void Travel(GwConstants::MapID MapID, DWORD District = 0, int Region = 0, DWORD Language = 0);

		// Returns array of icons (res shrines, quarries, traders, etc) on mission map.
		// Look at MissionMapIcon struct for more info.
		GW::MissionMapIconArray GetMissionMapIconArray();

		// Returns pointer of collision trapezoid array.
		GW::PathingMapArray GetPathingMap();

	private:
		MapMgr(GWAPIMgr& api) : GWCAManager(api) {}
		void RestoreHooks() override {}
	};
}
