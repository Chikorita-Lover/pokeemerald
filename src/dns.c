#include "global.h"
#include "main.h"
#include "dns.h"
#include "palette.h"
#include "start_menu.h"
#include "overworld.h"
#include "battle_main.h"
#include "rtc.h"
#include "constants/map_types.h"
#include "constants/rgb.h"

  /*******************************************************/
 /*********    Day and Night Configuration     **********/
/********************************************************
 * You can customize the DNS by editing the following   *
 * timelapses and the filters used to change the        *
 * palette colours.                                     *
 * In addition to that, you can also configure which    *
 * palettes are affected by the system, as well as      *
 * establishing sprite palettes exceptions by its TAG.  *
 * 
 * It is highly recommended to read the following config*
 * options, to understand how the dns works.            *
 * ******************************************************/
 
/* Timelapses */
enum
{
    TIME_DAWN,
    TIME_MORNING,
    TIME_DAY,
    TIME_SUNSET,
    TIME_DUSK,
    TIME_NIGHT,
};

/* End hours for each of the timelapses */
#define NIGHT_END_HOUR      6  //22 - 06
#define DAWN_END_HOUR       8  //06 - 08
#define MORNING_END_HOUR    10 //08 - 10
#define DAY_END_HOUR        18 //10 - 18
#define SUNSET_END_HOUR     20 //18 - 20
#define NIGHTFALL_END_HOUR  22 //20 - 22

#define LIGHTNING_END_HOUR      DAWN_END_HOUR
#define LIGHTNING_START_HOUR    19

/* This array contains the colours used for the windows or          *
 * other tiles that have to be illuminated at night.                *
 * You can add or remove light slots as you whish, each entry       *
 * requires the paletteNum and the colourNum of each colour slot,   *
 * as well as the RGB 15 bit colour that's gonna be used as         *
 * "light colour".                                                  */
const struct LightingColor gLightingColours[] =
{
    {
        .paletteNum = 1,
        .colourNum = 9,
        .lightColour = RGB2(31, 31, 23),
    },
    {
        .paletteNum = 1,
        .colourNum = 10,
        .lightColour = RGB2(30, 25, 10),
    },
    {
        .paletteNum = 6,
        .colourNum = 9,
        .lightColour = RGB2(31, 31, 23),
    },
    {
        .paletteNum = 6,
        .colourNum = 10,
        .lightColour = RGB2(30, 25, 10),
    },
    {
        .paletteNum = 8,
        .colourNum = 9,
        .lightColour = RGB2(31, 31, 23),
    },
    {
        .paletteNum = 8,
        .colourNum = 10,
        .lightColour = RGB2(30, 25, 10),
    },
    {
        .paletteNum = 9,
        .colourNum = 9,
        .lightColour = RGB2(31, 31, 23),
    },
    {
        .paletteNum = 9,
        .colourNum = 10,
        .lightColour = RGB2(30, 25, 10),
    },
    {
        .paletteNum = 10,
        .colourNum = 9,
        .lightColour = RGB2(31, 31, 23),
    },
    {
        .paletteNum = 10,
        .colourNum = 10,
        .lightColour = RGB2(30, 25, 10),
    },
};

/* Maptypes that are not affected by DNS */
const u8 gDnsMapExceptions[] =
{
    MAP_TYPE_NONE,
    MAP_TYPE_INDOOR,
    MAP_TYPE_UNDERGROUND,
    MAP_TYPE_SECRET_BASE,
};

/* Configure each palette slot to be affected or not by DNS *
 * while you are in the overworld.                          */
const struct DnsPalExceptions gOWPalExceptions = 
{
    .pal = {
        DNS_PAL_ACTIVE,     //0
        DNS_PAL_ACTIVE,     //1
        DNS_PAL_ACTIVE,     //2
        DNS_PAL_ACTIVE,     //3
        DNS_PAL_ACTIVE,     //4
        DNS_PAL_ACTIVE,     //5
        DNS_PAL_ACTIVE,     //6
        DNS_PAL_ACTIVE,     //7
        DNS_PAL_ACTIVE,     //8
        DNS_PAL_ACTIVE,     //9
        DNS_PAL_ACTIVE,     //10
        DNS_PAL_ACTIVE,     //11
        DNS_PAL_ACTIVE,     //12
        DNS_PAL_EXCEPTION,  //13
        DNS_PAL_EXCEPTION,  //14
        DNS_PAL_EXCEPTION,  //15
        DNS_PAL_ACTIVE,     //16
        DNS_PAL_ACTIVE,     //17
        DNS_PAL_ACTIVE,     //18
        DNS_PAL_ACTIVE,     //19
        DNS_PAL_ACTIVE,     //20
        DNS_PAL_ACTIVE,     //21
        DNS_PAL_ACTIVE,     //22
        DNS_PAL_ACTIVE,     //23
        DNS_PAL_ACTIVE,     //24
        DNS_PAL_ACTIVE,     //25
        DNS_PAL_ACTIVE,     //26
        DNS_PAL_ACTIVE,     //27
        DNS_PAL_ACTIVE,     //28
        DNS_PAL_ACTIVE,     //29
        DNS_PAL_ACTIVE,     //30
        DNS_PAL_ACTIVE,     //31
    }
};

