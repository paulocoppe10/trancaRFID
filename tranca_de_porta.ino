
#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);  
Servo myservo; 
LiquidCrystal_I2C lcd(0x27,16,2);
 
char st[20];
 
void setup() 
{
  SPI.begin();      
  mfrc522.PCD_Init();  
  lcd.begin(16, 2);  
  mensageminicial();
  lcd.init();
  myservo.attach(4);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
}
 
void loop() 
{
    lcd.setBacklight(HIGH);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "FC 56 F1 32" ||conteudo.substring(1) == "69 EE 03 B9") 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("seja bem vindo");
    lcd.setCursor(0,1);
    lcd.print("Acesso liberado!");
    myservo.write(90);
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(3000);
    mensageminicial();
  }
 
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("acesso negado");
    lcd.setCursor(0,1);
    lcd.print("tente novamente");
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(8, HIGH);
    delay(3000);
    mensageminicial();
  }
}
 
void mensageminicial()
{
    myservo.write(0);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
    digitalWrite(8, LOW);
  lcd.clear();
  lcd.print(" Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
