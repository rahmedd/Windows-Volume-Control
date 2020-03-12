//https://www.codeproject.com/Tips/233484/Change-Master-Volume-in-Visual-Cplusplus
//Original author - Sayyed Mostafa Hashemi

#include <iostream>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <string>

using namespace std;

bool ChangeVolume(double nVolume, bool bScalar)
{

	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;
	double newVolume = nVolume;

	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	IMMDeviceEnumerator* deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	IMMDevice* defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume* endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);

	
	//If 0 mute/keep mute, else unmute
	int currentMute = 0;
	endpointVolume->GetMute(&currentMute);
	if (nVolume == 0) {
		endpointVolume->SetMute(true, NULL);
	}
	else {
		endpointVolume->SetMute(false, NULL);
	}

	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

	if (bScalar == false)
	{
		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
	}
	else if (bScalar == true)
	{
		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
	}
	endpointVolume->Release();

	CoUninitialize();

	return 0;
}

int main(int argc, char* argv[])
{
	string args1;
	string args2;

	if (argc == 2) //Change vol up or down by increment
	{
		args1 = argv[1];
		double conv = stoi(args1);
		conv *= 0.01;

		if (stoi(args1) <= 100 && stoi(args1) >= 0)
		{
			ChangeVolume(conv, true);
		}
		else
		{
			printf("%s\n", "percentage args err!");

		}
	}

	//else if (argc == 3) //change by percentage DOESN'T WORK YET
	//{
	//	args2 = argv[2];
	//	//printf("%s\n", argv[2]);

	//	if (args2 == "up")
	//	{
	//		printf("%s\n", "up!");
	//	}
	//	else if (args2 == "dn")
	//	{
	//		printf("%s\n", "down!");
	//	}
	//	else
	//	{
	//		printf("%s\n", "increment args err!");
	//	}
	//}
	
	else
	{
		printf("%s\n", "args err!");
	}
}
