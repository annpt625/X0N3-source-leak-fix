#include "Skins.h"
#include "../Setup.h"
#include "../../GUI/Gui.h"

#define KITS_LIST_X 229
#define KITS_LIST_Y 363

#define ITEM_LIST_X 231
#define ITEM_LIST_Y 409

#define lol(e) XorStr(e)

string GlovesModels[49] =
{
	lol("default"),
	lol("Sport Superconductor"),
	lol("Sport Pandora's Box"),
	lol("Sport Hedge Maze"),
	lol("Sport Arid"),
	lol("Sport Vice"),
	lol("Sport Omega"),
	lol("Sport Bronze Morph"),
	lol("Sport Amphibious"),
	lol("Moto Eclipse"),
	lol("Moto Spearmint"),
	lol("Moto Boom!"),
	lol("Moto Cool Mint"),
	lol("Moto Polygon"),
	lol("Moto Transport"),
	lol("Moto Turtle"),
	lol("Moto Pow"),
	lol("Specialist Crimson Kimono"),
	lol("Specialist Emerald Web"),
	lol("Specialist Foundation"),
	lol("Specialist Forest DDPAT"),
	lol("Specialist Mogul"),
	lol("Specialist Fade"),
	lol("Specialist Buckshot"),
	lol("Specialist Crimson Web"),
	lol("Driver Lunar Weave"),
	lol("Driver Convoy"),
	lol("Driver Crimson Weave"),
	lol("Driver Diamondback"),
	lol("Driver Racing Green"),
	lol("Driver Overtake"),
	lol("Driver Imperial Plad"),
	lol("Driver King Snake"),
	lol("Hand Wraps Leather"),
	lol("Hand Wraps Spruce DDPAT"),
	lol("Hand Wraps Badlands"),
	lol("Hand Wraps Slaughter"),
	lol("Hand Wraps Aboreal"),
	lol("Hand Wraps Duct Tape"),
	lol("Hand Wraps Overprint"),
	lol("Hand Wraps Cobalt Skulls"),
	lol("Bloodhound Charred"),
	lol("Bloodhound Snakebite"),
	lol("Bloodhound Bronzed"),
	lol("Bloodhound Guerrilla"),
	lol("Hydra Case Hardened"),
	lol("Hydra Rattler"),
	lol("Hydra Mangrove"),
	lol("Hydra Emerald")
};

string AgentsModels[23] =
{
	lol("default"),
	lol("Ground Rebel | Elite Crew"),
	lol("Osiris | Elite Crew"),
	lol("Prof. Shahmat | Elite Crew"),
	lol("The Elite Mr. Muhlik | Elite Crew"),
	lol("Soldier | Phoenix"),
	lol("Enforcer | Phoenix"),
	lol("Slingshot | Phoenix"),
	lol("Operator | FBI SWAT"),
	lol("Markus Delrow | FBI HRT"),
	lol("Michael Syfers | FBI Sniper"),
	lol("Special Agent Ava | FBI"),
	lol("3rd Commando Company | KSK"),
	lol("Seal Team 6 Soldier | NSWC SEAL"),
	lol("Buckshot | NSWC SEAL"),
	lol("'Two Times' McCoy | USAF TACP"),
	lol("Lt. Commander Ricksaw | NSWC SEAL"),
	lol("Dragomir | Sabre"),
	lol("Maximus | Sabre"),
	lol("Rezan The Ready | Sabre"),
	lol("Blackwolf | Sabre"),
	lol("'The Doctor' Romanov | Sabre"),
	lol("B Squadron Officer | SAS")
};

int Page = 0;

static bool FindLower(string data, string find)
{
	if (find.empty())
		return true;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	transform(find.begin(), find.end(), find.begin(), ::tolower);

	if (data.find(find) != string::npos)
		return true;

	return false;
}

void CSkins::ItemsList(const vector<ItemSettings> &Items, int &var, const Vec2 Size, const string Name)
{
	if (X1Gui().ListBoxHeader(Name.c_str(), Size))
	{
		for (int i = 0; i < (int)Items.size(); i++)
		{
			bool selected = i == var;
			if (X1Gui().SelectLabel((string(Items[i].Name) + XorStr("##") + to_string(i)).c_str(), selected))
				var = i;
		}
	}
	X1Gui().ListBoxFooter();
}

