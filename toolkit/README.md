#Note
* Merging the ISR codes block of tones and IRSendRev, because they use the same timer interrupter timer2.See IRSendRev.cpp - ISR(TIMER_INTR_NAME)
<br>
* Inside colorRGBLed, watchdog will restart system when i2c communication crushed <br>
* 
