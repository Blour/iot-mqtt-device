#include <input_device.h>
#include <Arduino.h>
#include <constants.h>

class ProximitySensor: public InputDevice {
private:
    uint8_t pin_trigger;
    uint8_t pin_echo;
public:
    ProximitySensor(uint16_t device_id, uint16_t threshold, long sample_time): InputDevice(device_id, threshold, sample_rate) {};
    bool init(uint8_t pin_trigger, uint8_t pin_echo);
    uint16_t read();
};

bool ProximitySensor::init(uint8_t pin_trigger, uint8_t pin_echo){
    this->pin_trigger = pin_trigger;
    this->pin_echo = pin_echo;
    pinMode(this->pin_trigger, OUTPUT);     //pin como salida
    pinMode(this->pin_echo, INPUT);        //pin como entrada
    digitalWrite(this->pin_trigger, LOW); //Inicializamos el pin con 0
}

uint16_t ProximitySensor::read(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(this->pin_trigger, HIGH);
  delayMicroseconds(TRIGMS);          //Enviamos un pulso de 10us
  digitalWrite(this->pin_trigger, LOW);
  t = pulseIn(this->pin_echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  return(d);
}