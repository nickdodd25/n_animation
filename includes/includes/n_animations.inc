
#include <a_samp>

#if defined _nanimation_included
	#endinput
#endif
#define _nanimation_included


#define anims_folder "Anims/"
#define anims_dialog 4156


new anims_String[1000];
new anims_lastlib[MAX_PLAYERS][50];

#define Loop(%0,%1) \
	for(new %0 = 0; %0 != %1; %0++)

static const sAnimList[][50] = { 
{"AIRPORT"},
{"ATTRACTORS"},
{"BAR"},
{"BASEBALL"},
{"BD_FIRE"},
{"BEACH"},
{"BENCHPRESS"},
{"BF_INJECTION"},
{"BIKED"},
{"BIKEH"},
{"BIKELEAP"},
{"BIKES"},
{"BIKEV"},
{"BIKE_DBZ"},
{"BMX"},
{"BOMBER"},
{"BOX"},
{"BSKTBALL"},
{"BUDDY"},
{"BUS"},
{"CAMERA"},
{"CAR"},
{"CARRY"},
{"CAR_CHAT"},
{"CASINO"},
{"CHAINSAW"},
{"CHOPPA"},
{"CLOTHES"},
{"COACH"},
{"COLT45"},
{"COP_AMBIENT"},
{"COP_DVBYZ"},
{"CRACK"},
{"CRIB"},
{"DAM_JUMP"},
{"DANCING"},
{"DEALER"},
{"DILDO"},
{"DODGE"},
{"DOZER"},
{"DRIVEBYS"},
{"FAT"},
{"FIGHT_B"},
{"FIGHT_C"},
{"FIGHT_D"},
{"FIGHT_E"},
{"FINALE"},
{"FINALE2"},
{"FLAME"},
{"FLOWERS"},
{"FOOD"},
{"FREEWEIGHTS"},
{"GANGS"},
{"GHANDS"},
{"GHETTO_DB"},
{"GOGGLES"},
{"GRAFFITI"},
{"GRAVEYARD"},
{"GRENADE"},
{"GYMNASIUM"},
{"HAIRCUTS"},
{"HEIST9"},
{"INT_HOUSE"},
{"INT_OFFICE"},
{"INT_SHOP"},
{"JST_BUISNESS"},
{"KART"},
{"KISSING"},
{"KNIFE"},
{"LAPDAN1"},
{"LAPDAN2"},
{"LAPDAN3"},
{"LOWRIDER"},
{"MD_CHASE"},
{"MD_END"},
{"MEDIC"},
{"MISC"},
{"MTB"},
{"MUSCULAR"},
{"NEVADA"},
{"ON_LOOKERS"},
{"OTB"},
{"PARACHUTE"},
{"PARK"},
{"PAULNMAC"},
{"PED"},
{"PLAYER_DVBYS"},
{"PLAYIDLES"},
{"POLICE"},
{"POOL"},
{"POOR"},
{"PYTHON"},
{"QUAD"},
{"QUAD_DBZ"},
{"RAPPING"},
{"RIFLE"},
{"RIOT"},
{"ROB_BANK"},
{"ROCKET"},
{"RUSTLER"},
{"RYDER"},
{"SCRATCHING"},
{"SHAMAL"},
{"SHOP"},
{"SHOTGUN"},
{"SILENCED"},
{"SKATE"},
{"SMOKING"},
{"SNIPER"},
{"SPRAYCAN"},
{"STRIP"},
{"SUNBATHE"},
{"SWAT"},
{"SWEET"},
{"SWIM"},
{"SWORD"},
{"TANK"},
{"TATTOOS"},
{"TEC"},
{"TRAIN"},
{"TRUCK"},
{"UZI"},
{"VAN"},
{"VENDING"},
{"VORTEX"},
{"WAYFARER"},
{"WEAPONS"},
{"WUZI"},
{"WOP"},
{"GFUNK"},
{"RUNNINGMAN"},
{"SAMP"}
};


stock ShowAnimsDialog(playerid)
{
	if(strlen(anims_lastlib[playerid]) == 0)
	{
		anims_String = "\0";//Reset the global string
		anims_lastlib[playerid] = "\0";
		Loop(i,sizeof(sAnimList))
		{
			format(anims_String,sizeof(anims_String),"%s%s\n",anims_String,sAnimList[i]);
		}
		ShowPlayerDialog(playerid, anims_dialog, DIALOG_STYLE_LIST, "Please Choose an animation Library", anims_String, "Select", "Cancel");
	}
	else
	{
		ShowAnimsLib(playerid,anims_lastlib[playerid]);
	}
	ClearAnimations(playerid, 1);
	return 1;

}

