#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
byte patchNum=0;
byte bankNum=0;
long t = 0;
long debounce_delay = 600; 
// configurazione BANK per scorrimento SONG su NordStage3
const int MAX_BANKNUM = 16;
const int MIN_BANKNUM = 0;
const int MAX_PATCHNUM = 120;
const int MIN_PATCHNUM = 0;
const int channel = 2;
const int channelCPRO = 5;
const  int CC_CSCENE = 86;



void setup() {
  
  // SETUP PIN and VARIABLES 
  
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   pinMode(6, INPUT_PULLUP);
   pinMode(13, OUTPUT);
   MIDI.begin(MIDI_CHANNEL_OMNI);
   MIDI.sendControlChange(0,1,channel);
   MIDI.sendControlChange(32,bankNum,channel);
   MIDI.sendProgramChange(patchNum,channel);
  
}

void loop() {
             
            // TURN OFF LED on PIN 13
             digitalWrite(13,LOW);
               
             // SONG UP 
            if(digitalRead(3)== LOW && bankNum <=16){
              if ((millis() -t ) > debounce_delay){
                if(patchNum == 120) {
                                     patchNum=0;
                                     if ( bankNum == MAX_BANKNUM ) {
                                         bankNum = 0;
                                     } else bankNum++;
                                              
                                     
                   MIDI.sendControlChange(0,1,channel);
                   MIDI.sendControlChange(32,bankNum,channel);
                   MIDI.sendProgramChange(patchNum,channel);
                   digitalWrite(13,HIGH);
                   
                  }
                 patchNum=patchNum+5;    
                 MIDI.sendControlChange(0,1,channel);
                 MIDI.sendControlChange(32,bankNum,channel);
                 MIDI.sendProgramChange(patchNum,channel);
                 digitalWrite(13,HIGH);
                 t = millis();                    
              }
             }

             // SONG DOWN 
            if(digitalRead(2)== LOW && bankNum >=MIN_BANKNUM){
               if ((millis() -t ) > debounce_delay){
                if(patchNum == 0 ) {
                                     patchNum = MAX_PATCHNUM;
                                     if ( bankNum == 0 ) {
                                                          bankNum = MAX_BANKNUM;
                                                          
                                     } else bankNum--;
                 MIDI.sendControlChange(0,1,channel);
                 MIDI.sendControlChange(32,bankNum,channel);
                 MIDI.sendProgramChange(patchNum,channel);
                 digitalWrite(13,HIGH);
                 
                    
            }
       
          patchNum=patchNum-5;
          MIDI.sendControlChange(0,1,channel);
          MIDI.sendControlChange(32,bankNum,channel);
          MIDI.sendProgramChange(patchNum,channel);
          digitalWrite(13,HIGH);
          t = millis();                    
             }
  }

  // CAMELOT CHANGE SCENE
  if(digitalRead(4)== LOW){   
      if ((millis() -t ) > debounce_delay){
           MIDI.sendControlChange(CC_CSCENE,1,channelCPRO);
           digitalWrite(13,HIGH);
           t = millis();      
      }
  }

   // INCREASE BANK NUM on NS3
  if(digitalRead(5)== LOW && bankNum <=MAX_BANKNUM){
       if (bankNum == MAX_BANKNUM){
                                   bankNum == MAX_BANKNUM; 
       } else bankNum++;
                                   digitalWrite(13,HIGH);
                                   delay(200);      
   
  }
  // DECREASE BANKNUM on NS3
  if(digitalRead(6)== LOW && bankNum >= MIN_BANKNUM){

       if (bankNum == MIN_BANKNUM){
                                   bankNum == MIN_BANKNUM; 
       } else bankNum--;
    digitalWrite(13,HIGH);
    delay(200);      

    
  }  
 


}