/* Configure each palette slot to be affected or not by DNS *
 * while in combat.                                         */
const struct DnsPalExceptions gCombatPalExceptions =  
{
    .pal = {
        DNS_PAL_EXCEPTION,  //0
        DNS_PAL_EXCEPTION,  //1
        DNS_PAL_ACTIVE,     //2
        DNS_PAL_ACTIVE,     //3
        DNS_PAL_ACTIVE,     //4
        DNS_PAL_EXCEPTION,  //5
        DNS_PAL_ACTIVE,     //6
        DNS_PAL_ACTIVE,     //7
        DNS_PAL_EXCEPTION,  //8
        DNS_PAL_EXCEPTION,  //9
        DNS_PAL_EXCEPTION,  //10
        DNS_PAL_EXCEPTION,  //11
        DNS_PAL_ACTIVE,     //12
        DNS_PAL_ACTIVE,     //13
        DNS_PAL_ACTIVE,     //14
        DNS_PAL_ACTIVE,     //15
        DNS_PAL_EXCEPTION,  //16
        DNS_PAL_EXCEPTION,  //17
        DNS_PAL_EXCEPTION,  //18
        DNS_PAL_EXCEPTION,  //19
        DNS_PAL_EXCEPTION,  //20
        DNS_PAL_EXCEPTION,  //21
        DNS_PAL_EXCEPTION,  //22
        DNS_PAL_EXCEPTION,  //23
        DNS_PAL_EXCEPTION,  //24
        DNS_PAL_EXCEPTION,  //25
        DNS_PAL_EXCEPTION,  //26
        DNS_PAL_EXCEPTION,  //27
        DNS_PAL_EXCEPTION,  //28
        DNS_PAL_EXCEPTION,  //29
        DNS_PAL_EXCEPTION,  //30
        DNS_PAL_EXCEPTION,  //31
    }
};

  /*******************************************************/
 /*************    DNS Colour Filters     ***************/
/*******************************************************/
/* DNS filters are actual 15bit RGB colours.            *
 * This colours R - G - B channels are substracted from *
 * the original colour in the palette buffer during the *
 * transfer from the buffer to the palette RAM.         *
 *                                                      *
 *  [BUFFER] -> (Value - Filter) -> [PAL_RAM]           *
 *                                                      *
 * This means that you shouln't use too high values for *
 * RGB channels in the filters. Otherwie, the channels  *
 * will easily reach 0, giving you plain colours.       *
 * I Suggest to not use channels with a value above 16. *
 *                                                      *
 * Feel free to experiment with your own filters.       *
 * ******************************************************
 * DNS Alternative Filtering System                     *
 * I've created and alternative filtering system, which *
 * substracts the level of each channel porportionally. *
 * I personally prefer this alternative method, since   *
 * the filters are blended "softer".                    *
 * This is more noticeable with the darker filters.     *
 */

const u16 gDawnFilters[] =
{
    RGB2(12, 12, 0),
    RGB2(10, 11, 0),
    RGB2(9, 10, 0),
    RGB2(7, 10, 1),
    RGB2(6, 9, 1),
    RGB2(4, 8, 1),
    RGB2(2, 7, 1),
    RGB2(1, 6, 1),
    RGB2(0, 6, 2),
    RGB2(0, 5, 2),
    RGB2(0, 4, 2),
    RGB2(0, 3, 2),
    RGB2(0, 2, 2),
    RGB2(0, 2, 3),
    RGB2(0, 1, 3),
};

const u16 gMorningFilters[] =
{
    RGB2(0, 0, 3),
    RGB2(0, 0, 2),
    RGB2(0, 0, 1),
};

const u16 gDayFilter = RGB2(0, 0, 0);

const u16 gSunsetFilters[] = 
{
    RGB2(0, 0, 0),
    RGB2(0, 1, 1),
    RGB2(0, 1, 1),
    RGB2(0, 2, 2),
    RGB2(0, 2, 3),
    RGB2(0, 3, 3),
    RGB2(0, 3, 4),
    RGB2(0, 4, 5),
    RGB2(0, 4, 5),
    RGB2(0, 5, 6),
    RGB2(0, 5, 7),
    RGB2(0, 6, 7),
    RGB2(0, 6, 8),
    RGB2(0, 7, 9),
    RGB2(0, 7, 9),
};

