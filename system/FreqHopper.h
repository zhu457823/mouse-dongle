#ifndef	_FREQHOPPER_H
#define	_FREQHOPPER_H

#define		cMaxFreqNum	4	// 15
#define		cRFTime			1

#define		cCDDTDuty		25// about 250us 15// 25 // 3

// Note: 10ms total detect 40 times.
#define		cCDCNT			4	// 2 // 35 // 2// 1

//extern BYTE XDATA uRFTime;
extern bit bRXEndPacket;
//extern bit bFreqHopper;
extern bit bCurFreqActive;
extern bit bRFRXData;
extern BYTE uSignalQuality;


void InitFreqHopper(void);
void FreqProcess(void);
#endif
