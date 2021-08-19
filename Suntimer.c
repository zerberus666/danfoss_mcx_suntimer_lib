
#include "Suntimer_Brick.lib"





struct Suntimer
{
    // public
    DINT OffsetSunrise = 20; // OffsetSunrise
    DINT OffsetSunset = -20; // OffsetSunset
    DINT Latitude = 5575222; // Latitude
    DINT Longtitude = 3761556; // Longtitude
    INT Timezone = 3; // Timezone
    BOOL xNight = 0;
    BOOL xDay;

    // private
    Time_f Time_f_1;
    SunsetSunrise SunsetSunrise_1;
    DT_TO_TOD DT_TO_TOD_1;
    DT_TO_TOD DT_TO_TOD_2;
    DT_TO_TOD DT_TO_TOD_3;
    ADD_TOD_TIME ADD_TOD_TIME_1;
    ADD_TOD_TIME ADD_TOD_TIME_2;
    MUL MUL_1;
    MUL MUL_2;
    Timecheck Timecheck_2;
    NOT NOT_1;

    void Init()
    {
        Time_f_1.Init();
        SunsetSunrise_1.DayOfYear = Time_f_1.DayOfYear;
        SunsetSunrise_1.Timezone = Timezone;
        SunsetSunrise_1.Latitude = Latitude;
        SunsetSunrise_1.Longtitude = Longtitude;
        SunsetSunrise_1.Init();
        DT_TO_TOD_1.IN = Time_f_1.dtTime;
        DT_TO_TOD_1.Init();
        DT_TO_TOD_2.IN = SunsetSunrise_1.dtSunrise;
        DT_TO_TOD_2.Init();
        DT_TO_TOD_3.IN = SunsetSunrise_1.dtSunset;
        DT_TO_TOD_3.Init();
        ADD_TOD_TIME_1.IN2 = MUL_2.OUT;
        ADD_TOD_TIME_1.IN1 = DT_TO_TOD_2.OUT;
        ADD_TOD_TIME_1.Init();
        ADD_TOD_TIME_2.IN2 = DT_TO_TOD_3.OUT;
        ADD_TOD_TIME_2.IN1 = MUL_1.OUT;
        ADD_TOD_TIME_2.Init();
        MUL_1.IN2 = 60;
        MUL_1.IN1 = OffsetSunset;
        MUL_1.Init();
        MUL_2.IN1 = 60;
        MUL_2.IN2 = OffsetSunrise;
        MUL_2.Init();
        Timecheck_2.todTd = DT_TO_TOD_1.OUT;
        Timecheck_2.todStart = ADD_TOD_TIME_2.OUT;
        Timecheck_2.todStop = ADD_TOD_TIME_1.OUT;
        Timecheck_2.Init();
        NOT_1.IN = Timecheck_2.xBetween;
        NOT_1.Init();
    }

    void Main()
    {
        Time_f_1.Main();
        SunsetSunrise_1.DayOfYear = Time_f_1.DayOfYear;
        SunsetSunrise_1.Timezone = Timezone;
        SunsetSunrise_1.Latitude = Latitude;
        SunsetSunrise_1.Longtitude = Longtitude;
        SunsetSunrise_1.Main();
        DT_TO_TOD_1.IN = Time_f_1.dtTime;
        DT_TO_TOD_1.Main();
        DT_TO_TOD_2.IN = SunsetSunrise_1.dtSunrise;
        DT_TO_TOD_2.Main();
        DT_TO_TOD_3.IN = SunsetSunrise_1.dtSunset;
        DT_TO_TOD_3.Main();
        ADD_TOD_TIME_1.IN2 = MUL_2.OUT;
        ADD_TOD_TIME_1.IN1 = DT_TO_TOD_2.OUT;
        ADD_TOD_TIME_1.Main();
        ADD_TOD_TIME_2.IN2 = DT_TO_TOD_3.OUT;
        ADD_TOD_TIME_2.IN1 = MUL_1.OUT;
        ADD_TOD_TIME_2.Main();
        MUL_1.IN2 = 60;
        MUL_1.IN1 = OffsetSunset;
        MUL_1.Main();
        MUL_2.IN1 = 60;
        MUL_2.IN2 = OffsetSunrise;
        MUL_2.Main();
        xNight = Timecheck_2.xBetween;
        Timecheck_2.todTd = DT_TO_TOD_1.OUT;
        Timecheck_2.todStart = ADD_TOD_TIME_2.OUT;
        Timecheck_2.todStop = ADD_TOD_TIME_1.OUT;
        Timecheck_2.Main();
        xDay = NOT_1.OUT;
        NOT_1.IN = Timecheck_2.xBetween;
        NOT_1.Main();
    }
};


