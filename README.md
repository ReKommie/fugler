Rask innføring i klasser/objekter

Et objekt er en samling av egenskaper (variabler) og metoder (funksjoner). Objekter ligger nært sånn vi oppfatter virkeligheten. La oss ta eksempel i en radio. Den har noen egenskaper: en størrelse, et materiale, maks volum, strømforbruk osv. Samtidig kan den også gjøre ting vi at vi interagerer med den: vi kan skru den på, endre volum, skifte kanal osv. Slik kunne vi skrevet objektet radio i javaScript:



		var radio = {

			størrelse: 45,
			pris: 599,

			volum: 50,

			maksVolum: 100,
			volumOpp: function() {

				if(volum < maksVolum){

				this.volum++;

			}

		}




Her er eksempel på hvordan koden ville fungert:

		radio.størrelse;

		>  45

		radio.volum;
		>  50

		radio.volumOpp();

		radio.volum;

		>  51

		radio.volum = 100;
		radio.volum;
		>  100


Klasser er en oppskrift på et objekt, hvor egenskapene og metodene er de samme for alle objektene laget ut av klassen, men selve verdiene kan variere. Hvis vi fortsetter på radio-eksempelet, kan radio være en klasse. Noen radioer har liten størrelse, andre har stor, men alle har en. Alle radioer kan man skru lyden opp og ned på, men de kan ha forskjellige grenser for maks- og min-volum. Slik kunne en radioklasse sett ut i javaScript:

		function Radio(størrelse,pris,maksVolum) {
			this.størrelse = størrelse;

			this.pris = pris;

			this.maksVolum = maksVolum;

			this.volum = this.maksVolum / 2;

			this.volumOpp = function() {

				if(volum < maksVolum){

				this.volum++;

			}

		}



Nå kan vi lage et objekt ut av klassen og lagre det i en variabel:

		var radio1 = new Radio(45,599,100);



Denne variabelen er nå et objekt med størrelse 45, pris 599 og maksVolum 100, volum satt til halve maksvolumet (50), og metodene volumOpp. Altså vil denne variabelen nå fungere akkurat likt som radio-variabelen vi lagde i det første eksempelet:



		radio.størrelse;

		>  45

		radio.volum;
		>  50

		radio.volumOpp();

		radio.volum;

		>  51

		radio.volum = 100;
		radio.volum;
		>  100

Foreløpig virker det kanskje helt unødvendig å lage en slik klasse som vi lager objekter ut av, det var mye mindre å skrive når vi bare lagde radio-objektet uten å gå igjennom noen klasser. Poenget ligger i at hver gang vi skal lage en radio til med litt annerledes spesifikasjoner, vil vi ha spart mye arbeid. På denne måten kan vi også med sikkerhet vite at alle objektene som kommer fra én klasse vil ha alle de samme egenskapene og metodene. Vi kan lage en radio til veldig enkelt nå:



		var radio2 = new Radio(30,1299,500);

Objektet radio2 har nå størrelse 30, pris 1299 og maksVolum 500, volum satt til halve maksvolumet (250), og metoden volumOpp.


I script.js lagrer jeg alle objekter av en klasse i arrays (det samme som lister i Python):



		var radioer = [radio1, radio2];


		radioer[0].størrelse;
		>  45
