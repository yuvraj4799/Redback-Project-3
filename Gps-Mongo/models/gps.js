const mongoose = require('mongoose');

module.exports = mongoose.model('GPS_SENSOR', new mongoose.Schema({
    gpsSensorDeviceId: Number,
    sensorData: [
        {
            timestamp: {
                time: {
                    type: String,
                    required: true
                },
                date: {
                    type: String,
                    require: true
                }
            },
            gps_sensor_data: {
                location: {
                    latitude: {
                        type: String,
                        required: true
                    }, logitude: {
                        type: String,
                        required: true
                    }
                }, altitude: {
                    type: Number,
                    required: true
                }, satellite: {
                    type: Number,
                    required: true
                }
            },
        }
    ]
}, { collection: 'SENSOR_DATA' }));