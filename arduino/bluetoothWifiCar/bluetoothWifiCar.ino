

#define PIN6 6 //右电机转速
#define PIN7 7 //右电机转向
#define PIN8 8 //左电机转速
#define PIN9 9 //左电机转向

#define MOTOR_GO_FORWARD  { digitalWrite(PIN6,HIGH); digitalWrite(PIN7,LOW); digitalWrite(PIN8,HIGH); digitalWrite(PIN9,LOW); } //车体前进                              
#define MOTOR_GO_BACK     { digitalWrite(PIN6,LOW); digitalWrite(PIN7,HIGH); digitalWrite(PIN8,LOW); digitalWrite(PIN9,HIGH); }   //车体后退
#define MOTOR_GO_LEFT     { digitalWrite(PIN6,LOW); digitalWrite(PIN7,HIGH); digitalWrite(PIN8,HIGH); digitalWrite(PIN9,LOW); }  //车体左转
#define MOTOR_GO_RIGHT    { digitalWrite(PIN6,HIGH); digitalWrite(PIN7,LOW); digitalWrite(PIN8,LOW); digitalWrite(PIN9,HIGH); }  //车体右转
#define MOTOR_GO_STOP     { digitalWrite(PIN6,LOW); digitalWrite(PIN7,LOW); digitalWrite(PIN8,LOW); digitalWrite(PIN9,LOW); }       //车体静止

#define MAX_PACKETSIZE 100  //串口接收缓冲区
char buffUART[MAX_PACKETSIZE];
int buffUARTLen = 0;
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

void setup() {
    pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  buffUARTLen = 0;
}
 

void loop() {
  if(Serial.available()>0){
    char ch = Serial.read();
    buffUART[buffUARTLen]=ch;
    buffUARTLen++;
  //  Serial.print(ch);
    if( buffUARTLen >= MAX_PACKETSIZE-1 ){
        buffUART[buffUARTLen]='\n';
        buffUARTLen++;
    }
    if(ch=='\n' ||  buffUARTLen == MAX_PACKETSIZE){
        Serial.print(buffUART);
        

        char dest[4]={0,0,0,0};
        
        strncpy(dest, buffUART, 3);
     
        if(strcmp(dest, "222") == 0){
            Serial.println("go");
            MOTOR_GO_FORWARD;
            delay(333);
        }else if(strcmp(dest, "444") == 0){
            Serial.println("left");
            MOTOR_GO_LEFT;
            delay(333);
        }else if(strcmp(dest, "666") == 0){
            Serial.println("right");
            MOTOR_GO_RIGHT
            delay(333);
        }else if(strcmp(dest, "888") == 0){
            Serial.println("back");
            MOTOR_GO_BACK;
            delay(333);
        } else{
            MOTOR_GO_STOP;
        }
      



        buffUARTLen=0;
        memset(buffUART,0,sizeof(buffUART));
        
    }
    
  }


}