const u16 gDuskFilters[] = 
{
    RGB2(0, 8, 10),
    RGB2(1, 8, 9),
    RGB2(2, 9, 9),
    RGB2(2, 9, 8),
    RGB2(3, 9, 7),
    RGB2(4, 9, 7),
    RGB2(5, 10, 6),
    RGB2(6, 10, 5),
    RGB2(6, 10, 5),
    RGB2(7, 10, 4),
    RGB2(8, 11, 3),
    RGB2(9, 11, 3),
    RGB2(10, 11, 2),
    RGB2(10, 11, 1),
    RGB2(11, 12, 1),
};

const u16 gNightFilter = RGB2(12, 12, 0);

/*************   SpritePalette Dns exceptions by TAG   **************
 * If you are using any dynamic sprite palette allocation system,   *
 * you will most likely want to use this system to avoid certain    *
 * palette tags to be "banned" from dns, as the palettes may get    *
 * loaded in different slots each time.                             */
const u16 gPaletteTagExceptions[] =
{
    0xD6FF, //TAG_HEALTHBOX_PAL
    0xD704, //TAG_HEALTHBAR_PAL
    0xD710, //TAG_STATUS_SUMMARY_BAR_PAL
    0xD712, //TAG_STATUS_SUMMARY_BALLS_PAL
};

/***********************************************
 * --------- DNS CONFIGURATION END ----------- *
 * ******************************************* */


//Functions
static u16 DnsApplyFilterToColour(u16 colour, u16 filter);
static u16 DnsApplyProportionalFilterToColour(u16 colour, u16 filter);
static void DoDnsLightning();
static u16 GetDNSFilter();
static bool8 IsMapDNSException();
static bool8 IsSpritePaletteTagDnsException(u8 palNum);
static bool8 IsOverworld();
static bool8 IsCombat();
static bool8 IsLightActive();

//Dns palette buffer in EWRAM
ALIGNED(4) EWRAM_DATA static u16 sDnsPaletteDmaBuffer[512] = {0};


/* **************************************************** *
 * **************** D&N for pokeemerald *************** *
 * **************************************************** *
 * Based on Prime Dialga DNS for Pokemon GBA Games.     *
 * Additional credits to Andrea & Eing                  *
 * Author: Xhyz/Samu                                    *
 ****************************************************** */

//Called from TransferPlttBuffer
void DnsTransferPlttBuffer(void *src, void *dest)
{
    if ((IsOverworld() || IsCombat()) && !IsMapDNSException()) 
    {
        DmaCopy16(3, sDnsPaletteDmaBuffer, dest, PLTT_SIZE);
    }
    else
    {
        DmaCopy16(3, src, dest, PLTT_SIZE);
    }
}

/* Applies filter to palette colours, stores new palettes in EWRAM buffer.   *
 * It must be called from CB2 if the DNS wants to be used (similar to        *
 * TransferPlttBuffer)  in VBlank callbacks                                  */
void DnsApplyFilters()
{
    u8 palNum, colNum;
    u16 colour, rgbFilter;
    struct DnsPalExceptions palExceptionFlags;

    rgbFilter = GetDNSFilter();

    palExceptionFlags = gMain.inBattle ? gCombatPalExceptions : gOWPalExceptions;   //Init pal exception slots

    for (palNum = 0; palNum < 32; palNum++)
        if (palExceptionFlags.pal[palNum] && (palNum < 15 || !IsSpritePaletteTagDnsException(palNum - 16)))
            for (colNum = 0; colNum < 16; colNum++) //Transfer filtered palette to buffer
                sDnsPaletteDmaBuffer[palNum * 16 + colNum] = DnsApplyProportionalFilterToColour(gPlttBufferFaded[palNum * 16 + colNum], rgbFilter);
        else
            for (colNum = 0; colNum < 16; colNum++)  //Transfers palette to buffer without filtering
                sDnsPaletteDmaBuffer[palNum * 16 + colNum] = gPlttBufferFaded[palNum * 16 + colNum];      

    if (!IsMapDNSException() && IsLightActive() && !gMain.inBattle)
        DoDnsLightning();
}

