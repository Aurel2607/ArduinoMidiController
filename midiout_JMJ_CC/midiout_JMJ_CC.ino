#include <USBComposite.h>
#include <Ultrasonic.h>

#define sens1_trig PB9
#define sens1_echo PB8
#define sens2_trig PB7
#define sens2_echo PB6

const uint8_t notesTab[] = {60, 62, 64, 65, 67, 69, 71, 72, 61, 63, 66, 68, 70};
const int notesQty = sizeof(notesTab)/sizeof(*notesTab);
bool ledState = false;

#define MIDI_CHANNEL 6

#define MINMAX_ALLOWED 20

Ultrasonic ultrasonic_1(sens1_trig, sens1_echo);  // An ultrasonic sensor HC-04
Ultrasonic ultrasonic_2(sens2_trig, sens2_echo);  // An ultrasonic sensor HC-04
USBMIDI midi;

    unsigned int sens2_val_old = 0;
    unsigned int sens1_val_old = 0;
    unsigned int raw1_old = 0;

    uint16_t sens2_val_moy = 0;
    uint16_t sens1_val_moy = 0;



void setup()
{
    pinMode(PC13, OUTPUT);

    USBComposite.setProductId(0x0031);
    midi.begin();
    while (!USBComposite);

    sens1_val_moy = getData(ultrasonic_1.read());
    sens2_val_moy = getData(ultrasonic_2.read());
}

void loop()
{
    uint8_t sens1_val = getData(ultrasonic_1.read());
      sens1_val_moy = ((uint16_t)sens1_val  + (uint16_t)sens1_val_moy <<2)>>3;
      if(sens1_val_moy != sens1_val_old){
        midi.sendControlChange(MIDI_CHANNEL, 16, sens1_val_moy);
        sens1_val_old = sens1_val_moy;
      }

    uint8_t sens2_val = getData(ultrasonic_2.read());
      sens2_val_moy = ((uint16_t)sens2_val  + (uint16_t)sens2_val_moy <<2)>>3;
      if(sens2_val_moy != sens2_val_old){
        midi.sendControlChange(MIDI_CHANNEL, 17, sens2_val_moy);
        sens2_val_old = sens2_val_moy;
      }


  /*  
    uint8_t sens1_val = getData(ultrasonic_1.read());
      sens1_val_moy = ((uint16_t)sens1_val  + (uint16_t)sens1_val_moy <<2)>>3;
      if(sens1_val_moy != sens1_val_old){
        if(abs(sens1_val_moy - sens1_val_old) > MINMAX_ALLOWED){
          midi.sendControlChange(MIDI_CHANNEL, 16, sens1_val_moy);
        }
        sens1_val_old = sens1_val_moy;
      }
*/
/*    uint8_t sens2_val = getData(ultrasonic_2.read());
    if(abs(sens2_val - sens2_val_old) < MINMAX_ALLOWED){
      sens2_val_moy = (sens2_val + sens2_val_moy)>>1;
      if(sens2_val_old != sens2_val_moy){
        midi.sendControlChange(MIDI_CHANNEL, 17, sens2_val_moy);
        sens2_val_old = sens2_val_moy;
      }
    }
*/    
    ledState = !ledState;
    digitalWrite(PC13, ledState);
    
    delay(50);
 
 }

 uint8_t getData(uint8_t raw)
 {
    return raw  << 2;
  
 }
