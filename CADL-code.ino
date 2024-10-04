//Import some class libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <../.pio/libdeps/uno/Servo/src/Servo.h>
//Bluetooth soft serial port Settings
SoftwareSerial BTSerial(12, 13);
//Create a steering object
Servo myServo;

//Instruction call for car motion control
#define STOP              0
#define FORWARD           1
#define BACKWARD          2
#define TURN_LEFT         3
#define TURN_RIGHT        4

//Definition of pins for controlling steering gear
#define servoPin          9

//Definition of ultrasonic pins
#define TrigPin           A1
#define EchPin            A0

//Infrared pin definition
#define leftRay           A5
#define rightRay          A4
#define middleLeftRay     A2
#define middleRightRay    A3

//Initialize the master control command
char instruct = (char) NULL;

//Initialize the speed of the car
byte speed = 0;

//Store an array of car speeds, left front wheel, right front wheel, left rear wheel, right rear wheel
byte speedArray[4] = {0, 0, 0, 0};

//The numeric pin connected to L298N
byte carDigitalPin[4] = {2, 4, 7, 8};

//PWM pin of L298N
byte carPWMPin[4] = {3, 5, 6, 11};

//Initializes the accepted distance of the ultrasonic wave
float distance_cm = 0.0;

//The distance array on the left and right sides of the ultrasonic wave
float dis[2];

//Initialize the reset flag
bool init_flag = false;

//Initialize the initial value of left, middle and right infrared
byte left_r = 1;
byte right_r = 1;
byte middle_l = 1;
byte middle_r = 1;

