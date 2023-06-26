#pragma once
class __declspec(dllexport) DiscordRPC
{
private:
	char m_szApplicationID[MAX_PATH];
	char m_szState[MAX_PATH];
	char m_szDetails[MAX_PATH];
	char m_szLargeImageKey[MAX_PATH];
	char m_szLargeImageText[MAX_PATH];
	char m_szSmallImageKey[MAX_PATH];
public:
	void Initialize();
	void Update();
	void SetData(const char* szApplicationID, const char* szState, const char* szDetails, const char* szLargeImageKey, const char* szLargeImageText, const char* szSmallImageKey);
	long long GetEpochTime();
public:
	static DiscordRPC& GetInstance();
private:
	static DiscordRPC* sg_Instance;
public:
	void Init();
	DiscordRPC();
	virtual ~DiscordRPC();
};

#define g_Discord DiscordRPC::GetInstance()