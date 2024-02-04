const dgram = require('dgram');

const PORT = 12345;
const HOST = '192.168.7.2'; // <--- replace .6. with .7. if you are running a VM

function getMotion(client) {
    let buffer = Buffer.alloc("motion".length, "motion");

    client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
        if (err) 
            throw err; 
        // console.log('UDP message sent to ' + HOST +':'+ PORT);
    });
}

module.exports = {
    getMotion
}