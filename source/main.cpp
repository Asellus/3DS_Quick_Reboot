#include <3ds.h>

// https://www.3dbrew.org/wiki/PTMSYSM:LaunchFIRMRebootSystem
void PTM_RebootAsync(void) {

	ptmSysmInit();

	Handle serviceHandle = 0;
	Result result = srvGetServiceHandle(&serviceHandle, "ptm:sysm");
	if (result != 0) {
		return;
	}

	u32 *commandBuffer = getThreadCommandBuffer();
	commandBuffer[0] = 0x04090080;
	commandBuffer[1] = 0x00000000;
	commandBuffer[2] = 0x00000000;

	svcSendSyncRequest(serviceHandle);
	svcCloseHandle(serviceHandle);

	ptmSysmExit();
}

int main(int argc, char **argv) {

	// without one iteration of the APT main loop.
	aptMainLoop();

	PTM_RebootAsync();

	return 0;
}
