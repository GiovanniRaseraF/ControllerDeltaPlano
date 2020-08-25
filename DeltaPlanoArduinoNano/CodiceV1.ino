/*
 Name:	    CodiceV1.ino
 Created:	8/24/2020 2:04:33 PM
 Author:	giovannirasera
*/

/// <summary>
/// Connessione al Reley Shield 
/// </summary>
constexpr int   aout8_rin1  = 8,
                aout9_rin2  = 9,
                aout10_rin3 = 10,
                aout11_rin4 = 11;

/// <summary>
/// Input
/// </summary>
const int pin_input_1 = 5;     
const int pin_input_2 = 6;     
int bstate_1 = 0;
int bstate_2 = 0;
int prev_bstate1 = -1;
int prev_bstate2 = -1;
bool state_changed = true;
#define ACCESO HIGH
#define SPENTO  LOW
//MODALITA
constexpr int NO_POWER = 1, POWER_RADIO_NOISE = 3, BATTERY_NO_NOISE = 2, IMPOSSIBLE = 0;

//
void setup() {
    //Output al Reley Shield
    pinMode(aout8_rin1,     OUTPUT);
    pinMode(aout9_rin2,     OUTPUT);
    pinMode(aout10_rin3,    OUTPUT);
    pinMode(aout11_rin4,    OUTPUT);

    //Input dal convertitore
    pinMode(pin_input_1, INPUT_PULLUP);
    pinMode(pin_input_2, INPUT_PULLUP);
    
    //Debug monitor
    Serial.begin(9600);
    Serial.println("-- Benvenuto Mauro --");
    Serial.println("Info: ");
}

void loop() {
    //Leggi input
    read(bstate_1, pin_input_1);
    read(bstate_2, pin_input_2);
    state_changed = (prev_bstate1 != bstate_1 || prev_bstate2 != bstate_2);

    //Faccio qualcosa solo se lo stato è cambiato
    if (state_changed) {
        prev_bstate1 = bstate_1;
        prev_bstate2 = bstate_2;

        //DEBUG
        Serial.print("bstate_1: "); Serial.print(bstate_1); Serial.print("  bstate_2: "); Serial.println(bstate_2);

        //Menu delle modalita
        int scelta = calcola_scelta();
        switch (scelta) {
        case NO_POWER:
            Serial.print(scelta); Serial.println(" NO_POWER");

            set_releys(SPENTO, SPENTO, SPENTO, SPENTO);

            break;
        case POWER_RADIO_NOISE:
            Serial.print(scelta); Serial.println(" POWER_RADIO_NOISE");

            set_releys(ACCESO, SPENTO, SPENTO, SPENTO);

            break;
        case BATTERY_NO_NOISE:
            Serial.print(scelta); Serial.println(" BATTERY_NO_NOISE");

            set_releys(ACCESO, SPENTO, ACCESO, ACCESO);

            break;
        case IMPOSSIBLE:
            Serial.print(scelta); Serial.println(" IMPOSSIBLE");
            //TODO
            break;
        }
    }

    //Evita Bounce
    delay(200);
}

//Funzioni Utils

/// <summary>
/// Salva il valore letto nella variabile storing_val
/// </summary>
/// <param name="storing_var"> Dove salvare</param>
/// <param name="pin_input_val"> Da dove leggere</param>
void read(int& storing_var, const int pin_input_val) {
    storing_var = digitalRead(pin_input_val);
}

//Calcolo della scelta
int calcola_scelta() {
    return (bstate_1 << 1) + (bstate_2 << 0) ;
}

/// <summary>
/// Modifica la posizione dei reley
/// ATTENZIONE ALLA POSIZIONE
/// 4 3 2 R1   -->   USB
/// </summary>
/// <param name="state_rout4"></param>
/// <param name="state_rout3"></param>
/// <param name="state_rout2"></param>
/// <param name="state_rout1"></param>
void set_releys(int state_rout4, int state_rout3, int state_rout2, int state_rout1) {
    //Impostazione dei reley
    digitalWrite(aout8_rin1, state_rout1);
    digitalWrite(aout9_rin2, state_rout2);
    digitalWrite(aout10_rin3, state_rout3);
    digitalWrite(aout11_rin4, state_rout4);
}