void CSkins::SkinsList(const vector<paint_kit> &Skins, int &var, const Vec2 Size, const string Name, const string Find)
{
	if (X1Gui().ListBoxHeader(Name.c_str(), Size))
	{
		for (size_t i = 0; i < Skins.size(); i++)
		{
			if (!FindLower((true ? Skins[i].name_eng : Skins[i].name), Find))
				continue;

			bool selected = i == var;

			if (X1Gui().SelectLabel(((true ? Skins[i].name_eng : Skins[i].name) + XorStr("##") + to_string(i)).c_str(), selected, Vec2(151, 0)))
				var = i;
			X1Gui().SameLine(149);
			if (X1Gui().SelectLabel((XorStr("| ") + to_string(Skins[i].id)).c_str(), selected, Vec2(75, 0)))
				var = i;

		}
	}
	X1Gui().ListBoxFooter();
}

void CSkins::SortSkinsList(const vector<SortedKits_s> &Skins, int &var, const Vec2 Size, const string Name, const string Find)
{
	if (X1Gui().ListBoxHeader(Name.c_str(), Size))
	{
		for (size_t i = 0; i < Skins.size(); i++)
		{
			if (!FindLower((true ? Skins[i].name : Skins[i].name_rus), Find))
				continue;

			bool selected = i == var;

			if (X1Gui().SelectLabel(((true ? Skins[i].name : Skins[i].name_rus) + XorStr("##") + to_string(i)).c_str(), selected, Vec2(151, 0)))
				var = i;
			X1Gui().SameLine(149);
			if (X1Gui().SelectLabel((XorStr("| ") + to_string(Skins[i].kit)).c_str(), selected, Vec2(75, 0)))
				var = i;

		}
	}
	X1Gui().ListBoxFooter();

}