stock GetAnimsLibFromId(libid)
{
	new tmp[50];
	if(libid > sizeof(sAnimList))
	{
		printf("[N_ANIMS] Animation liabrary id %i is an invalid id",libid);
		format(tmp,sizeof(tmp),"Unknown");
	}
	else
	{
		format(tmp,sizeof(tmp),"%s",sAnimList[libid]);
	}
	return tmp;
}

stock ShowAnimsLib(playerid,lib[])
{
	new path[128];
	anims_String = "\0";//Reset the global string

	format(path, sizeof(path), "%s%s.txt", anims_folder,n_animtrim(lib));
	if(!fexist(path))
	{
		printf("[N_ANIMS] Animation liabrary %s not found. Check if %s is in your scriptfiles directory",lib,path);
		anims_lastlib[playerid] = "\0";
		return 1;
	}
	else
	{
		new line[128],File:anims_list = fopen(path, io_read), anims_title[128];
		
		while(fread(anims_list, line))
		{
			format(anims_String,sizeof(anims_String),"%s%s",anims_String,line);
		}
		fclose(anims_list);
		format(anims_title,sizeof(anims_title),"Please Choose an animation ( Animations/%s )",lib);

		ApplyAnimation(playerid,lib,"null",0.0,0,0,0,0,0);
		
		ShowPlayerDialog(playerid, anims_dialog+1, DIALOG_STYLE_LIST, anims_title, anims_String, "Select", "Cancel");

	}
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case anims_dialog:
		{
			if(response)
			{
				ShowAnimsLib(playerid,GetAnimsLibFromId(listitem));
				anims_lastlib[playerid] = "\0";
				strcat(anims_lastlib[playerid], GetAnimsLibFromId(listitem));
			}
			else
				anims_lastlib[playerid] = "\0";
			return 1;
		}
		case anims_dialog+1:
		{
			if(response)
			{
				anims_String = "\0";//Reset the global string
				format(anims_String,sizeof(anims_String),"[SERVER] Running animation (Animations/%s/%s)",anims_lastlib[playerid],inputtext);
				SendClientMessage(playerid, 0xF2FF00AA, anims_String);
				ApplyAnimation(playerid, n_animtrim(anims_lastlib[playerid]), n_animtrim(inputtext), 4.1, 1, 0, 0, 0, 0, 1);
			}
			else
			{
				anims_lastlib[playerid] = "\0";
				ShowAnimsDialog(playerid);
			}
			return 1;
		}
	}


	#if defined NA_OnDialogResponse
	    return NA_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
	    return 0;
	#endif
}

public OnPlayerDisconnect(playerid, reason)
{

	anims_lastlib[playerid] = "\0";


	#if defined NA_OnPlayerDisconnect
	    return NA_OnPlayerDisconnect(playerid, reason);
	#else
	    return 1;
	#endif
}


//I forgot where i got this, but i did not make it, full credit to the owner.
#define _strlib_included
#define _strlib_sma_string 128
#define _strlib_med_string 256
#define _strlib_big_string 512
stock n_animtrim(const sSource[])//Trim any und wanted chars from the source
{
    new
    iBegin,
    iEnd,
    iInputLength = strlen(sSource),
    sReturn[_strlib_med_string];

    strcat(sReturn, sSource, _strlib_med_string);

    for(iBegin = 0; iBegin < iInputLength; ++iBegin) {
        switch(sReturn[iBegin]) {
            case ' ', '\t', '\r', '\n':
            {
                continue;
            }
            default:
            {
                break;
            }
        }
    }

    for(iEnd = (iInputLength - 1); iEnd > iBegin; --iEnd) {
        switch(sReturn[iEnd]) {
            case ' ', '\t', '\r', '\n':
            {
                continue;
            }
            default:
            {
                break;
            }
        }
    }

    strdel(sReturn, (iEnd + 1), iInputLength);
    strdel(sReturn, 0, iBegin);

    return sReturn;
}


#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse NA_OnDialogResponse

#if defined NA_OnDialogResponse
	forward NA_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif



#if defined _ALS_OnPlayerDisconnect
	#undef OnDialogResponse
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect NA_OnPlayerDisconnect

#if defined NA_OnPlayerDisconnect
	forward NA_OnPlayerDisconnect(playerid, reason);
#endif