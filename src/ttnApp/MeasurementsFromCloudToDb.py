import time
import ttn
import json
import mysql.connector
from datetime import datetime

app_id = "lodz-lovehackathon-bluebrick"
access_key = "ttn-account-v2.BrTu-PcNO2acNVnNvwoCvyk1srv4pJZ1vokhp3-0g6Y"
insert_sql = "insert into MeasurementsReal (MeasurementID, MeasurementDate, SensorID, TypeID, Value) values (%s, %s, %s, %s, %s);"

def uplink_callback(msg, client):
  print()
  print("Received measurement from ", msg.dev_id)
  #print( msg.payload_fields.a0microphone )
  #print( msg.payload_fields.a2temperature )
  #print( msg.payload_fields.a3proximity )
  x = msg.metadata.gateways[0].time
  x = msg.metadata.gateways[0].time.replace("T", " ")
  x = x.replace("Z", " ")
  x = x.replace("Z", " ")
  y = x.split(".");
  x=y[0]
  values_temp = (None, x, msg.payload_fields.id, 0, msg.payload_fields.a2temperature) # temp
  values_noice = (None, x, msg.payload_fields.id, 3, msg.payload_fields.a0microphone) # halas
  values_lx = (None, x, msg.payload_fields.id, 2, msg.payload_fields.a3proximity) # temp
  values=(values_temp,values_noice,values_lx)
  #print(values_temp)
  #print(values_noice)
  #print(values_lx)
  
  mycursor.execute(insert_sql,values_temp)
  mydb.commit()
  print(mycursor.rowcount, "record inserted.")
  mycursor.execute(insert_sql,values_noice)
  mydb.commit()
  print(mycursor.rowcount, "record inserted.")
  mycursor.execute(insert_sql,values_lx)
  mydb.commit()
  print(mycursor.rowcount, "record inserted.")
  



handler = ttn.HandlerClient(app_id, access_key)
mydb = mysql.connector.connect(host="db4free.net",user="loveadmin",passwd="adminlove",database="lodzlove")
print(mydb)
print("Working")
mycursor = mydb.cursor()

# mycursor.execute("SELECT * FROM Users")
# myresult = mycursor.fetchall()
# for x in myresult:
  # print(x)


# using mqtt client
mqtt_client = handler.data()
mqtt_client.connect()
mqtt_client.set_uplink_callback(uplink_callback)
app_client =  handler.application()

#mqtt_client.close()