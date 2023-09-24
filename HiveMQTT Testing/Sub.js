// client.js

const mqtt = require('mqtt');
const brokerUrl = 'mqtt://broker.hivemq.com:1883';

// Define the topics you want to subscribe to
const topics = ['/Sensor1/Battery', '/Sensor2/Battery', '/Sensor3/Battery', '/+/SatelliteNumber', '/+/LatLong', '/+/Altitude'];

const client = mqtt.connect(brokerUrl);

client.on('connect', () => {
    console.log(`MQTT connected for ${topics.join(', ')}`);
    client.subscribe(topics);
});

client.on('message', (receivedTopic, message) => {
    console.log(`Received message from topic: ${receivedTopic}`);

    // Parse the topic to extract relevant information (if needed)
    const topicParts = receivedTopic.split('/');
    const sensorId = topicParts[1];

    // Handle different message types based on the topic
    if (receivedTopic.endsWith('/Battery')) {
        console.log(`Battery Level for Sensor ${sensorId}: ${message.toString()}%`);
    } else if (receivedTopic.endsWith('/SatelliteNumber')) {
        console.log(`Satellite Number for Sensor ${sensorId}: ${message.toString()}`);
    } else if (receivedTopic.endsWith('/LatLong')) {
        const { latitude, longitude } = JSON.parse(message.toString());
        console.log(`LatLong for Sensor ${sensorId}: Latitude: ${latitude}, Longitude: ${longitude}`);
    } else if (receivedTopic.endsWith('/Altitude')) {
        console.log(`Altitude for Sensor ${sensorId}: ${message.toString()} meters`);
    } else {
        console.log(`Message is: ${message.toString()}`);
    }
    console.log('');
});