void CSkins::Menu()
{
	float long_item_w = X1Gui().GetThis()->Info.Size.x - (X1Gui().GetStyle().wndPadding.x * 2);

	auto SkinParams = [&](SkinSettings &Item) -> void
	{
		X1Gui().PushItemWidth(400);
		SliderFloats("Seed", Item.seed, 0.f, 2.f);
		SliderFloats("Wear", Item.wear, 0.f, 1.f, XorStr("%.9f"));
		X1Gui().PushItemWidth(270);
		SliderInts("StatTrak", Item.stat_track, 0, 5000);
		X1Gui().SameLine();
		DCheckBox("Auto StatTrak", Item.auto_stat_track);

		X1Gui().PushItemWidth(400);

		vector<string> ItemsQuality = { lolc("Default"), lolc("Genuine"), lolc("Vintage"), lolc("Knife Star"), lolc("Tournament"), lolc("Community") ,
			lolc("Valve"), lolc("Prototype"), lolc("Customized"), lolc("StatTrak"), lolc("Complited") };

		VectorEx<const char* > ItemsQQ = { ItemsQuality[0].c_str(), ItemsQuality[1].c_str(), ItemsQuality[2].c_str(), ItemsQuality[3].c_str(), ItemsQuality[4].c_str(), ItemsQuality[5].c_str(),
			ItemsQuality[6].c_str(), ItemsQuality[7].c_str(), ItemsQuality[8].c_str(), ItemsQuality[9].c_str(), ItemsQuality[10].c_str() };

		DComboBox("Quality", Item.quality, ItemsQQ);

		X1Gui().InputText(XorStr("Name##custom_name"), Item.custom_name, 32);
	};

	VectorEx<const char*> SkinArr = { lolc("Weapon"), lolc("Knife"), lolc("Gloves"), lolc("Agents") };

	static int SkinSettingsMode = 0;

	TabsLabels(SkinSettingsMode, SkinArr, Vec2(long_item_w - 6, 0), false);
	X1Gui().Spacing();
	if (SkinSettingsMode == 0)
	{
		VectorEx<const char*> WeapSkinArr = { lolc("Skin##Changer"), lolc("Stickers##Changer") };
		static int WeapSkinSettingsMode = 0;

		TabsLabels(WeapSkinSettingsMode, WeapSkinArr, Vec2(long_item_w, 0), false);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (X1Gui().Button(XorStr("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(XorStr("Updated!"));
		}

		X1Gui().Spacing();

		if (WeapSkinSettingsMode == 0)
		{
			ItemsList(WeaponNames, SelectedWeapon, Vec2(ITEM_LIST_X, ITEM_LIST_Y), XorStr("##AllWeapons"));

			X1Gui().SameLine();

			ItemSettings* WItem = &WeaponNames[SelectedWeapon];

			//WeaponPreview = WItem->CdnName;

			X1Gui().BeginGroup();
			{
				X1Gui().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All") , lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				X1Gui().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedWeapons[SelectedWeapon].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedWeapons[SelectedWeapon].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedWeapons[SelectedWeapon].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedWeapons[SelectedWeapon].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						X1Gui().ListBoxHeader(XorStr("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						X1Gui().Text(XorStr("Loading Skins..."));
						X1Gui().ListBoxFooter();
					}

				}
			}
			X1Gui().EndGroup();

			X1Gui().Spacing();

			SkinParams(WItem->Skin);
		}
		else if (WeapSkinSettingsMode == 1)
		{
			X1Gui().Spacing();
			X1Gui().PushItemWidth(192);
			X1Gui().Spacing();

			X1Gui().PushItemWidth(320);

			static int iSlot = 0;

			VectorEx<const char*> Slots = { lolc("1"),lolc("2"), lolc("3"), lolc("4"), lolc("5") };
			DComboBox("Slot##Stickers", iSlot, Slots, Slots);

			static int StikersMode = 1;
			static int SortSelectedS = 0;

			VectorEx<const char*> itemssm = { lolc("All") ,lolc("Distributed") };
			DComboBox("Stickers##vodStickers", StikersMode, itemssm);
			static char FindBuf[128] = { 0 };
			static string FindSticker = "";

			X1Gui().Spacing();

			StickerSettings* SItem = &WeaponNames[SelectedWeapon].Skin.Stickers[iSlot];

			if (StikersMode == 0)
			{
				TextEdit("Find", FindSticker, FindBuf, 128);
				X1Gui().ListBoxHeader(XorStr("##StikerSerials"), Vec2(453, 380));
				for (size_t i = 0; i < sticker_kits.size(); i++)
				{
					if (!FindLower(sticker_kits[i].name, FindSticker))
						continue;

					bool selected = i == SItem->kit_menu_index;
					if (X1Gui().SelectLabel(sticker_kits[i].name.c_str(), selected))
						SItem->kit_menu_index = i;
				}
				X1Gui().ListBoxFooter();
				SItem->kit = sticker_kits[SItem->kit_menu_index].id;
			}
			else if (StikersMode == 1)
			{
				if (AllSkinsLoaded)
				{
					X1Gui().ListBoxHeader(XorStr("##SortStikerSerials"), Vec2(71, 402));
					for (size_t i = 0; i < SortedStickers.size(); i++)
					{
						bool selected = i == SortSelectedS;
						if (X1Gui().SelectLabel(SortedStickers[i].sub_name.c_str(), selected))
							SortSelectedS = i;
					}
					X1Gui().ListBoxFooter();
					X1Gui().SameLine();
					X1Gui().BeginGroup();
					{
						TextEdit("Find", FindSticker, FindBuf, 128);
						X1Gui().ListBoxHeader(XorStr("##StikerSerials"), Vec2(386, 380));
						for (size_t i = 0; i < SortedStickers[SortSelectedS].Stickers.size(); i++)
						{
							if (!FindLower(SortedStickers[SortSelectedS].Stickers[i].name, FindSticker))
								continue;

							bool selected = i == SItem->kit_menu_index;

							if (X1Gui().SelectLabel(SortedStickers[SortSelectedS].Stickers[i].name.c_str(), selected))
								SItem->kit_menu_index = i;
						}
						X1Gui().ListBoxFooter();
					}
					X1Gui().EndGroup();

					if (SItem->kit_menu_index > 0 && SItem->kit_menu_index < (int)SortedStickers[SortSelectedS].Stickers.size())
						SItem->kit = SortedStickers[SortSelectedS].Stickers[SItem->kit_menu_index].id;
				}
				else
				{
					X1Gui().Text(XorStr("Loading Stickers..."));
				}
			}

			X1Gui().PushItemWidth(400);
			SliderFloats("Wear", SItem->wear, 0.f, 1.f);
			SliderFloats("Scale", SItem->scale, 0.f, 1.f);
			SliderFloats("Rotation", SItem->rotation, 0.f, 360);
		}
	}
	else if (SkinSettingsMode == 1)
	{
		VectorEx<const char*> KnfTeamArr = { lolc("CT"), lolc("T") };
		static int KnfTeamSettingsMode = 0;

		TabsLabels(KnfTeamSettingsMode, KnfTeamArr, Vec2(long_item_w, 0), false);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (X1Gui().Button(XorStr("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(XorStr("Updated!"));
		}

		X1Gui().Spacing();

		if (KnfTeamSettingsMode == 0)
		{
			ItemsList(KnifeNames, SelectedKnifeModelCT, Vec2(ITEM_LIST_X, ITEM_LIST_Y), XorStr("##AllKnifes"));
			X1Gui().SameLine();
			ItemSettings* WItem = &KnifeNames[SelectedKnifeModelCT];

			//WeaponPreview = WItem->CdnName;

			X1Gui().BeginGroup();
			{
				X1Gui().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All"), lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				X1Gui().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllKnifSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedKnives[SelectedKnifeModelCT].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllKnifSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedKnives[SelectedKnifeModelCT].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedKnives[SelectedKnifeModelCT].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedKnives[SelectedKnifeModelCT].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						X1Gui().ListBoxHeader(XorStr("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						X1Gui().Text(XorStr("Loading Skins..."));
						X1Gui().ListBoxFooter();
					}
				}
			}
			X1Gui().EndGroup();
			X1Gui().Spacing();

			SkinParams(WItem->Skin);

			//WeaponPreview = KnifeNames[SelectedKnifeModelCT].CdnName;
			//SkinPreview = skin_kits[KnifeNames[SelectedKnifeModelCT].Skin.paint_kit_menu].cdn_name;
		}
		else if (KnfTeamSettingsMode == 1)
		{
			ItemsList(KnifeNamesTT, SelectedKnifeModelTT, Vec2(ITEM_LIST_X, ITEM_LIST_Y), XorStr("##AllKnifes"));
			X1Gui().SameLine();
			ItemSettings* WItem = &KnifeNamesTT[SelectedKnifeModelTT];

			//WeaponPreview = WItem->CdnName;

			X1Gui().BeginGroup();
			{
				X1Gui().PushItemWidth(185);
				VectorEx<const char*> itemssm = { lolc("All"), lolc("Distributed") };
				DComboBox("Skins##vod", WItem->Skin.skins_mode, itemssm);
				static char FindBuf[128] = { 0 };
				static string FindSkin = "";
				TextEdit("Find", FindSkin, FindBuf, 128);
				X1Gui().Spacing();
				if (WItem->Skin.skins_mode == 0)
				{
					SkinsList(skin_kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllKnifSkins"), FindSkin);
					WItem->Skin.paint_kit_id = skin_kits[WItem->Skin.paint_kit_menu].id;
					//SkinPreview = skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
				}
				else if (WItem->Skin.skins_mode == 1)
				{
					if (AllSkinsLoaded)
					{
						SortSkinsList(SortedKnives[SelectedKnifeModelTT].kits, WItem->Skin.paint_kit_menu, Vec2(KITS_LIST_X, KITS_LIST_Y), XorStr("##AllKnifSkins"), FindSkin);
						if (WItem->Skin.paint_kit_menu < (int)SortedKnives[SelectedKnifeModelTT].kits.size())
						{
							WItem->Skin.paint_kit_id = SortedKnives[SelectedKnifeModelTT].kits[WItem->Skin.paint_kit_menu].kit;
							//SkinPreview = SortedKnives[SelectedKnifeModelTT].kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
					}
					else
					{
						X1Gui().ListBoxHeader(XorStr("##AllSkinsEmpty"), Vec2(KITS_LIST_X, KITS_LIST_Y));
						X1Gui().Text(XorStr("Loading Skins..."));
						X1Gui().ListBoxFooter();
					}
				}
			}
			X1Gui().EndGroup();
			X1Gui().Spacing();

			SkinParams(WItem->Skin);

			//WeaponPreview = KnifeNamesTT[SelectedKnifeModelTT].CdnName;
			//SkinPreview = skin_kits[KnifeNamesTT[SelectedKnifeModelTT].Skin.paint_kit_menu].cdn_name;
		}
	}
	else if (SkinSettingsMode == 2)
	{
		VectorEx<const char*> glvTeamArr = { lolc("CT"), lolc("T") };
		static int glvTeamSettingsMode = 0;

		TabsLabels(glvTeamSettingsMode, glvTeamArr, Vec2(long_item_w, 0), false);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (X1Gui().Button(XorStr("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(XorStr("Updated!"));
		}

		X1Gui().Spacing();

		if (glvTeamSettingsMode == 0)
		{
			X1Gui().ListBoxHeader(XorStr("##Gloves"), Vec2(long_item_w, 527));
			for (int i = 0; i < sizeof(GlovesModels) / sizeof(GlovesModels[0]); i++)
			{
				bool selected = i == SelectedGloveCT;
				if (X1Gui().SelectLabel(GlovesModels[i].c_str(), selected))
					SelectedGloveCT = i;
			}
			X1Gui().ListBoxFooter();

			//if (SelectedGloveCT > 0)
			//{
			//	SkinPreview = GlovesSkin_Array[SelectedGloveCT - 1].Url;
			//	WeaponPreview = GlovesSkin_Array[SelectedGloveCT - 1].Url;
			//}

			X1Gui().PushItemWidth(400);

			if (SelectedGloveCT > 0)
			{
				SliderFloats("Wear", GloveCTWear, 0.f, 1.f, XorStr("%.9f"));
				//X1Gui().InputText(XorStr("Name##Glove"), GloveCTName, 32);
			}
		}
		
		else if (glvTeamSettingsMode == 1)
		{
			X1Gui().ListBoxHeader(XorStr("##Gloves"), Vec2(long_item_w, 527));
			for (int i = 0; i < sizeof(GlovesModels) / sizeof(GlovesModels[0]); i++)
			{
				bool selected = i == SelectedGloveTT;
				if (X1Gui().SelectLabel(GlovesModels[i].c_str(), selected))
					SelectedGloveTT = i;
			}
			X1Gui().ListBoxFooter();

			//if (SelectedGloveTT > 0)
			//{
			//	SkinPreview = GlovesSkin_Array[SelectedGloveTT - 1].Url;
			//	WeaponPreview = GlovesSkin_Array[SelectedGloveTT - 1].Url;
			//}

			X1Gui().PushItemWidth(400);

			if (SelectedGloveTT > 0)
			{
				SliderFloats("Wear", GloveTTWear, 0.f, 1.f, XorStr("%.9f"));
			//	X1Gui().InputText(XorStr("Name##Glove"), GloveTTName, 32);
			}
		}	
	}
	else if (SkinSettingsMode == 3)
	{
		VectorEx<const char*> agtTeamArr = { lolc("CT"), lolc("T") };
		static int agtTeamSettingsMode = 0;

		TabsLabels(agtTeamSettingsMode, agtTeamArr, Vec2(long_item_w, 0), false);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (X1Gui().Button(XorStr("Update"), Vec2(long_item_w, 22)))
		{
			UpdateSkins();
			Message::Get().Start(XorStr("Updated!"));
		}

		X1Gui().Spacing();

		if (agtTeamSettingsMode == 0)
		{
			X1Gui().ListBoxHeader(XorStr("##Agents"), Vec2(long_item_w, 550));
			for (int i = 0; i < sizeof(AgentsModels) / sizeof(AgentsModels[0]); i++)
			{
				bool selected = i == SelectedAgentCT;
				if (X1Gui().SelectLabel(AgentsModels[i].c_str(), selected))
					SelectedAgentCT = i;
			}
			X1Gui().ListBoxFooter();
		}

		else if (agtTeamSettingsMode == 1)
		{
			X1Gui().ListBoxHeader(XorStr("##Agents"), Vec2(long_item_w, 550));
			for (int i = 0; i < sizeof(AgentsModels) / sizeof(AgentsModels[0]); i++)
			{
				bool selected = i == SelectedAgentTT;
				if (X1Gui().SelectLabel(AgentsModels[i].c_str(), selected))
					SelectedAgentTT = i;
			}
			X1Gui().ListBoxFooter();
		}
	}
}

//void CSkins::Preview()
//{
//	int ImageSzX = 304;
//	int ImageSzY = 231;
//
//	Vec2 BackMin = X1Gui().GetCursorPos();
//	Vec2 BackMax = Vec2(BackMin.x + ImageSzX, BackMin.y + ImageSzY);
//
//	color_t BackColor = color_t(185.f, 183.f, 185.f, 183.f);
//	X1Gui().DrawFilledBox(BackMin, BackMax, BackColor);
//
//	static IDirect3DTexture9* skinImg = nullptr;
//
//	static string OldKit = SkinPreview;
//	string link = "";
//
//	if (OldKit != SkinPreview)
//	{
//		skinImg = nullptr;
//
//		link = CGlobal::FindSkinURl(SkinPreview, WeaponPreview);
//		if (skinImg == nullptr)
//		{
//			std::string imData = CGlobal::DownloadSkinBytes(link.c_str());
//
//			D3DXCreateTextureFromFileInMemoryEx(GP_Render->m_pDevice, imData.data(), imData.length(), 512, 384, D3DX_DEFAULT,
//				0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &skinImg);
//		}
//	}
//
//	if (skinImg)
//		X1Gui().DrawImage(skinImg, BackMin, BackMin + Vec2(ImageSzX, ImageSzY));
//
//	OldKit = SkinPreview;
//}



























































