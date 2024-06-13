float calculated_dist;
float avg_dist;
bool in_range_data;
int trig = 12;
int echo = 13;


void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  calculated_dist = get_sensor_data();
  Serial.println(calculated_dist);
  in_range_data = in_range(200);
  Serial.println(in_range_data);
  avg_dist = get_average_data();
  Serial.println(avg_dist);
  delay(2000);
}

float base_get_data(){
  long time_d;
  float distance;
  // send the trig command
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  time_d = pulseIn(echo, HIGH);
  distance = (time_d * 0.034) /2;
  
  return distance; 
}

float get_sensor_data(char unit){
  float data;
  if (unit == 'c'){
      data =  base_get_data();
  }
  else if(unit == 'i'){
      data = base_get_data() * 0.393701;
  }

  return data;
}

float get_sensor_data(){
  float data;
  data =  base_get_data();
  
  return data;
}

bool in_range(int range){
  float data;
  data = base_get_data();
  if(data <= range){
    return true;
  }else{
    return false;
  }

}

float get_average_data(){
  float sum_dist = 0;
  int data_counter = 0;
  float data;

  unsigned long current_time = millis();
  while(millis() - current_time <100){
    sum_dist = sum_dist + base_get_data();
    data_counter ++ ;
  }
  
  data = sum_dist / data_counter;
  return data; 
}



