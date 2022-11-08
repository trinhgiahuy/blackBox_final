// import './App.css';
import React from 'react';
import { Routes, Route} from 'react-router-dom';
// import { Switch } from "react-router"
import SideBar from './components/Sidebar/Sidebar'
import MainLayout from './layout/MainLayout/MainLayout';
import Overview from './pages/Overview/Overview';
import BlackboxManagement from './pages/BlackboxManagement/BlackboxManagement'

const App = () => {

    return(
        <div>
          <SideBar />
          <Routes>
            <Route path ="/" element= {<MainLayout />}/>
            <Route path = "/overview" element = {<Overview />}/>
            <Route path = "/management" element={<BlackboxManagement />}/>
          </Routes>
          
        </div>
        
    );

}

export default App;
