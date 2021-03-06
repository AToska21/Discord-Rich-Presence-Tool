#include "discord.hh"

Discord::Discord()
	: bInitialised(false),
	  rich{}
{
}

Discord::~Discord()
{
	Shutdown();
}

auto Discord::Initialise(std::string appId) -> void
{
	if (!bInitialised)
	{
		// Initialise handlers
		handlers = {};

		Discord_Initialize(appId.c_str(), &handlers, 1, nullptr);

		bInitialised = true;
	}
}

auto Discord::UpdatePresence(RichPresence &richPresence) -> bool
{
	if (bInitialised)
	{
		// Copy Rich Presence details from parameter struct to member struct
		rich.details = richPresence.details.c_str();
		rich.state = richPresence.state.c_str();
		rich.largeImageKey = richPresence.largeKey.c_str();
		rich.largeImageText = richPresence.largeText.c_str();
		rich.partyMax = richPresence.partyMax;
		rich.partySize = richPresence.partySize;
		rich.smallImageKey = richPresence.smallKey.c_str();
		rich.smallImageText = richPresence.smallText.c_str();
		rich.startTimestamp = richPresence.timeStart;
		rich.endTimestamp = richPresence.timeEnd;

		Discord_UpdatePresence(&rich);

		return true;
	}
	else
	{
	   return false;
	}
}

auto Discord::Shutdown() -> void
{
	if (bInitialised)
	{
		// Clean up Discord
		Discord_Shutdown();

		bInitialised = false;
	}
}
