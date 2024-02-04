const express = require("express");
const app = express();
const server = require("http").createServer(app);
const { Server } = require('socket.io');
const io = new Server(server);
const child = require('child_process');
const dgram = require('dgram');

const bbg = require('./src/bbg');

const port = 3000;
const client = dgram.createSocket('udp4');

app.use(express.json());
app.use(express.static('./frontend/dist'));

let recording = false;
io.on('connection', (socket) => {
  console.log('a user connected');

  // ask bbg for motion sensor value
  setInterval(() => {bbg.getMotion(client)}, 500);
  // capture bbg response for motion sensor value
  client.on('message', (data, remote) => {
    value = ""+data;
    if (value == "1" && !recording) {
      recording = true;
      io.sockets.emit('recordStart');
    } else if (value == "0" && recording) {
      recording = false;
      io.sockets.emit('recordEnd');
    }
  })

  // Camera, live streaming child process
  let ffmpeg = child.spawn("ffmpeg", [
    "-re",
    "-y",
    "-i",
    "udp://192.168.7.1:1234", // <--- CHANGE 192.168.6.1 TO MATCH YOUR BBG IP, todo: make this a variable
    "-preset",
    "ultrafast",
    "-f",
    "mjpeg",
    "pipe:1"
  ]);
  ffmpeg.on('error', function (err) {
    console.log(err);
    throw err;
  });
  ffmpeg.on('close', function (code) {
    console.log('ffmpeg exited with code ' + code);
  });
  ffmpeg.stderr.on('data', function (data) {
    // Don't remove this
    // Child Process hangs when stderr exceed certain memory
    let error = ""+data;
  });
  ffmpeg.stdout.on('data', function (data) {
    var frame = Buffer.from(data).toString('base64'); //convert raw data to string
    io.sockets.emit('canvas', frame); //send data to client
  });

  let ffm = child.spawn(
    "ffmpeg",
    "-f mp3 -i udp://192.168.7.1:10001 -f mp3 -".split(
      " "
    )
  );

  app.get("/audio", (req, res) => {
    console.log("Audio request");
      res.writeHead(200, { "Content-Type": "audio/mp3" });

      ffm.stdout.on("data", (data) => {
        res.write(data);
      });
    });

});

var listener = server.listen(process.env.PORT || port, () => console.log(`Listening on ${listener.address().port}`))
