# smart_hostel
To reduce and optimize the usage of electricity in college hostel's a simple model based on Internet of Things was designed. The model included a NodeMCU micro-controller, Temperature sensor(DHT11), Ultrasonics sensor(HC-SR04), Bluetooth(HC-05), L-shape signle shaft 150rom motor, DPDT switch and an OLED display.
#Wokring Principle
- Ultrasonic sensor senses an obstacle or object in front of it and sends a signal to the NodeMCU.
- NodeMCU sends a signal to Bluetooth to send a request for the paired device to ask for the passcode.
- The passcode entered by the paired device or the user is cross verified and if the passcode entered is correct then the welcome message is displayed on the OLED screen.
- Then, user is allowed to use the switch to operate automatic door operation in the model.
- If the passcode entered is wrong then the alert is sent to the buzzer to initiate burglar alarm.
- Temperature sensor shows the temperature of the building or houses and can be used to regulate air conditioning.
