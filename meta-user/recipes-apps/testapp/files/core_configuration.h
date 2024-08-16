/*********************************************************************************************
 *@file:       core_configuration.h
 *
 *@Created:    25-07-2024
 *
 *@brief:      This file implements to perform 32-bit write operation on registers.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

/* Macros */
#define Driver_path        "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1
#define DIR_LOG            printf         /* Macro for information messages */
#define DIR_ERRLOG         printf         /* Macro for error messages */

/* Operation codes */
#define OP_32BIT_WRITE     6

/* Structure to store memory operation details */
struct core_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

unsigned int write_operation[] = {
    0x80116000, 0x80116004, 0x80116008, 0x8011600C, 0x80116010, 0x80116014, 0x80116018, 0x8011601C, 0x80116020,
    0x80116024, 0x80116028, 0x8011602C, 0x80116030, 0x80116034, 0x80116038, 0x8011603C, 0x80116040, 0x80116044,
    0x80116048, 0x8011604C, 0x80116050, 0x80116054, 0x80116058, 0x8011605C, 0x80116060, 0x80116064, 0x80116068,
    0x8011606C, 0x80116070, 0x80116074, 0x80116078, 0x8011607C, 0x80116080, 0x80116084, 0x80116088, 0x8011608C,
    0x80116090, 0x80116094, 0x80116098, 0x8011609C, 0x801160A0, 0x801160A4, 0x801160A8, 0x801160AC, 0x801160B0,
    0x801160B4, 0x801160B8, 0x801160BC, 0x801160C0, 0x801160C4, 0x801160C8, 0x801160CC, 0x801160D0, 0x801160D4,
    0x801160D8, 0x801160DC, 0x801160E0, 0x801160E4, 0x801160E8, 0x801160EC, 0x801160F0, 0x801160F4, 0x801160F8,
    0x801160FC, 0x80116100, 0x80116104, 0x80116108, 0x8011610C, 0x80116110, 0x80116114, 0x80116118, 0x8011611C,
    0x80116120, 0x80116124, 0x80116128, 0x8011612C, 0x80116130, 0x80116134, 0x80116138, 0x8011613C, 0x80116140,
    0x80116144, 0x80116148, 0x8011614C, 0x80116150, 0x80116154, 0x80116158, 0x8011615C, 0x80116160, 0x80116164,
    0x80116168, 0x8011616C, 0x80116170, 0x80116174, 0x80116178, 0x8011617C, 0x80116180, 0x80116184, 0x80116188,
    0x8011618C, 0x80116190, 0x80116194, 0x80116198, 0x8011619C, 0x801161A0, 0x801161A4, 0x801161A8, 0x801161AC,
    0x801161B0, 0x801161B4, 0x801161B8, 0x801161BC, 0x801161C0, 0x801161C4, 0x801161C8, 0x801161CC, 0x801161D0,
    0x801161D4, 0x801161D8, 0x801161DC, 0x801161E0, 0x801161E4, 0x801161E8, 0x801161EC, 0x801161F0, 0x801161F4,
    0x801161F8, 0x801161FC, 0x80116200, 0x80116204, 0x80116208, 0x8011620C, 0x80116210, 0x80116214, 0x80116218,
    0x8011621C, 0x80116220, 0x80116224, 0x80116228, 0x8011622C, 0x80116230, 0x80116234, 0x80116238, 0x8011623C,
    0x80116240, 0x80116244, 0x80116248, 0x8011624C
};

