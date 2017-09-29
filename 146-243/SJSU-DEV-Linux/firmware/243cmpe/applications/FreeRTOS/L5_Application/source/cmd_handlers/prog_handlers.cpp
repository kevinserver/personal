#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "ff.h"
#include "storage.hpp"
#include "fat/disk/spi_flash.h"
#include "command_handler.hpp"
#include "lpc_sys.h"
#include "chip_info.h"



CMD_HANDLER_FUNC(flashProgHandler)
{
    FIL file;
    const int maxChars = 12;

    if (cmdParams.getLen() >= maxChars) {
        output.printf("Filename should be less than %i chars\n", maxChars);
    }
    else if (FR_OK == f_open(&file, cmdParams(), FA_OPEN_EXISTING | FA_READ))
    {
        f_close(&file);
        output.printf("%s (%u bytes) will be programmed.\n"
                      "Rebooting now to upgrade firmware!\n\n",
                      cmdParams(), file.fsize);


        output.flush();
        vTaskDelay(10);

        /**
         * Disable interrupts otherwise the register we use to store the "program command"
         * is re-written by FreeRTOS kernel interrupt where FreeRTOS stores the last
         * running task name.
         */
        taskDISABLE_INTERRUPTS();
        chip_program_from_filename(cmdParams());
        sys_reboot();
    }
    else {
        output.printf("Unable to open '%s'\n", cmdParams());
    }
    return true;
}

CMD_HANDLER_FUNC(getFileHandler)
{
    const int maxBufferSize = 1024;
    static char *spBuffer = (char*) malloc(maxBufferSize);

    /**
     * Packet format:
     * buffer <offset> <num bytes> ...
     * commit <filename> <file offset> <num bytes from buffer>
     */
    if (cmdParams.beginsWithIgnoreCase("commit"))
    {
        char filename[128] = { 0 };
        int offset = 0;
        int size = 0;
        cmdParams.scanf("%*s %128s %i %i", &filename[0], &offset, &size);

        FRESULT writeStatus = FR_INT_ERR;
        if(0 == offset) {
            writeStatus = Storage::write(filename, spBuffer, size);
        }
        else {
            writeStatus = Storage::append(filename, spBuffer, size, offset);
        }
        output.printf(FR_OK == writeStatus ? "OK\n" : "File write error\n");
    }
    else if (cmdParams.beginsWithIgnoreCase("buffer"))
    {
        int offset = 0;
        int numBytes = 0;
        int checksum = 0;
        char c = 0;

        cmdParams.scanf("%*s %i %i", &offset, &numBytes);

        if (offset + numBytes > maxBufferSize) {
            output.printf("ERROR: Max buffer size is %i bytes\n", maxBufferSize);
            return true;
        }

        for(int i=offset; i - offset < numBytes && i < maxBufferSize; i++) {
            if(! output.getChar(&c, OS_MS(2000))) {
                output.printf("ERROR: TIMEOUT\n");
                return true;
            }

            spBuffer[i] = c;
            checksum += c;
        }

        output.printf("Checksum %i\n", checksum);
    }
    else {
        return false;
    }

    return true;
}

CMD_HANDLER_FUNC(signalHelpHandler)
{
    //save pin functionality
    uint32_t savePINCON = LPC_PINCON->PINSEL2;
    uint32_t saveFIODIR = LPC_GPIO1->FIODIR;

    LPC_PINCON->PINSEL2 &= ~(0xCCF);
    LPC_GPIO1->FIODIR |= 0x113;

    for (uint8_t i = 0; i < 3; i++){
        LPC_GPIO1->FIOCLR = 0x113;
        vTaskDelay(500);
        LPC_GPIO1->FIOSET = 0x113;
        vTaskDelay(500);
    }
    for (uint8_t i = 0; i < 3; i++){
        LPC_GPIO1->FIOCLR = 0x113;
        vTaskDelay(250);
        LPC_GPIO1->FIOSET = 0x113;
        vTaskDelay(250);
    }
    for (uint8_t i = 0; i < 3; i++){
        LPC_GPIO1->FIOCLR = 0x113;
        vTaskDelay(500);
        LPC_GPIO1->FIOSET = 0x113;
        vTaskDelay(500);
    }

    printf("Help has been signaled (poorly). Please remain calm.\n");
    vTaskDelay(2000);
    printf("Deep breaths.\n");
    vTaskDelay(2000);
    printf("Deeper.\n");
    vTaskDelay(2000);
    printf("DEEPER!\n");
    vTaskDelay(2000);
    printf("Good. :)\n");
    vTaskDelay(1000);


    LPC_PINCON->PINSEL2 = savePINCON;
    LPC_GPIO1->FIODIR = saveFIODIR;

    return true;
}