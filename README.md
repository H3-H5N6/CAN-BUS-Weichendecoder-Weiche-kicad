# CAN-BUS Weichendecoder

Der Weichendecoder liefert regelmäßig seinen aktuellen Zustand

## Protocol

### IDs

0x200 Kommuikatien Zentrale -> Decoder
0x400 Kommuication Decoder -> Zentrale (z.B. für die Übertragung des ajtuellen Zustandes)


### Byte 0 Kommando

0x01: Sendet Befehl zu Stellen eines Aktor
0x02: Liefert den aktellen Status eines Aktor


### Byte 1 Adresse 0


### Byte 2 Adresse 1


### Byte 3 Art des Aktor

0x01 W
0x02 HP

### Byte 4 Zustand des Aktor

#### Weichen W

0x00 Ungekannt
0x01 wird auf Abzweig gestellt
0x02 wird auf Gerade gestellt
0x03 Abzweig
0x04 Gerade

Weitere Positionen für EKW/DKW, Dreiweiche noch definiert


#### Signale HP

0x00 unbekannt
0x01 HP0
0x02 HP1
0x03 HP2
0x04 HP0+Sh1


### Byte 5