unsigned int data_to_write[] = {
        0x8B000987, 0x00000000, 0x00000001, 0xDD9EB80C, 0x93FC00C8, 0x43B275BA, 0x04000000, 0x00000001, 0x281E1ECC,
        0x000640C8, 0xB47D33B3, 0x07000000, 0x00000003, 0xC5B7AC97, 0x00000000, 0x00000000, 0xC0000000, 0xE0B104DF,
        0x0A000000, 0x00000011, 0xC737F732, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x10D76EAD, 0x01000000, 0x00000001, 0xE0FE91BC, 0x40000000, 0x57989E8C, 0x02000000,
        0x00000002, 0xB5EB4482, 0x40000000, 0x0FFED000, 0xAAD863B2, 0x03000000, 0x00000001, 0x9A3EC2DC, 0x00640000,
        0x20D571BF, 0x05000000, 0x00000003, 0xBF77FFF7, 0x00000000, 0x00000000, 0x00000000, 0x7BD5C66F, 0x06000000,
        0x00000001, 0x52DE4DAC, 0x7FD01000, 0x7CE0D5DE, 0x08000000, 0x00000002, 0xFF5B5C23, 0x00000000, 0xE7F9F400,
        0x2CFF294A, 0x09000000, 0x00000001, 0xD08EDA7D, 0x00000000, 0x2144DF1C, 0x0B000000, 0x00000003, 0x00474196,
        0x0E000000, 0x10080000, 0x077FFA00, 0xB1340E8E, 0x20000000, 0x00000003, 0xB6565F83, 0x00030000, 0x72A70200,
        0x03000000, 0x197FAF06, 0x21000000, 0x00000003, 0x8B367633, 0x9C000000, 0x236781CA, 0x43222366, 0x6DC2A1A6,
        0x22000000, 0x00000001, 0x669FC468, 0xE0E072A7, 0x58F9530A, 0x23000000, 0x0000000E, 0x039CFD8E, 0x00000000,
        0x0A47FF00, 0x00032401, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02000800, 0x00000000,
        0x00000000, 0xFFFF0000, 0x0000000F, 0x00000000, 0x0B4CF3F1, 0x24000000, 0x00000001, 0xE9DF31C8, 0x40000000,
        0x57989E8C, 0x25000000, 0x00000002, 0xC60AB796, 0x80000000, 0x21F00065, 0x80E99929, 0x27000000, 0x00000001,
        0xAE7F4B18, 0x00000000, 0x2144DF1C, 0x29000000, 0x00000003, 0xBB463DF2, 0x88000000, 0x7802800A, 0x1FE20040,
        0x41B05CA1, 0x00000000, 0x00000000, 0xDBB787D4
};

const char *register_name[] = {
	"Device_id", "Schedule Table", "BlockLength", "Local crc", "DATA", "Local crc", "Schedule Entry Points Table", "BlockLength", 
	"Local crc", "DATA", "Local crc", "Schedule Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", 
	"Clock Synchronization Parameter", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "[127:96]", "[159:128]", 
	"[191:160]", "[223:192]", "[255:224]", "[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]", 
	"[479:448]", "[511:480]", "[543:512]", "Local crc", "IC/RM Table", "BlockLength", "Local crc", "DATA", "Local crc", "Output VL Table", 
	"BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "crc_std", "Input VL Lookup Table", "BlockLength", "Local crc", "DATA[31:0]", 
	"Local crc", "Best-Effort Filter Table", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Partition Space Table", 
	"BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Shaping Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "Local crc", 
	"IC/RM Parameters", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "General Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", 
	"[95:64]", "Local crc", "Output Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Output Port Table",
	"BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Output Partition Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc",
	"Input Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "[127:96]", "[159:128]", "[191:160]", "[223:192]", "[255:224]",
	"[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]", "crc_std", "Input Lookup Table", "BlockLength", "Local crc", "DATA[31:0]", 
	"Local crc", "Input Port Table", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "Local crc", "Input Defragmentation Table", "BlockLength", "Local crc", 
	"DATA[31:0]", "Local crc", "Output Sub-VL Table", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "block id 0", 
	"eof file(block length zero)", "koopman Global crc"
};

/* Function: Core_configuration_main
 * ------------------------
 * This function performs the fixed 32-bit write operation on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is written successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform write operation, it will return DIR_FAILURE.
 */
int core_configuration_main(void);
