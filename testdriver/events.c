#pragma warning (disable : 4047)
#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("ImageLoaded: %ls \n", FullImageName->Buffer);

	if (wcsstr(FullImageName->Buffer, L"\\Among.Us.v2020.9.9s\\GameAssembly.dll"))
	{
		DebugMessage("GameAssembly.dll bulundu!\n");
		AmongUsDllAdd = ImageInfo->ImageBase;

		DebugMessage("ProcessID: %d \n", ProcessId);
	}

	return STATUS_SUCCESS;

}