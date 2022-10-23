#include <USBComposite.h>
#include <Ultrasonic.h>

#define sens1_trig PB9
#define sens1_echo PB8
#define sens2_trig PB7
#define sens2_echo PB6

const uint8_t notesTab[] = {60, 62, 64, 65, 67, 69, 71, 72, 61, 63, 66, 68, 70};
const int notesQty = sizeof(notesTab)/sizeof(*notesTab);

#define MIDI_CHANNEL 10

Ultrasonic ultrasonic_1(sens1_trig, sens1_echo);  // An ultrasonic sensor HC-04
Ultrasonic ultrasonic_2(sens2_trig, sens2_echo);  // An ultrasonic sensor HC-04
USBMIDI midi;

void setup()
{
    pinMode(PC13, OUTPUT);

    USBComposite.setProductId(0x0031);
    midi.begin();
    while (!USBComposite);
}

void loop()
{
    unsigned int sens2_val = ultrasonic_2.read();
    unsigned int dist = ultrasonic_1.read();
    uint8_t note = 60+ dist;
    uint8_t midi_time = 40 + (sens2_val << 1);

    midi.sendNoteOn(MIDI_CHANNEL, note, 127);
    
    digitalWrite(PC13, HIGH);
    
    delay(midi_time);
    
    midi.sendNoteOff(MIDI_CHANNEL, note, 127);
    
    digitalWrite(PC13, LOW);
    
    delay(midi_time);

 
  /*
  for (int i=0;i<notesQty;i++)
  {
    midi.sendNoteOn(MIDI_CHANNEL, notesTab[i], 127);
    
    digitalWrite(PC13, HIGH);
    
    delay(200);
    
    midi.sendNoteOff(MIDI_CHANNEL, notesTab[i], 127);

    digitalWrite(PC13, LOW);
    
    delay(200);

  }
*/
}
