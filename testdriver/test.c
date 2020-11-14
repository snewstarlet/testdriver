#pragma warning (disable : 4100 4047 4024)

#include "events.h"
#include "test.h"
#include "messages.h"
#include "data.h"
#include "com.h"
#include <ntddk.h>



NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = UnloadDriver;
	DebugMessage("Sa krds hosgeldin among us ac bakim");


	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\test");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\test");
	
	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	DebugMessage("grsrz krds driver kacar");

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	return STATUS_SUCCESS;
}