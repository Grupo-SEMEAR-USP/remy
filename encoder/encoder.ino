#define ha_pin 18
#define hb_pin 19
#define hc_pin 21
#define pwm 4

volatile long etapas = 0;

volatile bool mudou_hall = false;

void IRAM_ATTR mudar_ha() {
  mudou_hall = true; }

void IRAM_ATTR mudar_hb() {
  mudou_hall = true; }

void IRAM_ATTR mudar_hc() {
  mudou_hall = true; }

void setup() {
  
  Serial.begin(9600);

  pinMode(ha_pin, INPUT);
  pinMode(hb_pin, INPUT);
  pinMode(hc_pin, INPUT);
  pinMode(pwm, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ha_pin), mudar_ha, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hb_pin), mudar_hb, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hc_pin), mudar_hc, CHANGE);

}

void loop() {

  analogWrite(pwm, 10);

  static unsigned long antes = millis();
  unsigned long agora = millis();
  static long graus = 0;

  int ha, hb, hc;

  //sempre que um dos halls muda de valor
  if (mudou_hall) {
    mudou_hall = false;
    etapas++;
    graus += 4;

    ha = digitalRead(ha_pin);
    hb = digitalRead(hb_pin);
    hc = digitalRead(hc_pin);

    Serial.print(ha );
    Serial.print(hb );
    Serial.println(hc);
    Serial.print("Graus girados: ");
    Serial.println(graus);
  }

  // Cálculo de velocidade (a cada 1 segundo)
  if (agora - antes >= 1000) {
    antes = agora;
    float rpm_eletrico = (etapas / 6.0) * 60.0; // 6 etapas por rotação elétrica
    float rpm_mecanico = rpm_eletrico / 15.0;    // 15 pares de polos

    Serial.print("Velocidade: ");
    Serial.print(rpm_mecanico);
    Serial.println(" RPM");

    etapas = 0;
  }

  
}


