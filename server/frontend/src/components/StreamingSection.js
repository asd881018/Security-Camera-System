import { sourceContentFor } from '@jridgewell/trace-mapping';
import React from 'react';
import '../App.css';
import './StreamingSection.css'

function StreamingSection(props) {

    const { socket } = props;
    var recorder;
    let chunks = [];
    let saveChunks = (e) => {
        chunks.push(e.data);
    }
    let exportStream = (e) => {
        const canvas = document.getElementById('videostream');
        var blob = new Blob(chunks);
        var vidURL = URL.createObjectURL(blob);
        var vid = document.createElement('video');
        vid.controls = true;
        vid.src = vidURL;
        vid.style.maxWidth = '640px';
        vid.style.maxHeight = '320px';
        vid.onended = function () {
            URL.revokeObjectURL(vidURL);
        }
        document.body.appendChild(vid);
    }

    props.socket.on("canvas", (data) => {
        const canvas = document.getElementById('videostream');
        const context = canvas.getContext('2d');
        const image = new Image();
        image.src = "data:image/jpeg;base64," + data;
        image.onload = function () {
            context.height = image.height;
            context.width = image.width;
            context.drawImage(image, 0, 0, context.width, context.height);
        }
    })

    props.socket.on("recordStart", () => {
        console.log("recordStart");

        chunks = [];
        const canvas = document.getElementById('videostream');
        let stream = canvas.captureStream(30);
        recorder = new MediaRecorder(stream);
        recorder.start();
        recorder.ondataavailable = saveChunks;
        recorder.onstop = exportStream;
    });

    props.socket.on("recordEnd", () => {
        console.log("recordEnd");
        try {
            recorder.stop();
        } catch { }
    });
    return (
        <div className="streaming-section-container">
            <div className="video-container">
                <canvas id="videostream" width="640" height="360" className="canvas"></canvas>
            </div>
            <div className="audio-container">
                <audio src='http://192.168.7.1:3000/audio' type='audio/mp3' controls></audio>
            </div>
        </div>
    );
}

export default StreamingSection;

<div className="streaming-section-container">
    <div className="video-container">
        <canvas id="videostream" width="640" height="360" className="canvas"></canvas>
    </div>
    <div className="audio-container">
        <audio src='http://192.168.7.1:3000/audio' type='audio/mp3' controls></audio>
    </div>
</div>