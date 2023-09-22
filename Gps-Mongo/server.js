const bodyParser = require('body-parser');
const mongoose = require('mongoose');
mongoose.connect('mongodb+srv://yuvraj:yuvraj%401234@gps.salfwnd.mongodb.net/GPS_SENSOR_DATA');


const gpsDevice = require('./models/gps');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const gps = require('./models/gps');

const serial_port = new SerialPort({
    path: '/dev/cu.usbmodem101',
    baudRate: 9600
})

const parser = serial_port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

parser.on('data', async (data) => {

    console.log(data);

    const array_data = data.split(" ");

    const sensorID = array_data[0];
    const time = array_data[1];
    const date = array_data[2];
    const latitude = array_data[3];
    const longitude = array_data[4];
    const altitude = array_data[5];
    const satellite = array_data[6];

    console.log(sensorID);
    console.log(time);
    console.log(date);
    console.log(latitude);
    console.log(longitude);
    console.log(altitude);
    console.log(satellite);

    try {
        const abc = await gpsDevice.findOne({ 'gpsSensorDeviceId': sensorID }).exec();

        if (abc == null) {
            var document = {
                'gpsSensorDeviceId': parseInt(sensorID),
                'sensorData': [
                    {
                        'timestamp': {
                            'time': time,
                            'date': date
                        },
                        'gps_sensor_data': {
                            'location': {
                                'latitude': latitude,
                                'logitude': longitude,
                            },
                            'altitude': parseFloat(altitude),
                            'satellite': parseInt(satellite)
                        }
                    }
                ]
            }
            const create = await gpsDevice.create(document);
            console.log(create);
        }

        if (abc != null) {
            console.log(abc);
        }

    } catch (error) {
        console.log(error);
    }

    try {
        const xyz = await gpsDevice.updateOne({ 'gpsSensorDeviceId': sensorID }, {
            $push: {
                'sensorData': [
                    {
                        'timestamp': {
                            'time': time,
                            'date': date
                        },
                        'gps_sensor_data': {
                            'location': {
                                'latitude': latitude,
                                'logitude': longitude,
                            },
                            'altitude': parseFloat(altitude),
                            'satellite': parseInt(satellite)
                        }
                    }
                ]
            }
        })

        console.log(xyz);

    } catch (error) {
        console.log(error);
    }

    console.log(data);
});