//Sets pin output mode and baud rate definition
void setup() {
    BTSerial.begin(9600);
//   Serial port baud rate of PID tracking module
    Serial.begin(115200);

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);

    pinMode(leftRay, INPUT);
    pinMode(rightRay, INPUT);
    pinMode(middleLeftRay, INPUT);
    pinMode(middleRightRay, INPUT);


    myServo.attach(servoPin);
    pinMode(TrigPin, OUTPUT);
    pinMode(EchPin, INPUT);
}
void motorRun(byte move) {
    switch (move) {
        case FORWARD:
            for (int i = 0; i < 4; i++) {
                analogWrite(carPWMPin[i], speedArray[i]);
                digitalWrite(carDigitalPin[i], LOW);
            }
            break;
        case BACKWARD:
            for (int i = 0; i < 4; i++) {
                analogWrite(carPWMPin[i], 0);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            break;
        case TURN_LEFT:
            for (int i = 0; i < 4; i += 2) {
                analogWrite(carPWMPin[i], 0);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            for (int i = 1; i < 4; i += 2) {
                analogWrite(carPWMPin[i], 255);
                digitalWrite(carDigitalPin[i], LOW);
            }
            delay(350);
            for (int i = 0; i < 4; i++) {
                analogWrite(carPWMPin[i], 255);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            break;

        case TURN_RIGHT:
            for (int i = 0; i < 4; i += 2) {
                analogWrite(carPWMPin[i], 255);
                digitalWrite(carDigitalPin[i], LOW);
            }
            for (int i = 1; i < 4; i += 2) {
                analogWrite(carPWMPin[i], 0);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            delay(350);
            for (int i = 0; i < 4; i++) {
                analogWrite(carPWMPin[i], 255);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            break;
        case STOP:
            for (int i = 0; i < 4; i++) {
                analogWrite(carPWMPin[i], 255);
                digitalWrite(carDigitalPin[i], HIGH);
            }
            break;
        default:
            BTSerial.println("wrong");
    }
}

void initialize() {
    if (BTSerial.available()) {
        char flag = (char) BTSerial.read();
        if (flag == 'S') {
            motorRun(STOP);
            while (BTSerial.read() >= 0) {}
            init_flag = true;
        }
    }
}

//Enable ultrasound to return a range data
float getDistance() {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    distance_cm = pulseIn(EchPin, HIGH) / 58.0;
    delay(50);
    if (distance_cm >= 50) {
        //Returns data if the distance is less than 50 cm
        return 50;
    } else {
        return distance_cm;
    }
}

//Turn right to control steering gear
void servoTurnRight() {
    for (int pos = 90; pos >= 30; pos -= 2) {
        myServo.write(pos);
        delay(10);
    }
}

//Control steering gear to turn left
void servoTurnLeft() {
    for (int pos = 90; pos < 150; pos += 2) {
        myServo.write(pos);
        delay(10);
    }
}

//Bring the steering gear back to 90 degrees
void servoTurnForward() { 
    byte pos = myServo.read();
    if (pos < 90) {
        for (byte i = pos; i <= 90; i++) {
            myServo.write(i);
            delay(10);
        }
    } else {
        for (byte i = pos; i >= 90; i--) {
            myServo.write(i);
            delay(10);
        }
    }
}

//Accept the ultrasonic return value, steering gear to determine the left and right distance who is large, and then to the larger distance of the place to turn
void diversion() {
    servoTurnLeft();
    dis[0] = getDistance();
    servoTurnRight();
    dis[1] = getDistance();
    if (dis[0] >= dis[1]) {
        motorRun(TURN_LEFT);
    } else {
        motorRun(TURN_RIGHT);
    }
}

//Compare the distance between the two sides and turn in the direction of the larger value
void observe() {
    servoTurnForward();
    if (getDistance() > 2 && getDistance() < 35) {
        motorRun(BACKWARD);
        delay(200);
        motorRun(STOP);
        servoTurnLeft();
        dis[0] = getDistance();
        servoTurnRight();
        dis[1] = getDistance();
        if (dis[0] >= dis[1]) {
            motorRun(TURN_LEFT);
        } else {
            motorRun(TURN_RIGHT);
        }
    }
}

//Obstacle avoidance is carried out according to infrared and ultrasonic signals
void avoid() {
    BTSerial.println("avoidance is on");
    do {
        motorRun(FORWARD);
        left_r = digitalRead(A5);
        right_r = digitalRead(A4);
        middle_l = digitalRead(A2);
        middle_r = digitalRead(A3);
        initialize();
        if (init_flag) {
            BTSerial.println("successful initialize");
            break;
        }
        if (right_r == 0 || left_r == 0 || middle_l == 0 || middle_r == 0) {
            motorRun(BACKWARD);
            delay(100);
            motorRun(STOP);
            diversion();
        }
        observe();
    } while (true);
}

//Sets the speed of all arrays
void setAllSpeed() {
    BTSerial.print("successfully read speed: ");
    BTSerial.println(speed);
    for (unsigned char &i: speedArray) {
        i = speed;
    }
}

//The state of sending the speed of the car
void printSpeedState() {
    BTSerial.print("a_pwm: ");
    BTSerial.println(speedArray[0]);
    BTSerial.print("b_pwm: ");
    BTSerial.println(speedArray[1]);
    BTSerial.print("c_pwm: ");
    BTSerial.println(speedArray[2]);
    BTSerial.print("d_pwm: ");
    BTSerial.println(speedArray[3]);
}

//Control the turn of tracking
void turnLeft(){
    for (int i = 0; i < 4; i += 2) {
        analogWrite(carPWMPin[i], 0);
        digitalWrite(carDigitalPin[i], HIGH);
    }
    for (int i = 1; i < 4; i += 2) {
        analogWrite(carPWMPin[i], 255);
        digitalWrite(carDigitalPin[i], LOW);
    }
    delay(70);
    for (int i = 0; i < 4; i++) {
        analogWrite(carPWMPin[i], 255);
        digitalWrite(carDigitalPin[i], HIGH);
     }
}

void turnRight(){
    for (int i = 0; i < 4; i += 2) {
        analogWrite(carPWMPin[i], 255);
        digitalWrite(carDigitalPin[i], LOW);
    }
    for (int i = 1; i < 4; i += 2) {
        analogWrite(carPWMPin[i], 0);
        digitalWrite(carDigitalPin[i], HIGH);
    }
    delay(70);
    for (int i = 0; i < 4; i++) {
        analogWrite(carPWMPin[i], 255);
        digitalWrite(carDigitalPin[i], HIGH);
     }
}

void track() {
    int track;
    Serial.println(" successfully into track model");
    do {
        initialize();
        if (init_flag) {
            BTSerial.println("successful initialize");
            break;
        }
        Serial.begin(115200);
        if (Serial.available()) {
            track = (int)Serial.parseInt();
            delay(2);
            Serial.end();
//            clear buffer
            while(Serial.read()>=0){}
//            Set preset values to prevent frequent steering of the car
            if ((track != 30000) && !(-400 < track && track < 400)) {
                if (track > 400) {
                    turnLeft();
                } else {
                    turnRight();
                }
            }
            if (track == 30000) {
                motorRun(STOP);
            }
            if ((track != 30000) && (-400 < track && track < 400)) {
                motorRun(FORWARD);
            }
        }
        delay(5);
    } while (true);
}


void readSpeed() {
    speed = BTSerial.parseInt();
    BTSerial.read();
}

void loop() {
    byte cmd;
    if (BTSerial.available()) {
        instruct = (char) BTSerial.read();
        switch (instruct) {
            case 'a':
                readSpeed();
                speedArray[0] = speed;
                printSpeedState();
                break;
            case 'b':
                readSpeed();
                speedArray[1] = speed;
                printSpeedState();
                break;
            case 'c':
                readSpeed();
                speedArray[2] = speed;
                printSpeedState();
                break;
            case 'd':
                readSpeed();
                speedArray[3] = speed;
                printSpeedState();
                break;
            case 'A':
                readSpeed();
                setAllSpeed();
                printSpeedState();
                break;
            case 'B':
                avoid();
                break;
            case 'C':
                cmd = BTSerial.parseInt();
                BTSerial.read();
                BTSerial.println("successfully read a moving instruction");
                motorRun(cmd);
                break;
            case 'T':
                track();
                break;
            default:
                BTSerial.println("NO command");} } }
