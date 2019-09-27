CREATE TABLE `Sensors` (
  `SensorID` int,
  `SensorName` varchar(255),
  `SensorPassword` varchar(255),
  `SensorDescription` varchar(255),
  `Gps_latitude` float8,
  `Gps_longitude` float8,
  `Gps_altitude` float8
);

CREATE TABLE `Measurements` (
  `MeasurementID` int,
  `MeasurementDate` datetime,
  `SensorID` int,
  `TypeID` int,
  `Value` double
);

CREATE TABLE `Types` (
  `TypeID` int,
  `Name` varchar(255)
);

CREATE TABLE `Users` (
  `UsersID` int,
  `SensorID` int,
  `Name` varchar(255),
  `Owner` varchar(255),
  `Email` varchar(255)
);

ALTER TABLE `Measurements` ADD FOREIGN KEY (`SensorID`) REFERENCES `Sensors` (`SensorID`);

ALTER TABLE `Types` ADD FOREIGN KEY (`TypeID`) REFERENCES `Measurements` (`TypeID`);

ALTER TABLE `Sensors` ADD FOREIGN KEY (`SensorID`) REFERENCES `Users` (`SensorID`);
