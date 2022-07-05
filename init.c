void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

// AUTHOR: teaearlgraycold @ https://gist.github.com/teaearlgraycold/8c20f5c5582e84f7fd6c64a9a2247423 
// Code Obtained from https://github.com/ravmustang/DayZ_SA_ClassName_Dump/blob/master/Everything%20DayZ/DayZ%20SA%20Community%20Scripting/PVPLoadout_init.c
// Below code until end is the code that creates the three different random loadouts
class CustomMission: MissionServer

{
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++) {
			mag = player.GetInventory().CreateInInventory(mag_type);
		}

		player.SetQuickBarEntityShortcut(mag, 1, true);
	}

	EntityAI assaultClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("M4A1");
		gun.GetInventory().CreateAttachment("M4_RISHndgrd_Black");
		gun.GetInventory().CreateAttachment("M4_MPBttstck_Black");
		gun.GetInventory().CreateAttachment("ACOGOptic");
		addMags(player, "Mag_STANAG_30Rnd", 3);

		return gun;
	}

	EntityAI sniperClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("SVD");
		gun.GetInventory().CreateAttachment("PSO1Optic");
		addMags(player, "Mag_SVD_10Rnd", 3);

		return gun;
	}

	EntityAI smgClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("UMP45");
		gun.GetInventory().CreateAttachment("PistolSuppressor");
		addMags(player, "Mag_UMP_25Rnd", 3);

		return gun;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
		
		player.GetInventory().CreateInInventory("UKAssVest_Camo");
		player.GetInventory().CreateInInventory("AssaultBag_Green");
		player.GetInventory().CreateInInventory("TTSKOPants");
		player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
		player.GetInventory().CreateInInventory("CombatBoots_Black");
		player.GetInventory().CreateInInventory("BoonieHat_Flecktran");
		player.GetInventory().CreateInInventory("TacticalGloves_Black");
		player.GetInventory().CreateInInventory("SodaCan_Pipsi");
		player.GetInventory().CreateInInventory("SodaCan_Pipsi");
		player.GetInventory().CreateInInventory("SpaghettiCan");
		player.GetInventory().CreateInInventory("TacticalBaconCan_Opened");
		player.GetInventory().CreateInInventory("HuntingKnife");
		player.GetInventory().CreateInInventory("OrienteeringCompass");
		player.GetInventory().CreateInInventory("TacticalBaconCan_Opened");
		player.GetInventory().CreateInInventory("TetracyclineAntibiotics");
		player.GetInventory().CreateInInventory("AntiChemInjector");
		player.GetInventory().CreateInInventory("BandageDressing");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);

		EntityAI primary;
		EntityAI axe = player.GetInventory().CreateInInventory("FirefighterAxe");

		switch (Math.RandomInt(0, 3)) {
			case 0: primary = assaultClass(player); break;
			case 1: primary = sniperClass(player); break;
			case 2: primary = smgClass(player); break;
		}

		player.LocalTakeEntityToHands(primary);
		player.SetQuickBarEntityShortcut(primary, 0, true);
		player.SetQuickBarEntityShortcut(rags, 2, true);
		player.SetQuickBarEntityShortcut(axe, 3, true);
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}