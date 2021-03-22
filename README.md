# CAN-BUS Weichendecoder

Der Weichendecoder liefert regelmäßig seinen aktuellen Zustand

## Protocol

### IDs

* 0x200 Kommuikatien Zentrale -> Decoder
* 0x400 Kommuication Decoder -> Zentrale (z.B. für die Übertragung des ajtuellen Zustandes)


### Byte 1 Kommando

* 0x01: Sendet Befehl zu Stellen eines Aktor
* 0x02: Liefert den aktellen Status eines Aktor
* 0x03: Liefert die aktuelle Koniguration

### Byte 2 Adresse 0 (MSB)

Adresse der Bus-Teilnehmers (MSB)

* 0x00  Es ist die Modul-Adresse
* \>0x00 Adresse des Aktor (MSB)
### Byte 3 Adresse 1 (LSB)

Adresse der Bus-Teilnehmers (LSB) 

* MSB  0x00: Nummer des Moduls (kein Aktor)
* MSB >0x00: Adresse des Aktors (LSB)
### Byte 4 Art des Aktor oder anderes

* 0x01 W
* 0x02 HP
* ...
* 0x80 Version (nur get)


### Byte 5 Zustand des Aktor 
#### Weichen W (0x01)

* 0x00 Ungekannt
* 0x01 wird auf Abzweig gestellt
* 0x02 wird auf Gerade gestellt
* 0x03 Abzweig
* 0x04 Gerade

Weitere Positionen für EKW/DKW, Dreiweiche noch nicht definiert
#### Signale HP (0x02)

* 0x00 unbekannt
* 0x01 HP0
* 0x02 HP1
* 0x03 HP2
* 0x04 HP0+Sh1

#### Version (0x80)

* xx Major-Version
### Byte 6 Data 1 

* xx Minor-Version
### Byte 7 Data 2

noch nicht benutzt
### Byte 8 Data 3 

noch nicht benutzt

## Beispiele

```
+--+--+--+--+--+--+--+--+
|01|nn|nn|AA|PO|  |  |  | set Position
+--+--+--+--+--+--+--+--+
|02|nn|nn|01|PO|  |  |  | liefert Status Weiche
+--+--+--+--+--+--+--+--+
|02|nn|nn|02|PO|  |  |  | liefert Status Signal HP
+--+--+--+--+--+--+--+--+
|02|00|NN|80|xx|xx|  |  | leifert Version des Decoders (nn)
+--+--+--+--+--+--+--+--+
```

