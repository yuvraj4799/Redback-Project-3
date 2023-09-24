// server.js

const mqtt = require('mqtt');
const publisherClient = mqtt.connect('mqtt://broker.hivemq.com:1883');

const sensorNames = ['Sensor1', 'Sensor2', 'Sensor3']; // Replace with the actual names of the sensors
const topicBattery = '/Battery';
const topicSatelliteNumber = '/SatelliteNumber';
const topicLatLong = '/LatLong';
const topicAltitude = '/Altitude';

// Simulated data for GPS sensors
const sensorData = [
    {
        batteryLevel: 85,
        satelliteNumber: 12,
        latitude: 37.7749,
        longitude: -122.4194,
        altitude: 100,
    },
    {
        batteryLevel: 78,
        satelliteNumber: 14,
        latitude: 40.7128,
        longitude: -74.0060,
        altitude: 150,
    },
    {
        batteryLevel: 92,
        satelliteNumber: 10,
        latitude: 34.0522,
        longitude: -118.2437,
        altitude: 75,
    },
];

publisherClient.on('connect', () => {
    console.log('MQTT connected for GPS Sensors');
    setInterval(() => {
        // Publish data for each sensor to respective topics
        sensorData.forEach((data, index) => {
            const sensorName = sensorNames[index];
            const sensorTopicBattery = `/${sensorName}${topicBattery}`;
            const sensorTopicSatelliteNumber = `/${sensorName}${topicSatelliteNumber}`;
            const sensorTopicLatLong = `/${sensorName}${topicLatLong}`;
            const sensorTopicAltitude = `/${sensorName}${topicAltitude}`;

            publisherClient.publish(sensorTopicBattery, data.batteryLevel.toString());
            publisherClient.publish(sensorTopicSatelliteNumber, data.satelliteNumber.toString());
            publisherClient.publish(sensorTopicLatLong, JSON.stringify({ latitude: data.latitude, longitude: data.longitude }));
            publisherClient.publish(sensorTopicAltitude, data.altitude.toString());
        });
    }, 5000); // Publish data every 5 seconds
});
