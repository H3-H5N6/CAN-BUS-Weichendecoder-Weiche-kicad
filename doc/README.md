# CAN-BUS-Frames

Die einzelnen Aktoren haben eine id im Wertebereich uint_16 (2byte)
## Aktor schalten

* Frame ID: 100
* data16: ID1 [, [ID2][, [ID3][, [ID4]]]]

Pro Frame können 4 Aktoren gleichzeit geschaltet werden

## Status der Aktoren

* Frame ID 300
* data16: ID des Aktor, Status des Aktors, unbenutz, ID des aktiven Aktors

### Bedeutung der Status

* OFF 0x00
* ON  0x01
* RUNNING 0x02
* BLOCKED_STATE 0x03
* UNKNOWN_STATE 0x04

Eine einfache Weiche besteht aus zwei Aktoren. Um den Status dieser Weiche zu erhalten, werden zwei Frames gesendet.

Hat der eine Aktor einen Status RUNNING, so hat der zweite Aktor einen Status von BLOCKED_STATE, da dieser aktuell nicht verändert werden kann. 



# Adapter Wannenstecker 2x3 zu Stiftleiste 1x6

## Adapter auf Lochrasterplatte, Ansicht von unten.
![](kicad/Signalsimulator/Adapter-2x3zu1x6.svg)

![](kicad/Signalsimulator/Adapter-2x3zu1x6-Beispiel-small.jpg)

## Leiterplatte, Blick von oben auf die Bestückungsseite

![](kicad/2x3zu1x6/Adapter-2x3zu1x6.png)

## Belegung der 1x6-Stiftleiste, Blick von oben auf die Leiterplatte

6  |  5 |  4 |  3 | 2  | 1 
---|----|----|----|----|---
r1 | r2 | gr |  + | ge | w  

## Belegung des 2x3-Wannensteckers 

5  | 6  | 1  
---|----|----
r2 | r1 | w  
gr | +  | ge 
4  | 3  | 2  