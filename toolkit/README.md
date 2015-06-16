#Modification
* Merging the ISR codes block of tones and IRSendRev, because they use the same timer interrupter timer2.See IRSendRev.cpp - ISR(TIMER_INTR_NAME)
<br>
* Inside colorRGBLed watchdog will restart program when i2c communication crush into block <br>
