# Create Your Node!

# 1. ask for credentials

Write email to administrator: sosnus15@gmail.com

Email template: 

```
- Name
- Owner (company or smt)
- Email 
- Name of Sensor
- Password which u will be using to authorize sensor
- Short description of sensor
- GPS coordinates where sensor will be placed
```

You will receive:

- ID of User
- ID of Sensor
- list of TypeId's to identify what type of data will You be sending to us(ex. temp , pm2.5)

and snippet arduino code, please copy&paste this into Your Arduino project
```
const id = 22;
static const PROGMEM u1_t NWKSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
static const u1_t PROGMEM APPSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
static const u4_t DEVADDR = 0x03FF0001 ;
```

# 2. Download and modify Arduino sample and add credentials.

1. Copy Arduino project
2. Replace variables `id, NWKSKEY, APPSKEY, DEVADDR ` in Arduino code

# 3. Upload code to your node based on Arduino and open Grafana portal

// TODO: wkleić foto node (pudełko)
# 4. look at Your data on Grafana and have fun ;)

// TODO: wkleić foto grafany