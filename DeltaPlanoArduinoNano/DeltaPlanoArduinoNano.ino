/*
 Name:		CodecePerDeltaplano.ino
 Created:	8/15/2020 2:04:33 PM
 Author:	giovannirasera
*/
// Include the required Arduino libraries:
//Reley//

///////////

//Public//
const int NUMERO_PROGRAMMI = 3;
volatile int programmaSelezionato = 0;
const int interruptPin = 2;

//	Menu
const int BATTERIA = 0;
const int RADIO = 1;
const int LUCI = 2;
//////////

//
void setuppp() {
	//Seriali
	Serial.begin(9600);
	Serial.write("\n- Ciao Mauro - \n");

	//Init Variabili
	programmaSelezionato = 0;
}

//
void looppp() {
	//Init Loop

	//Menu programmaOpzioni
	switch (programmaSelezionato) {
	case BATTERIA:
		Serial.println("BATTERIA");
		break;

	case RADIO:
		Serial.println("RADIO");
		break;

	case LUCI:
		Serial.println("LUCI");
		break;

	default:
		Serial.println("ERRORE!!");
		break;
	}

}

//Interrupt Vector//
/*Aggionra la variabile del menu*/
////////////////////

