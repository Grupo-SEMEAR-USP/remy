#define ha_pin 18
#define hb_pin 19
#define hc_pin 21

volatile bool mudou_ha = false;
volatile bool mudou_hb = false;
volatile bool mudou_hc = false;

void IRAM_ATTR mudar_ha() {
  mudou_ha = true; }

void IRAM_ATTR mudar_hb() {
  mudou_hb = true; }

void IRAM_ATTR mudar_hc() {
  mudou_hc = true; }

void setup() {
  
  Serial.begin(9600);

  pinMode(ha_pin, INPUT);
  pinMode(hb_pin, INPUT);
  pinMode(hc_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(ha_pin), mudar_ha, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hb_pin), mudar_hb, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hc_pin), mudar_hc, CHANGE);

}

void loop() {

  int ha, hb, hc;
  int contador = 0;

  if (mudou_ha) {
    mudou_ha = false;
    contador++;
    ha = digitalRead(ha_pin);
    Serial.print(ha );
    Serial.print(hb );
    Serial.println(hc);
    Serial.print("Numero de mudancas: ");
    Serial.println(contador);
  }

  if (mudou_hb) {
    mudou_hb = false;
    contador++;
    hb = digitalRead(hb_pin);
    Serial.print(ha );
    Serial.print(hb );
    Serial.println(hc);
    Serial.print("Numero de mudancas: ");
    Serial.println(contador);
  }

  if (mudou_hc) {
    mudou_hc = false;
    contador++;
    hc = digitalRead(hc_pin);
    Serial.print(ha );
    Serial.print(hb );
    Serial.println(hc);
    Serial.print("Numero de mudancas: ");
    Serial.println(contador);

  }
}


