const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const fs = require('fs');

const port = new SerialPort({ path: '/dev/cu.usbmodem11101', baudRate: 9600 }, false);
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

const csvFilePath = 'DataLog.csv'; // Set your desired CSV file path

// Create a writable stream to the CSV file
const csvStream = fs.createWriteStream(csvFilePath);

// Write the CSV header
csvStream.write('time,data values\n');

parser.on('data', data => {
    const currentTime = new Date().toISOString(); // Generate the current time
    csvStream.write(`${currentTime},${data}\n`); // Write data to the CSV file
    console.log(`${currentTime} | ${data}`);
});