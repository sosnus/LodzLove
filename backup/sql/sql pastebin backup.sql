	
	


SELECT 
    Sensors.SensorID,
    Sensors.SensorName,
    Sensors.SensorDescription,
    Sensors.Gps_latitude,
    Sensors.Gps_longitude,
	Measurements.MeasurementID,
    Measurements.TypeID,
    Measurements.Value,
    Measurements.MeasurementDate as newest
FROM 
	Measurements
INNER JOIN Sensors on Sensors.SensorID = Measurements.SensorID
where 
	Measurements.MeasurementDate in (
        select maxdate 
            from(
                    SELECT max(Measurements.MeasurementDate) as maxdate, Measurements.SensorID
                    from Measurements 
                    GROUP by Measurements.SensorID
                ) aa
        )




SELECT 
    Sensors.SensorID,
    Sensors.SensorName,
    Sensors.SensorDescription,
    Sensors.Gps_latitude,
    Sensors.Gps_longitude,
	MeasurementsReal.MeasurementID,
    MeasurementsReal.TypeID,
    MeasurementsReal.Value,
    MeasurementsReal.MeasurementDate as newest
FROM 
	MeasurementsReal
INNER JOIN Sensors on Sensors.SensorID = MeasurementsReal.SensorID
where 
	MeasurementsReal.MeasurementDate in (
        select maxdate 
            from(
                    SELECT max(MeasurementsReal.MeasurementDate) as maxdate, MeasurementsReal.SensorID
                    from MeasurementsReal 
                    GROUP by MeasurementsReal.SensorID
                ) aa
        )
		
SELECT 
    Sensors.SensorID,
    Sensors.SensorName,
    Sensors.SensorDescription,
    Sensors.Gps_latitude,
    Sensors.Gps_longitude,
	MeasurementsReal.MeasurementID,
    MeasurementsReal.TypeID,
    MeasurementsReal.Value,
    MeasurementsReal.MeasurementDate as asd
FROM 
	MeasurementsReal
INNER JOIN Sensors on Sensors.SensorID = MeasurementsReal.SensorID