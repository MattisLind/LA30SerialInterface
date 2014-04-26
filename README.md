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


![Arduino Mini Pro connections](https://dl.dropboxusercontent.com/u/96935524/Datormusuem/Parallell%20converter.png)
