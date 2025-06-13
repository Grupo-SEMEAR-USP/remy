//motor 1:
#define ha1_pin 18
#define hb1_pin 19
#define hc1_pin 21
#define pwm1 4

//motor 2:
#define ha2_pin 25
#define hb2_pin 26
#define hc2_pin 27
#define pwm2 12

volatile long etapas_1 = 0;
volatile long etapas_2 = 0;

volatile bool mudou_hall_1 = false;
volatile bool mudou_hall_2 = false;

void IRAM_ATTR mudar_ha1() {
  mudou_hall_1 = true; }

void IRAM_ATTR mudar_hb1() {
  mudou_hall_1 = true; }

void IRAM_ATTR mudar_hc1() {
  mudou_hall_1 = true; }

void IRAM_ATTR mudar_ha2() {
  mudou_hall_2 = true; }

void IRAM_ATTR mudar_hb2() {
  mudou_hall_2 = true; }

void IRAM_ATTR mudar_hc2() {
  mudou_hall_2 = true; }

void setup() {
  
  Serial.begin(9600); //Nao esquecer de colocar o monitor serial em 9600

  pinMode(ha1_pin, INPUT);
  pinMode(hb1_pin, INPUT);
  pinMode(hc1_pin, INPUT);
  pinMode(pwm1, OUTPUT);

  pinMode(ha2_pin, INPUT);
  pinMode(hb2_pin, INPUT);
  pinMode(hc2_pin, INPUT);
  pinMode(pwm2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ha1_pin), mudar_ha1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hb1_pin), mudar_hb1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hc1_pin), mudar_hc1, CHANGE);

  attachInterrupt(digitalPinToInterrupt(ha2_pin), mudar_ha2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hb2_pin), mudar_hb2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hc2_pin), mudar_hc2, CHANGE);

}

void loop() {

  analogWrite(pwm1, 20); //Controlar velocidade do motor 1      <--------------------- AQUI MUDAS AS VELOCIDADESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  analogWrite(pwm2, 40); //Controlar velocidade do motor 2      (Pelo amor de deus nao passem de 80)

  unsigned long agora = millis();

  static unsigned long antes_1 = millis();
  static long graus_1 = 0;

  static unsigned long antes_2 = millis();
  static long graus_2 = 0;

  int ha1, hb1, hc1, ha2, hb2, hc2;

  // Proteção contra condição de corrida para o motor 1
  bool mudou_1;
  noInterrupts();
  mudou_1 = mudou_hall_1;
  if (mudou_hall_1) {
    mudou_hall_1 = false;
  }
  interrupts();

  if (mudou_1) {
    noInterrupts();
    etapas_1++;
    interrupts();
    graus_1 += 4;
  }

  // Proteção contra condição de corrida para o motor 2
  bool mudou_2;
  noInterrupts();
  mudou_2 = mudou_hall_2;
  if (mudou_hall_2) {
    mudou_hall_2 = false;
  }
  interrupts();

  if (mudou_2) {
    noInterrupts();
    etapas_2++;
    interrupts();
    graus_2 += 4;
  }

  // Cálculo de velocidade do motor 1 (a cada 1 segundo)
  if (agora - antes_1 >= 1000) {
    antes_1 = agora;
    float rpm_eletrico_1 = (etapas_1 / 6.0) * 60.0; // 6 etapas por rotação elétrica
    float rpm_mecanico_1 = rpm_eletrico_1 / 15.0;    // 15 pares de polos

    Serial.print("Velocidade Motor 1: ");
    Serial.print(rpm_mecanico_1);
    Serial.println(" RPM");

    etapas_1 = 0;
  }

  // Cálculo de velocidade do motor 2 (a cada 1 segundo)
  if (agora - antes_2 >= 1000) {
    antes_2 = agora;
    float rpm_eletrico_2 = (etapas_2 / 6.0) * 60.0; // 6 etapas por rotação elétrica
    float rpm_mecanico_2 = rpm_eletrico_2 / 15.0;    // 15 pares de polos

    Serial.print("Velocidade Motor 2: ");
    Serial.print(rpm_mecanico_2);
    Serial.println(" RPM");

    etapas_2 = 0;
  }

  
}