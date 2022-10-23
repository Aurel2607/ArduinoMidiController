#include <USBComposite.h>

const uint8_t notesTab[] = {60, 62, 64, 65, 67, 69, 71, 72, 61, 63, 66, 68, 70};
const int notesQty = sizeof(notesTab)/sizeof(*notesTab);

#define MIDI_CHANNEL 10

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
  for (int i=0;i<notesQty;i++)
  {
    midi.sendNoteOn(MIDI_CHANNEL, notesTab[i], 127);
    
    digitalWrite(PC13, HIGH);
    
    delay(200);
    
    midi.sendNoteOff(MIDI_CHANNEL, notesTab[i], 127);

    digitalWrite(PC13, LOW);
    
    delay(200);

  }

}
