import React, { useState, useEffect } from 'react'
import { Link } from 'react-router-dom'
// import { Button } from './Button';
import './Navbar.css';

function NavBar() {
    const [click, setClick] = useState(false);
    const [button, setButton] = useState(true);

    const handleClick = () => setClick(!click);
    const closeMobileMenus = () => setClick(false);

    const showButton = () => {
        if (window.innerWidth <= 960) {
            setButton(false);
        } else {
            setButton(true);
        }
    }

    useEffect(() => {
        showButton();
    }, []);

    window.addEventListener('resize', showButton);

    return (
        <>
            <nav className='navbar'>
                <div className='navbar-container'>
                    <Link to="/" className="navbar-logo" onClick = {closeMobileMenus}>
                        HSCP Inc &nbsp; <i className='fa-sharp fa-solid fa-place-of-worship' />
                    </Link>
                    <div className='menu-icon' onClick={handleClick}>
                        <i className={click ? 'fas fa-times' : 'fas fa-bars'} />
                    </div>
                    <ul className={click ? 'nav-menu active' : 'nav-menu'}>
                        <li className='nav-item'>
                            <Link to='/' className='nav-links' onClick={closeMobileMenus}>
                                Home
                            </Link>
                        </li>
                        <li className='nav-item'>
                            <Link to='/streaming' className='nav-links' onClick={closeMobileMenus}>
                                Streaming
                            </Link>
                        </li>
                        <li className='nav-item'>
                            <Link to='/videos' className='nav-links' onClick={closeMobileMenus}>
                                Videos
                            </Link>
                        </li>
                        
                    </ul>
                    
                </div>
            </nav>
        </>
    )
}

export default NavBar