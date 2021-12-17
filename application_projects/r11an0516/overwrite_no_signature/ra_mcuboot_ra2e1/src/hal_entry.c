#include "hal_data.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event) BSP_PLACE_IN_SECTION(".code_in_gap*");
FSP_CPP_FOOTER

/* Use the following commands to sign the image, replacing ${ProjName}.elf with the path to your image elf file.
 * Regenerate this template if any MCUboot properties change in the bootloader project.
 Make the following updates to convert to binary, then sign image 1 (primary slot: 2000, secondary/upgrade slot: 4000):
 1. Update ${ProjName} to reflect the location of the image 1 .elf file
 2. Update ${workspace_loc:ra_mcuboot_ra2e1} to reflect the location of the root of the bootloader project
 arm-none-eabi-objcopy -O binary ${ProjName}.elf ${ProjName}.bin & python ${workspace_loc:ra_mcuboot_ra2e1}/ra/mcu-tools/MCUboot/scripts/imgtool.py sign --version 1.0.0+0 --header-size 0x100 --align 8 --max-align 8 --slot-size 0x2000 --max-sectors 4 --overwrite-only  --confirm --pad-header ${ProjName}.bin ${ProjName}_signed.bin
 */

void mcuboot_quick_setup() BSP_PLACE_IN_SECTION(".code_in_gap*");
/* Quick setup for MCUboot.
 *
 * To update the linker regions of an application to be used with this bootloader, add a the *.bld file created during the
 * build as a File property in e2 studio or RASC under Project > Properties, then C/C++ Build > Build Variables with variable
 * name BootloaderDataFile.
 */
void mcuboot_quick_setup()
{
#ifdef MCUBOOT_USE_MBED_TLS

    /* Initialize mbedtls. */
    mbedtls_platform_context ctx = {0};
    assert(0 == mbedtls_platform_setup(&ctx));
#elif (defined(MCUBOOT_USE_TINYCRYPT) && defined(RM_MCUBOOT_PORT_USE_TINYCRYPT_ACCELERATION))

    /* Initialize TinyCrypt port. */
    assert(FSP_SUCCESS == RM_TINCYRYPT_PORT_Init());
#elif (defined(MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK))

/* Initialize Custom Crypto (Protected Mode) driver. */
    assert(FSP_SUCCESS == R_SCE_Open(&sce_ctrl, &sce_cfg));
#endif
#if 0
    /* (Optional, not required if --pad is used during signing) To check for updates, call boot_set_pending. */
    bool update = 0;
    if (update)
    {
        boot_set_pending(0);
    }
#endif

    /* Verify the boot image and get its location. */
    struct boot_rsp rsp;
    assert(0 == boot_go(&rsp));

    /* Enter the application. */
    RM_MCUBOOT_PORT_BootApp(&rsp);
}

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */
    mcuboot_quick_setup();
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
  //      R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif
