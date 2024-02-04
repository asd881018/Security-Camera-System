import React from 'react'
import './Cards.css'

function Cards() {
  
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
        vid.style.display = "flex";
        vid.onended = function () {
            URL.revokeObjectURL(vidURL);
        }
        document.body.appendChild(vid);
    }

    return (
        <div className="streaming-section-container">
        </div>
    )
}

export default Cards