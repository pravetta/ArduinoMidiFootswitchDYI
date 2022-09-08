#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
byte patchNum=0;
byte bankNum=1;
// configurazione BANK per scorrimento SONG su NordStage3
const int MAX_BANKNUM = 16;
const int MIN_BANKNUM = 0;
const int MAX_PATCHNUM = 120;
const int MIN_PATCHNUM = 0;
const int channel = 2;
void setup() {
  // put your setup code here, to run once:
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   pinMode(13, OUTPUT);
   MIDI.begin(MIDI_CHANNEL_OMNI);
   MIDI.sendControlChange(0,1,channel);
   MIDI.sendControlChange(32,2,channel);
   MIDI.sendProgramChange(patchNum,channel);
   //Serial.begin(9600);  
}

void loop() {
             digitalWrite(13,LOW);
             // PATCH UP:
             if(digitalRead(3)== LOW && patchNum <=127){
                patchNum++;
                MIDI.sendProgramChange(patchNum,channel);
                digitalWrite(13,HIGH);
                delay(200);
             }
             // PATCH DOWN
             if(digitalRead(2)== LOW && patchNum >=1){
                patchNum--;
                MIDI.sendProgramChange(patchNum,channel);
                digitalWrite(13,HIGH);
                delay(200);
             }  
             // SONG UP 
            if(digitalRead(5)== LOW && bankNum <=MAX_BANKNUM){
                if(patchNum == 120) {
                                     patchNum=0;
                                     if ( bankNum == MAX_BANKNUM ) {
                                         bankNum = 0;
                                     } else bankNum++;
                   MIDI.sendControlChange(0,1,channel);
                   MIDI.sendControlChange(32,bankNum,channel);
                   MIDI.sendProgramChange(patchNum,channel);
                   digitalWrite(13,HIGH);
                   delay(200);     
                   }
                 patchNum=patchNum+5;    
                 MIDI.sendControlChange(0,1,channel);
                 MIDI.sendControlChange(32,bankNum,channel);
                 MIDI.sendProgramChange(patchNum,channel);
                 digitalWrite(13,HIGH);
                 delay(200);   
             }

             // SONG DOWN 
            if(digitalRead(4)== LOW && bankNum >=MIN_BANKNUM){
                if(patchNum == 0 ) {
                                     patchNum = MAX_PATCHNUM;
                                     if ( bankNum == 0 ) {
                                                          bankNum = MAX_BANKNUM;
                                                          digitalWrite(13,HIGH);
                                                          delay(200);        
                                     } else bankNum--;
                 MIDI.sendControlChange(0,1,channel);
                 MIDI.sendControlChange(32,bankNum,channel);
                 MIDI.sendProgramChange(patchNum,channel);
                 digitalWrite(13,HIGH);
                 delay(200);
                    
            }
       
          patchNum=patchNum-5;
          MIDI.sendControlChange(0,1,channel);
          MIDI.sendControlChange(32,bankNum,channel);
          MIDI.sendProgramChange(patchNum,channel);
          digitalWrite(13,HIGH);
          delay(200);
  
  }


}
