Dokumentasjon for Converter.

Programmet konverterer rådata fra IR-kameraet til et gråskala-bilde.

Prøv å dra testfile.txt over Converter.exe for en prøvekjøring.


Datafilen må se slik ut:
Først en linje med ett tall, x, som er bredden på arrayet. (Antall kolonner.)
Så enda en linje med ett tall, y, høyden på arrayet. (Antall rader.)

Så følger y linjer arrangert slik:
Et tall på fire (4) siffer, evnt m antall mellomrom og 4-m siffer.
Så ett mellomrom før et nytt tall, helt til bredden av arrayet er nådd.

Vedlagt følger også testfile.txt og testfile.txt.bmp, som er bildefilen programmet lager, for sammenligning. 

Et eksempel kan se slik ut:
5
5
 555  555 1024 1024 0   
1024  555  555  555 1024
 555   25 1024 1024 0   
1024  555  555  555 1024
 555  555 1024 1024 0   