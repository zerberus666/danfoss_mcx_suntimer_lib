# danfoss_mcx_suntimer_lib
Suntimer library for Danfoss MCX PLC
## FB Suntimer
Hotspots:
1) Timezone : In INT 
2) Latitude : In DINT  - to calculate value, take latitude of you place and multiply by 10000. For example: Latitude of Moscow is 55.75222, value is 5575222
3) Longtitude : In DINT - the same as latitude
4) OffsetSunset : In DINT - minutes. If you want the night to come earlier, set negative value
5) OffsetSunrise : In DINT - minutes. If you want the night to end faster, set negative value, else - positive
6) xNight : BOOL - if is night
7) xDay : BOOL - if is day



