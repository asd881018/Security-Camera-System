import React from 'react';
import '../App.css';
import { BtnStreaming, BtnVideo } from './Button';
import './HeroSection.css';

function HeroSection() {
  return (
    <div className='hero-container'>
      {/* <video src='/videos/video-1.mp4' autoPlay loop muted /> */}
      <h1>Security Camera</h1>
      <p>What are you waiting for?</p>
      <div className='hero-btns'>
        <BtnStreaming
          className='btns'
          buttonStyle='btn--outline'
          buttonSize='btn--large'
        >
          STREAMING
        </BtnStreaming>
        
        <BtnVideo
          className='btns'
          buttonStyle='btn--primary'
          buttonSize='btn--large'
        >
          WATCH VIDEOS <i className='far fa-play-circle' />
        </BtnVideo>
      </div>
    </div>
  );
}

export default HeroSection;