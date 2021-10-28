# CAN-BUS Weichendecoder

## Serielle Console
Auf der seriellen Console kann man die Konfiguration einsehen und und die Modul-Id ändern.

Die Serielle Schnittstelle muss dazu auf 115200 gesetzt werden

## Konfigiratuion ansehen

Mit der Taste "p" wird die aktuelle Konfiguartion angezeigt. Beispiel:

```
==== CAN-Konfiguration ====
Version:       1
Status ID:     2
CAN ID: [0] => 811
CAN ID: [1] => 812
CAN ID: [2] => 813
CAN ID: [3] => 814
CAN ID: [4] => 815
CAN ID: [5] => 816
CAN ID: [6] => 817
CAN ID: [7] => 818
CAN ID: [8] => 819
CAN ID: [9] => 820
===========================
```

## Modul-Adresse ändern:

Mit der Eingabe &lt;i> + Nr + &lt;Return> kann die Modul-Adresse geändert werden.

```
Neue ID: 2
Setze neue Id: 2
```


Der Weichendecoder liefert regelmäßig seinen aktuellen Zustand

## Protocol

### IDs


* 100 Frames mit der Id 100 dient dem Verändern des Zustandes
* 200 Sendet den aktuellen Zustand des Decoders, wenn die im ersten Datafeld (u_int16) angegebene Moduladresse mit der des Moduls übereinstimmt. Der Status selbst wird mit der Id 300 gesendet

