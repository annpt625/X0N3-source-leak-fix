#pragma once
#include "../Engine/EntityMem.h"
#include "Esp/Esp.h"
#include "LegitAim/LegitAim.h"
#include "Misc/Misc.h"
#include "Radar/Radar.h"
#include "Skins/Skins.h"
#include "Inventory/Inventory.h"
#include "GrenadeHelper/GreandeHelper.h"
#include "../Render/DXRender.h"
#include "../Engine/GrenadePrediction.h"
#include "../Engine/SDK/SDK.h"
#include "../Main.h"
#include "../Include/Def.h"
#include "../X1API/MinHook/hook.h"

namespace HookTables
{
	extern void Shutdown();
}

class IISetup
{
public:
	virtual class ISetup
	{
	public:
		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
	};
};

extern CRender::IRender*	GP_Render;
extern CEntityPlayers*		GP_EntPlayers;
extern CEsp*				GP_Esp;
extern CMisc*				GP_Misc;
extern CLegitAim*			GP_LegitAim;
extern CRadar*				GP_Radar;
extern CSkins*				GP_Skins;
#ifdef ENABLE_INVENTORY
extern CInventory*          GP_Inventory;
#endif
extern CGHelper*			GP_GHelper;
extern CMain*               GP_Main;


class CSetup : public IISetup
{
public:
	virtual class ISetup
	{
	public:
		virtual void Setup()
		{
			VMP_ULTRA("SetupThread_Init_Setup")
			ADD_LOG("2-1-11-7-0\n");
			GP_Render =		new CRender::IRender();
			GP_EntPlayers = new CEntityPlayers();
			GP_Esp =		new CEsp();
			GP_Misc =		new CMisc();
			GP_LegitAim =	new CLegitAim();
			GP_Radar =		new CRadar();
			GP_Skins =		new CSkins();
#ifdef ENABLE_INVENTORY
			GP_Inventory =  new CInventory();
#endif
			GP_GHelper =	new CGHelper();
			GP_Main =       new CMain();
			ADD_LOG("2-1-11-7-1\n");
			CGSettings::G().UpdateList();
			GP_Misc->UpdateSoundList();
			ADD_LOG("2-1-11-7-2\n");
			GP_Esp->InitVisuals();
			GP_Esp->InitMaterials();
			GP_LegitAim->InitConVar();
			GP_Render->Initialize();
			GP_GHelper->Initialize();
			ADD_LOG("2-1-11-7-3\n");
#ifndef ONLY_DRAW_HOOK
			GP_Misc->HitWorker.RegListener();
			GP_Skins->FireEvent.RegListener();
			GP_Skins->initialize_kits();
			GP_Skins->ParseSortedKits();
			GP_Skins->PrepareSortedSkins();
#ifdef ENABLE_INVENTORY
			GP_Inventory->InitalizeMedals();
#endif
#endif
			ADD_LOG("2-1-11-7-4\n");
			GP_Skins->AllSkinsLoaded = true;
			ADD_LOG("2-1-11-7-5\n");
			VMP_END
		}
		virtual void Shutdown()
		{
			HookTables::Shutdown();

			GP_Misc->HitWorker.UnRegListener();
			GP_Skins->FireEvent.UnRegListener();

			DELETE_PTR(GP_Render);
			DELETE_PTR(GP_EntPlayers);
			DELETE_PTR(GP_Esp);
			DELETE_PTR(GP_Misc);
			DELETE_PTR(GP_LegitAim);
			DELETE_PTR(GP_Radar);
			DELETE_PTR(GP_Skins);
#ifdef ENABLE_INVENTORY
			DELETE_PTR(GP_Inventory);
#endif
			DELETE_PTR(GP_GHelper);
			DELETE_PTR(GP_Main);
		}
	};
};

extern CSetup::ISetup *GP_Setup;