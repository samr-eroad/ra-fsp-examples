/***********************************************************************************************************************
 * File Name    : rtc_app.h
 * Description  : Contains declarations of data structures and functions used in rtc_app.c.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *
 * This file is part of Renesas RA Flex Software Package (FSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas FSP license agreement. Unless otherwise agreed in an FSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

#ifndef RTC_APP_H_
#define RTC_APP_H_

#include "sntp_client_thread.h"
#include "ctype.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* macros to print info, error and trap the error.*/
#define PRINT_INFO_STR(str)  app_rtt_print_data(RTT_OUTPUT_MESSAGE_APP_INFO_STR, sizeof(str), str);
#define PRINT_ERR_STR(str)   app_rtt_print_data(RTT_OUTPUT_MESSAGE_APP_ERR_STR, sizeof(str), str);
#define ERROR_TRAP(err)      app_rtt_print_data(RTT_OUTPUT_MESSAGE_APP_ERR_TRAP, sizeof(UINT *), &err);

/* MACRO for null character */
#define NULL_CHAR   '\0'

/* MACRO for max bytes received */
#define MAX_BYTES            (32U)
#define TIME_BUFF_SIZE       (10U)

/*MACROs to adjust month and year values */
#define MON_ADJUST_VALUE      (1)
#define YEAR_ADJUST_VALUE     (1900)

/* Time zone offset value can be changed as per required timezone.
 * to change the offset value, Refer -
 * https://www.epochconverter.com/timezones
 * All region time zone offset value are present in above URL.*/
/* Time zone offset value as per IST.*/
#define TIME_ZONE_OFFSET      (19800)

/* ENUM for ASCII code */
typedef enum e_ascii_codes
{
    ASCII_ZERO_CODE = 48,
    ASCII_CHAR_A    = 65,
    ASCII_LOWER_A   = 0x61,
    ASCII_LOWER_N   = 0x6E,
    ASCII_LOWER_R   = 0x72,
    ASCII_LOWER_P   = 0x70
}ascii_codes_t;

/* ENUM for month conversion processing */
typedef enum e_month_convert_val
{
    JAN_JUN_JUL  = 0x4A,
    FEB          = 0x46,
    MAR_MAY      = 0x4D,
    APR_AUG      = 0x41,
    SEP          = 0x53,
    OCT          = 0x4F,
    NOV          = 0x4E,
    DEC          = 0x44
}month_convert_val_t;

/* function declarations */
fsp_err_t update_time_stamp_to_rtc_block(char * const time_data);
fsp_err_t rtc_init_and_display_time(void);
fsp_err_t set_rtc_calendar_time(rtc_time_t * set_time);
fsp_err_t get_rtc_calendar_time(rtc_time_t * get_time);
void rtc_deinit(void);
void rtc_month_year_readability_update(rtc_time_t * time);
void rtc_month_year_time_format_update(rtc_time_t * time);
void assign_month_value(rtc_time_t * time, char * read_buffer);
void convert_network_timestamp_to_rtc_block(rtc_time_t * time, char * read_buffer);

#endif /* RTC_APP_H_ */
