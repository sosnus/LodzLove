	
	


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