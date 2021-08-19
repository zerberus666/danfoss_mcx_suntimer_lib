//#define M_PI ((float)3.141592653589793)
#define M_PI12 (M_PI / 12.0)
#define M_PI6 (M_PI / 6.0)
#define M_PI2 (M_PI / 2.0)
/* square root of 3 */
#define SQRT3 1.732050807569

#define HOUR_T	3600	// 1 hour in seconds
#define DAY_T	86400	//1 day in seconds

float Arctan(float x)
{
	int sta = 0;
	int sp = 0;
	float x2;
	float a;
	/* check up the sign change */
	if (x < 0.0)
	{
		x = -1.0 * x;
		sta = sta | 1;
	}
	/* check up the invertation */
	if (x > 1.0)
	{
		x = 1.0 / x;
		sta = sta | 2;
	}
	/* process shrinking the domain until x<PI/12 */
	while (x > M_PI12)
	{
		sp = sp + 1;
		a = x + SQRT3;
		a = 1.0 / a;
		x = x * SQRT3;
		x = x - 1.0;
		x = x * a;
	}
	/* calculation core */
	x2 = x * x;
	a = x2 + 1.4087812;
	a = 0.55913709 / a;
	a = a + 0.60310579;
	a = a - 0.05160454 * x2;
	a = a * x;
	/* process until sp=0 */
	while (sp > 0)
	{
		a = a + M_PI6;
		sp = sp - 1;
	}
	/* invertation took place */
	if (sta & 2)
		a = M_PI2 - a;
	/* sign change took place */
	if (sta & 1)
		a = -1.0 * a;
	return (a);
}

float Arcsin(float x)
{
	/* check for exceptions */
	if (x < -1.0) //out of range
	{
		//*a = -1.0 * M_PI2;
		return (-1.0 * M_PI2);
	}
	if (x == -1.0)
	{
		//*a = -1.0 * M_PI2;
		return (-1.0 * M_PI2);
	}
	if (x > 1.0) //out of range
	{
		//*a = M_PI2;
		return (M_PI2);
	}
	if (x == 1.0)
	{
		//*a = M_PI2;
		return (M_PI2);
	}
	/* transform the argument */
	x = x / sqrtf(1.0 - x * x);
	//*a = Arctan(x);
	return (Arctan(x));
}

float Arccos(float x)
{
	//a = M_PI2 - Arcsin(x);
	return (M_PI2 - Arcsin(x));
}

float Rad(float x) //this function converts Radiant to degrees
{
	return (fmodf(0.0174532925199433 * x, M_PI2));
}

struct Time_f
{
	// public
	INT Day;
	INT Month;
	INT Hour;
	INT Min;
	INT Year;
	INT DayOfYear;
	DINT dtTime;

	// private

	void Init()
	{
	}

	void Main()
	{
		TDateTime td;
		if (td.LoadRTC() == errOk)
		{
			td.Explode();
			Min = td.Minutes;
			Hour = td.Hours;
			Month = td.Month;
			Day = td.Day;
			Year = td.Year;
			DayOfYear = td.DayOfYear();
			dtTime = td.GetTime;
		}
	}
};

struct SunsetSunrise
{
	// public
	DINT Latitude;
	DINT Longtitude;
	INT DayOfYear;
	INT MiddayHours;
	INT MiddayMins;
	DINT Test;
	INT SunRiseHours;
	INT SunRiseMins;
	INT SunSetHours;
	INT SunSetMins;
	INT Timezone;
	DINT dtSunrise;
    DINT dtSunset;

	// private
	float b;
	float t;
	float offset;
	
	float lon;
	float dk;

	float delta;
	
	TDateTime midday;
	float middayHrs;

	TDateTime sunrise;
	float sunRiseHrs;

	TDateTime sunset;
	float sunSetHrs;

	TDateTime timetest;

	float h = -0.83333333333;

	void Init()
	{
	}

	void Main()
	{
		b = (IntegerToFloat(Latitude, 0) / 100000.0) * 0.0174532925199433;
		t = IntegerToFloat(DayOfYear, 0);
		lon = IntegerToFloat(Longtitude, 0) / 100000.0;

		offset = -0.1752 * sinf(0.033430 * t + 0.5474) - 0.134 * sinf(0.018234 * t - 0.1939);
		middayHrs = 12.0 - offset - lon * 0.0666666666666;
		midday.SetTime(FloatToIntegerRound(middayHrs * HOUR_T + DAY_T)); //shouldn't be 0
				
		dk = 0.40954 * sinf(0.0172 * (t - 79.35)); //sun declination at midday

		delta = Arccos((sinf(Rad(h)) - sinf(b) * sinf(dk)) / (cosf(b) * cosf(dk))) * 3.819718632; // in hours
				
		sunrise.SetTime(FloatToIntegerRound(middayHrs * HOUR_T + DAY_T));		//shouldn't be 0
		sunset.SetTime(FloatToIntegerRound(middayHrs * HOUR_T + DAY_T));		//shouldn't be 0
		sunrise.AddSec(FloatToIntegerRound(-1.0 * delta * HOUR_T));
		sunset.AddSec(FloatToIntegerRound(delta * HOUR_T));

		sunrise.AddSec(FloatToIntegerRound(Timezone * HOUR_T));
		sunset.AddSec(FloatToIntegerRound(Timezone * HOUR_T));
		midday.AddSec(FloatToIntegerRound(Timezone * HOUR_T));

		sunrise.ExplodeTime();
		sunset.ExplodeTime();
		midday.ExplodeTime();

		SunRiseHours = sunrise.Hours;
		SunRiseMins = sunrise.Minutes;
		SunSetHours = sunset.Hours;
		SunSetMins = sunset.Minutes;
		MiddayHours = midday.Hours;
		MiddayMins = midday.Minutes;

		sunrise.SetTime(0);
		sunrise.Implode();

		sunset.SetTime(0);
		sunset.Implode();

		midday.SetTime(0);
		midday.Implode();

		dtSunrise = sunrise.GetTime;		// да хрен его знает в каком виде они DATETIME сделают - пусть так пока будет
		dtSunset = sunset.GetTime;			

		//Test = FloatToIntegerTrunc( timetest. );
	}
};

struct Timecheck
{
    // public
    DINT todStart;
    DINT todStop;
    DINT todTd;
    BOOL xBetween;

    // private

    void Init()
    {
    }

    void Main()
    {
		if (todStop < todStart)
		{
			xBetween = ( todStart <= todTd ) || ( todTd < todStop );
		} 
		else
		{
			xBetween = ( todStart <= todTd ) && (todTd < todStop );
		}
    }
};