CREATE TABLE `Sensors` (
  `SensorId` int,
  `SensorName` varchar(255),
  `SensorPassword` varchar(255),
  `SensorDescription` varchar(255)
);

CREATE TABLE `Measurements` (
  `MeasurementId` int,
  `MeasurementDate` datetime,
  `SensorId` int,
  `TypeId` int,
  `Value` double
);

CREATE TABLE `Types` (
  `TypeId` int,
  `Name` varchar(255)
);

ALTER TABLE `Measurements` ADD FOREIGN KEY (`SensorId`) REFERENCES `Sensors` (`SensorId`);

ALTER TABLE `Measurements` ADD FOREIGN KEY (`TypeId`) REFERENCES `Types` (`TypeId`);