//Applies filter to a colour. Filters RGB channels are substracted from colour RGB channels.
//Based on Andrea's DNS filtering system 
static u16 DnsApplyFilterToColour(u16 color, u16 filter)
{
    u16 red, green, blue;

    red = (color & 0x1F) - (filter & 0x1F);
    green = ((color & 0x3E0) - (filter & 0x3E0)) >> 5;
    blue = ((color & 0x7C00) - (filter & 0x7C00)) >> 10;

    return RGB2(red <= 31 ? red : 0, green <= 31 ? green : 0, blue <= 31 ? blue : 0);
}

/*Alternative way to apply filter. Works similar to the first one, but colours are substracted PROPORTIONALLY.
This system is great if you want to avoid colours with low rgb channels getting donw to 0 too fast.
That's something that can easily happen with above Andrea's filtering system.*/
static u16 DnsApplyProportionalFilterToColour(u16 color, u16 filter)
{
    u32 red, green, blue;

    red = (color & 0x1F) * (0x1F - (filter & 0x1F)) >> 5;
    green = ((color & 0x3E0) >> 5) * ((0x3E0 - (filter & 0x3E0)) >> 5) >> 5;
    blue = ((color & 0x7C00) >> 10) * ((0x7C00 - (filter & 0x7C00)) >> 10) >> 5;

    return RGB2(red <= 31 ? red : 0, green <= 31 ? green : 0, blue <= 31 ? blue : 0);  
}

//returns the filter to use depending on RTC time.
static u16 GetDNSFilter()
{
    u8 hour = gLocalTime.hours;
    u8 minutes = gLocalTime.minutes;
    u8 time = hour % 2 * 60 + minutes;

    switch(GetDnsTimeLapse(hour))
    {
        case TIME_DAWN:
            return gDawnFilters[time >> 3];
        case TIME_MORNING:
            return gMorningFilters[time >> 5];
        case TIME_DAY:
            return gDayFilter;
        case TIME_SUNSET:
            return gSunsetFilters[time >> 3];
        case TIME_DUSK:
            return gDuskFilters[time >> 3];
        case TIME_NIGHT:
            return gNightFilter;
    }

    return 0;
}

static void DoDnsLightning()
{
    u8 i;

    for (i = 0; i < sizeof(gLightingColours)/sizeof(gLightingColours[0]); i++)
    {
        u16 colourSlot = gLightingColours[i].paletteNum * 16 + gLightingColours[i].colourNum;
        
        if (gPlttBufferFaded[colourSlot] != 0x0000)
        {
            if (gPaletteFade.active)
            {
                sDnsPaletteDmaBuffer[colourSlot] = gPlttBufferFaded[colourSlot];
                gPlttBufferUnfaded[colourSlot] = gLightingColours[i].lightColour;
            }
            else
            {
                sDnsPaletteDmaBuffer[colourSlot] = gLightingColours[i].lightColour;
            }
        }
    }
}

//Returns Dns time lapse
u8 GetDnsTimeLapse(u8 hour)
{
    if (hour < NIGHT_END_HOUR)
        return TIME_NIGHT;
    else if (hour < DAWN_END_HOUR)
        return TIME_DAWN;
    else if (hour < MORNING_END_HOUR)
        return TIME_MORNING;
    else if (hour < DAY_END_HOUR)
        return TIME_DAY;
    else if (hour < SUNSET_END_HOUR)
        return TIME_SUNSET;
    else if (hour < NIGHTFALL_END_HOUR)
        return TIME_DUSK;
    else 
        return TIME_NIGHT;
}

//Checks if current map is affected by dns
static bool8 IsMapDNSException()
{
    u8 i;
    for (i=0; i < sizeof(gDnsMapExceptions)/sizeof(gDnsMapExceptions[0]); i++)
        if (gMapHeader.mapType == gDnsMapExceptions[i])
            return TRUE;
    return FALSE;
}

//Returns true if the palette should not be affected by DNS filtering
static bool8 IsSpritePaletteTagDnsException(u8 palNum)
{
    u8 i;

    for (i = 0; i < sizeof(gPaletteTagExceptions)/sizeof(gPaletteTagExceptions[0]); i++)
        if (GetSpritePaletteTagByPaletteNum(palNum) == gPaletteTagExceptions[i])
            return TRUE;
    return FALSE;
}

//Returns true if overworld is running
static bool8 IsOverworld()
{
    if (gMain.callback2 == CB2_Overworld || gMain.callback2 ==CB2_OverworldBasic)
        return TRUE;
    else
        return FALSE;
}

//Returns true if combat is running
static bool8 IsCombat()
{
    if (gMain.callback2 == BattleMainCB2)
        return TRUE;
    else
        return FALSE;
}

static bool8 IsLightActive()
{
    if (gLocalTime.hours >= LIGHTNING_START_HOUR || gLocalTime.hours < LIGHTNING_END_HOUR)
        return TRUE;
    return FALSE;
}
