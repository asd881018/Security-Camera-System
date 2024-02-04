import React from "react";
import '../../App.css'
import { io } from 'socket.io-client';
import StreamingSection from "../StreamingSection";

export default function Streaming() {
    const socket = io();
    return (
        <>
            <h1 className="streaming">STREAMING</h1>
            <StreamingSection  socket={socket} />
        </>
    );
}