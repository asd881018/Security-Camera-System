import React, { useState, useEffect } from "react";

import Navbar from './components/Navbar';
import './App.css';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Home from './components/pages/Home';
import Streaming from './components/pages/Streaming';
import Videos from './components/pages/Videos';

function App() {

  // The return statement uses fragments <></> that wrap all the elements.
  // It renders components wrapped in a react-router-dom's <Router> component. 
  return (
    <>
      <Router>
        <Navbar />
        <Routes>
          <Route exact path='/' element={<Home/>} />
          <Route path='/streaming' element={<Streaming/>} />
          <Route path='/videos' element={<Videos/>}/>
        </Routes>
      </Router>
    </>
  );
}

export default App;