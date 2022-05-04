LA30SerialInterface
===================

LA30 serial interface

This code is an Arduino project to subsititue the serial interface cards of a DecWriter. The original serial interface
consists of two cards, M7731 and M7389 which include a UART and a 16 byte buffer.

Adapter board connections

         1         2
    --------------------
    A             +5V
    B   PDEM      
    C             GND
    D   PBIT1     KBIT2
    E   PBIT2     PSTB
    F
    H   PBIT3     KBIT3
    J   PBIT4
    K             PBIT5
    L   PBIT6   
    M   KSTB      KBIT4
    N 
    P   PBIT7     KBIT5
    R
    S   KBIT1     KBIT6
    T   BAUD1     KBIT7
    U   BAUD2     LOCAL
    V   BAUD3     PINIL

This cards sits in slot A06.
To have the LINE / LOCAL and BAUD RATE switch working on the keyboard wire 
wrap connections between slot A09 R1 and A06 T1, A09 S1 and A06 U1, A09 T2 and A06 V1 and finally A09 R2 and A06 U2. 


![Arduino Mini Pro connections](http://storage.datormuseum.se/u/96935524/Datormusuem/Parallell%20converter.png)

The RS-232 converter is a Sparkfun [MAX3232 breakout board](https://www.sparkfun.com/products/11189)

A standard AtMega328 processor can only handle 18 digital I/O signals. Thus BAUD1, BAUD2, BAUD3 and LOCAL is not supported as of yet.
