#include "StdAfx.h"
#include <discord_register.h>
#include <discord_rpc.h>
#include <time.h>
#include <chrono>
#include "DiscordRPC.h"

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

DiscordRPC* DiscordRPC::sg_Instance = NULL;

DiscordRPC& DiscordRPC::GetInstance()
{
	if (sg_Instance == NULL)
	{
		sg_Instance = new DiscordRPC;
	}
	return *sg_Instance;
}

DiscordRPC::DiscordRPC()
{
	Init();
}

DiscordRPC::~DiscordRPC()
{
	delete[] sg_Instance;
}

void DiscordRPC::Init()
{
	strcpy(m_szApplicationID, "");
	strcpy(m_szState, "");
	strcpy(m_szDetails, "");
	strcpy(m_szLargeImageKey, "");
	strcpy(m_szLargeImageText, "");
	strcpy(m_szSmallImageKey, "");
}

//호출 1
void DiscordRPC::SetData(const char* szApplicationID, const char* szState, const char* szDetails, const char* szLargeImageKey, const char* szLargeImageText, const char* szSmallImageKey)
{
	strcpy(m_szApplicationID, szApplicationID);
	strcpy(m_szState, szState);
	strcpy(m_szDetails, szDetails);
	strcpy(m_szLargeImageKey, szLargeImageKey);
	strcpy(m_szLargeImageText, szLargeImageText);
	strcpy(m_szSmallImageKey, szSmallImageKey);
}

//호출2
void DiscordRPC::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize(m_szApplicationID, &Handle, 1, NULL);
}

//호출3
void DiscordRPC::Update()
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = m_szState;
	discordPresence.details = m_szDetails;
	discordPresence.startTimestamp = eptime;
	discordPresence.largeImageKey = m_szLargeImageKey;
	discordPresence.largeImageText = m_szLargeImageText;
	discordPresence.smallImageKey = m_szSmallImageKey;
	Discord_UpdatePresence(&discordPresence);
}

long long DiscordRPC::GetEpochTime()
{
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);

	FILETIME fileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime;
	uli.HighPart = fileTime.dwHighDateTime;

	return static_cast<long long>(uli.QuadPart / 10000000LL - 11644473600LL);
}