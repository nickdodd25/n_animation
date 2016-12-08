#include <a_samp>
#include <zcmd>
#include <n_animations>

CMD:anims(playerid,params[])
{
	return ShowAnimsDialog(playerid);
}

CMD:stopanims(playerid,params[])
{
	return ClearAnimations(playerid, 1);
}